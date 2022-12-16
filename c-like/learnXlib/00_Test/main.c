#include "head.h"

// int (*funp(int (*hand)(int x, int y))) () { return hand; };
// int (*funcp) (int x, int y);

int main() {
  // funcp = funp(func);
  // funcp(1, 2);

  static Display *dpy;
  if (!(dpy = XOpenDisplay(NULL))) {
    printf("Can not open a display\n");
  } else {
    int screen = DefaultScreen(dpy);
    unsigned int w = XDisplayWidth(dpy, screen), h = XDisplayHeight(dpy, screen);
    unsigned int d = DefaultDepth(dpy, screen);
    Window root = RootWindow(dpy, screen);

    // printf("XDisplay Cells = %d\n", XDisplayCells(dpy, XDefaultScreen(dpy)));
    // printf("XDisplay Planes = %d\n", XDisplayPlanes(dpy, XDefaultScreen(dpy)));

    // printf("XDisplayMM Width = %d, XDisplayMM Height = %d\n",
    //        XDisplayWidthMM(dpy, screen),
    //        XDisplayHeightMM(dpy, XDefaultScreen(dpy)));
    // printf("Color Depth = %d\n", d);

    Drawable drawable = XCreatePixmap(dpy, root, w, h, d);
    printf("root = %ld, drawable = %ld\n", root, drawable);
  }
  XCloseDisplay(dpy);

  // printf("%s\n", setlocale(LC_CTYPE, ""));
  return 0;
}
