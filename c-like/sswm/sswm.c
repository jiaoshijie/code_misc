#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define LENGTH(X) (sizeof X / sizeof X[0])
#define CLEANMASK(mask) (mask & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))

static Display *dpy;  // "structure" that cannot be modified by programer
static Window root;
static XWindowAttributes attr;
static XButtonEvent start;
static XEvent ev;
static int running = 1;
static FILE *messageP;
typedef struct client{
  // Prev and next client
  struct client *next;
  struct client *prev;

  // The window
  Window win;
}client;
static client *w_head, *w_current;

typedef union {
  int i;
  unsigned int ui;
  float f;
  const void *v;
}Arg;

typedef struct {
  unsigned int mod;
  KeySym keysym;
  void (*func)(const Arg *);
  const Arg arg;
}Key;

static void checkotherwm();
static int OnWmDetected(Display *display, XErrorEvent *e);
static int OnXError(Display *display, XErrorEvent *e);
static void grabkeys();
static void grabbutton();
static void Run();
static void spawn(const Arg *arg);
static void quit(const Arg *arg);
static void killclient(const Arg *arg);
static void keypress();
static void buttonpress();
static void buttonrelease();
static void motionotify();
static void sigchld(int unused);
static void die(const char *m);
static void maprequest();
static void setup();
static int sendevent(Atom proto);
static void focus();  // focus w_current if it isn't a NULL
static void cleanup();
static void destroynotify();
static void remove_window();

static void (*handler[LASTEvent]) () = {
  [ButtonPress] = buttonpress,
  [KeyPress] = keypress,
  [MotionNotify] = motionotify,
  [ButtonRelease] = buttonrelease,
  [MapRequest] = maprequest,
  [DestroyNotify] = destroynotify
};

#include "config.h"

int main() {

  // messageP = fopen("/home/red/Downloads/wm/sswm/message.txt",  "w");
  messageP = stdout;
  if (!messageP) {
    fputs("open file failed", stderr);
    exit(EXIT_FAILURE);
  }

  if (!(dpy = XOpenDisplay(0x0))) {
    fputs("Error: Cannot connect to X server.\n", messageP);
    return 1;
  }

  root = DefaultRootWindow(dpy);

  checkotherwm();

  setup();

  Run();

  cleanup();
  if (messageP != stdout) fclose(messageP);
  XCloseDisplay(dpy);
  return 0;
}


int OnWmDetected(Display *display, XErrorEvent *e) {
  if ((int)(e->error_code) == BadAccess) {
    fprintf(messageP, "Error: sswm: another wm has already been running!\n");
  }
  return 0;
}

int OnXError(Display *display, XErrorEvent *e) {
  fprintf(messageP, "Error: Error Code: %d\n", (int)(e->error_code));
  return 0;
}


void checkotherwm() {
  XSetErrorHandler(&OnWmDetected);
  // NOTICE: After using SubstructureRedirectMask, you need to respond the "MapRequest" event to show window
  XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);
  XSync(dpy, False);
  // set error handler
  XSetErrorHandler(&OnXError);
  XSync(dpy, False);
}

void grabkeys() {
  for (unsigned int i = 0; i < LENGTH(keys); i++) {
    XGrabKey(dpy, XKeysymToKeycode(dpy, keys[i].keysym), keys[i].mod,
        root, True, GrabModeAsync, GrabModeAsync);  // open dmenu_run
  }
}

void grabbutton() {
  XGrabButton(dpy, 1, Mod4Mask, root, True,
      ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
      GrabModeAsync, GrabModeAsync, None, None);

  XGrabButton(dpy, 3, Mod4Mask, root, True,
      ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
      GrabModeAsync, GrabModeAsync, None, None);
}

void Run() {
  start.subwindow = None;
  XSync(dpy, False);
  while (running && !XNextEvent(dpy, &ev)) {
    if (handler[ev.type])
      handler[ev.type]();
  }
}

void spawn(const Arg *arg) {
  if (fork() == 0) {
    if (dpy)
      close(ConnectionNumber(dpy));
    setsid();
    execl(((char**)arg->v)[0], ((char**)arg->v)[1], NULL);
  }
  // printf("spawn = %p\n", (void*)w_head);
}

void quit(const Arg *arg) {
  running = 0;
}

static int sendevent(Atom proto) {
  int n;
  Atom *protocols;
  int exists = 0;
  XEvent ke;
  if (XGetWMProtocols(dpy, w_current->win, &protocols, &n)) {
    while (!exists && n--)
      exists = protocols[n] == proto;
    XFree(protocols);
  }
  if (exists) {
    // send a message of type WM_PROTOCOLS and value WM_DELETE_WINDOW to kill it.
    ke.type = ClientMessage;
    ke.xclient.window = w_current->win;
    ke.xclient.message_type = XInternAtom(dpy, "WM_PROTOCOLS", True);
    ke.xclient.format = 32;
    ke.xclient.data.l[0] = XInternAtom(dpy, "WM_DELETE_WINDOW", True);
    ke.xclient.data.l[1] = CurrentTime;
    XSendEvent(dpy, w_current->win, False, NoEventMask, &ke);
  }
  return exists;
}

