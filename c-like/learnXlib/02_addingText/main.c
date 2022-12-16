#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

int main() {
  Display *dpy;
  int screen;
  Window win;
  XEvent event;

  Window childwin;

  int x, y;
  Window root_win;
  Colormap colormap;
  XColor button_color;
  XColor lightgray_color, darkgray_color;
  XGCValues gcv_lightgray, gcv_darkgray;
  GC gc_lightgray, gc_darkgray;
  unsigned int border_width, depth, width, height;

  // Text declaration vars
  XFontStruct *font;
  XTextItem ti[1];

  if (!(dpy = XOpenDisplay(NULL))) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(dpy);

  win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), /*x*/ 200, /*y*/ 200,
                            /*width*/ 500, /*height*/ 300, 1,
                            XBlackPixel(dpy, screen),
                            WhitePixel(dpy, screen));


  XSelectInput(dpy, win, ExposureMask | KeyPressMask);
  XMapWindow(dpy, win);

  // child window

  colormap = XDefaultColormap(dpy, screen);
  XParseColor(dpy, colormap, "rgb:cc/cc/cc", &button_color);
  XAllocColor(dpy, colormap, &button_color);

  XParseColor(dpy, colormap, "rgb:ee/ee/ee", &lightgray_color);
  XAllocColor(dpy, colormap, &lightgray_color);
  gcv_lightgray.foreground = lightgray_color.pixel;
  gcv_lightgray.background = button_color.pixel;
  gc_lightgray = XCreateGC(dpy, RootWindow(dpy, screen),
                           GCForeground | GCBackground, &gcv_lightgray);

  XParseColor(dpy, colormap, "rgb:88/88/88", &darkgray_color);
  XAllocColor(dpy, colormap, &darkgray_color);
  gcv_darkgray.foreground = darkgray_color.pixel;
  gcv_darkgray.background = button_color.pixel;
  gc_darkgray = XCreateGC(dpy, RootWindow(dpy, screen),
                           GCForeground | GCBackground, &gcv_darkgray);

  childwin = XCreateSimpleWindow(
      dpy, win, /*x*/ 20, /*y*/ 20,
      /*width*/ 200, /*height*/ 100, 1, XBlackPixel(dpy, screen),
      button_color.pixel);

  XSelectInput(dpy, childwin,
               ExposureMask | KeyPressMask | ButtonPressMask |
                   ButtonReleaseMask);
  XMapWindow(dpy, childwin);

  XGetGeometry(dpy, childwin, &root_win, &x, &y, &width, &height, &border_width,
               &depth);

  while (1) {
    XNextEvent(dpy, &event);
    if (event.xany.window == childwin) {
      if (event.type == Expose) {
        // XDrawLine(dpy, childwin, DefaultGC(dpy, screen), 10, 10, 60, 60);
        XDrawLine(dpy, childwin, gc_lightgray, 0, 0, width - 1, 0);
        XDrawLine(dpy, childwin, gc_lightgray, 0, 0, 0, height - 1);
        XDrawLine(dpy, childwin, gc_darkgray, width - 1, 0, width - 1, height - 1);
        XDrawLine(dpy, childwin, gc_darkgray, 0, height - 1, width - 1, height - 1);
        // see: https://comp.unix.programmer.narkive.com/QRQKSVeD/xlib-load-fonts
        // see: https://unix.stackexchange.com/questions/428776/adding-a-font-to-x11-xloadqueryfont
        font = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-*-*-17-*-*-*-*-*-*-*");  // To install "xorg-xlsfonts" in archlinux, this command will list all X fonts.
        ti[0].chars = "Press me!";
        ti[0].nchars = strlen(ti[0].chars);
        ti[0].delta = 0;
        ti[0].font = font->fid;
        XDrawText(dpy, childwin, DefaultGC(dpy, screen),
                  (width - XTextWidth(font, ti[0].chars, ti[0].nchars)) / 2,
                  (height - (font->ascent + font->descent)) / 2 + font->ascent,
                  ti, 1);
        XUnloadFont(dpy, font->fid);
      }
      if (event.type == ButtonPress) {
        if (event.xbutton.button == 1) {
          XDrawLine(dpy, childwin, gc_darkgray, 0, 0, width - 1, 0);
          XDrawLine(dpy, childwin, gc_darkgray, 0, 0, 0, height - 1);
          XDrawLine(dpy, childwin, gc_lightgray, width - 1, 0, width - 1, height - 1);
          XDrawLine(dpy, childwin, gc_lightgray, 0, height - 1, width - 1, height - 1);
        }
      }

      if (event.type == ButtonRelease) {
        if (event.xbutton.button == 1) {
          XDrawLine(dpy, childwin, gc_lightgray, 0, 0, width - 1, 0);
          XDrawLine(dpy, childwin, gc_lightgray, 0, 0, 0, height - 1);
          XDrawLine(dpy, childwin, gc_darkgray, width - 1, 0, width - 1, height - 1);
          XDrawLine(dpy, childwin, gc_darkgray, 0, height - 1, width - 1, height - 1);
        }
      }
    }
  }

  XCloseDisplay(dpy);
  return 0;
}
