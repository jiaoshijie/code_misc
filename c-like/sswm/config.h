static char *stcmd[] = { "/usr/local/bin/st", "st" };
static char *dmenucmd[] = { "/usr/local/bin/dmenu_run", "dmenu_run"};

static Key keys[] = {
  { Mod4Mask,               XK_Return,  spawn,        { .v = stcmd } },
  { Mod4Mask,               XK_d,       spawn,        { .v = dmenucmd } },
  { Mod4Mask | ShiftMask,   XK_q,       killclient,   { 0 } },
  { Mod4Mask | ShiftMask,   XK_d,       quit,         { 0 } },
};