void killclient(const Arg *arg) {
  if (!w_current)
    return;
  // printf("w_current = %p\n", (void*)w_current);
  if (!sendevent(XInternAtom(dpy, "WM_DELETE_WINDOW", False))) {
    // kill window directly with XKillClient()
    XKillClient(dpy, w_current->win);
  }
  focus();
}

void keypress() {
  KeySym ks = XKeycodeToKeysym(dpy, (KeyCode)ev.xkey.keycode, 0);

  for (unsigned int i = 0; i < LENGTH(keys); i++) {
    if (ks == keys[i].keysym
        && CLEANMASK(keys[i].mod) == CLEANMASK(ev.xkey.state)
        && keys[i].func) {
      keys[i].func(&(keys[i].arg));
    }
  }
}

void buttonpress() {
  // NOTE: 这个事件是wm的所以要用subwindow
  if (ev.xkey.subwindow != None) {
    client *p = NULL;
    for (p = w_head; p->win != ev.xkey.subwindow && p != NULL; p = p->next);
    if (p)
      w_current = p;
    focus();
    XGetWindowAttributes(dpy, w_current->win, &attr);
    start = ev.xbutton;
    // printf("w_head: %p\n", (void*)w_head);
  }
}

void focus() {
  if (!w_current) return;
  XRaiseWindow(dpy, w_current->win);
  XSetInputFocus(dpy, w_current->win, RevertToPointerRoot, CurrentTime);
}

void buttonrelease() {
  int i = 0;
  for (client *p = w_head; p; p = p->next) {
    printf("w_head[%d] = %p\n", ++i, (void*)p);
  }
#if 0
  if (ev.xkey.subwindow != None) {
    Window Wroot, Wparent, *Wchild = NULL;
    unsigned int num_Wchild;
    XQueryTree(dpy, ev.xbutton.window, &Wroot, &Wparent, &Wchild, &num_Wchild);
    fprintf(messageP, "INFO: window = %ld, root = %ld, subwindow = %ld, Wroot = %ld, Wparent = %ld\n",
        ev.xbutton.window, ev.xbutton.root, ev.xbutton.subwindow, Wroot, Wparent);
    if (Wchild)
      XFree((char *)Wchild);
  }
#endif
}

void motionotify() {
  if (ev.xkey.subwindow != None) {
    int xdiff = ev.xbutton.x_root - start.x_root;
    int ydiff = ev.xbutton.y_root - start.y_root;

    if (start.button == 1) { // MOVE
      XMoveWindow(dpy, start.subwindow, attr.x + xdiff, attr.y + ydiff);
    } else if (start.button == 3) {  // RESIZE
      XResizeWindow(dpy, start.subwindow,
          MAX(300, attr.width + xdiff), MAX(300, attr.height + ydiff));
    }
  }
}

void sigchld(int unused) {
  // Again, thx to dwm ;)
  if(signal(SIGCHLD, sigchld) == SIG_ERR)
    die("Can't install SIGCHLD handler");
  while(0 < waitpid(-1, NULL, WNOHANG));
}

void die(const char *m) {
  fprintf(messageP, "Error: sswm: %s\n", m);
  exit(EXIT_FAILURE);
}


void maprequest() {
  XMapRequestEvent *e = &ev.xmaprequest;
  client *c = (client*)malloc(sizeof(client)), *p;
  if (!w_head) {
    c->next = NULL;
    c->prev = NULL;
    w_head = c;
  } else {
    for (p = w_head; p->next; p = p->next);
    c->next = NULL;
    c->prev = p;
    p->next = c;
  }
  c->win = e->window;
  w_current = c;
  XMapWindow(dpy, c->win);
  XRaiseWindow(dpy, w_current->win);
  XSetInputFocus(dpy, w_current->win, RevertToPointerRoot, CurrentTime);
  // printf("maprequest is running!!!\n");
}

void setup() {

  sigchld(0);
  grabkeys();
  grabbutton();

  w_head = NULL;
  w_current = NULL;

  // NOTE: reparent existing top-level windows, MapRequest event handle it
}

static void cleanup() {
  while (w_head) {
    w_current = w_head;
    killclient(0);
    w_head = w_head->next;
  }
}

void destroynotify() {
  // printf("destory event\n");
  int i = 0;
  client *p;
  XDestroyWindowEvent *de = &ev.xdestroywindow;
  for (p = w_head; p; p = p->next)
    if(de->window == p->win) i++;

  if (i == 0) return;
  remove_window(de->window);
  focus();
}

void remove_window() {
  client *dc = w_current;
  if (w_head == w_current) {
    w_head = w_head->next;
    if (w_head)
      w_head->prev = NULL;
    w_current = w_head;
  } else {
    client *p = NULL;
    for (p = w_head; p->next != w_current; p=p->next);
    p->next = w_current->next;
    if (w_current->next) {
      w_current->next->prev = p;
      w_current = p->next;
    } else {
      w_current = w_head;
    }
  }
  free(dc);
}
