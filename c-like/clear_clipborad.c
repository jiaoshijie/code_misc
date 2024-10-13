#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

/* The name we were invoked as (argv[0]) */
static char *progname;

/* Our X Display and Window */
static Display *display;
static Window window;

/* Our timestamp for all operations */
static Time timestamp;

static Time get_timestamp(void)
{
    XEvent event;

    XSelectInput (display, window, PropertyChangeMask);
    XChangeProperty (display, window, XA_WM_NAME, XA_STRING, 8,
            PropModeAppend, NULL, 0);

    for(;;) {
        XNextEvent (display, &event);

        if (event.type == PropertyNotify && event.xproperty.window == window)
            return event.xproperty.time;
    }
}

static void clear_selection(void)
{
    Atom clipboard = XInternAtom(display, "CLIPBOARD", False);

    XSetSelectionOwner(display, XA_PRIMARY, None, timestamp);
    XSetSelectionOwner(display, XA_SECONDARY, None, timestamp);
    XSetSelectionOwner(display, clipboard, None, timestamp);

    /* Call XSync to ensure this operation completes before program
     * termination, especially if this is all we are doing. */
    XSync(display, False);
}


int main(int argc, char **argv) {
    Window root;

    progname = argv[0];
    const char *window_name = progname;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "XOpenDisplay failed");
        exit(1);
    }
    root = XDefaultRootWindow(display);
    int black = BlackPixel (display, DefaultScreen(display));
    window = XCreateSimpleWindow(display, root, 0, 0, 1, 1, 0, black, black);

    XStoreName(display, window, window_name);

    timestamp = get_timestamp();

    clear_selection();

    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
