/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[] = "-*-xbmicons-medium-r-*-*-12-*-*-*-*-*-*-*" ","
                           "-*-terminus2-medium-r-*-*-12-*-*-*-*-*-*-*";
#define NUMCOLORS 12
static const char colors[NUMCOLORS][ColLast][9] = {
  // border foreground background
  { "#282a2e", "#777b81", "#1d1f21" }, // 1 = normal (grey on black)
  { "#f0c674", "#c5c8c6", "#1d1f21" }, // 2 = selected (white on black)
  { "#dc322f", "#1d1f21", "#f0c674" }, // 3 = urgent (black on yellow)
  { "#282a2e", "#282a2e", "#1d1f21" }, // 4 = darkgrey on black (for glyphs)
  { "#282a2e", "#1d1f21", "#282a2e" }, // 5 = black on darkgrey (for glyphs)
  { "#282a2e", "#cc6666", "#1d1f21" }, // 6 = red on black
  { "#282a2e", "#b5bd68", "#1d1f21" }, // 7 = green on black
  { "#282a2e", "#de935f", "#1d1f21" }, // 8 = orange on black
  { "#282a2e", "#f0c674", "#282a2e" }, // 9 = yellow on darkgrey
  { "#282a2e", "#81a2be", "#282a2e" }, // A = blue on darkgrey
  { "#282a2e", "#b294bb", "#282a2e" }, // B = magenta on darkgrey
  { "#282a2e", "#8abeb7", "#282a2e" }, // C = cyan on darkgrey
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "\uE002", "\uE002", "\uE002", "\uE002", "\uE002",
                              "\uE008", "\uE007", "\uE007","\uE007 " };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Emoji Choice",     NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.50;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "\uE019 \uE009 \uE019",    tile },    /* first entry is default */
  { "\uE019 \uE00A \uE019",    NULL },    /* no layout function means floating behavior */
  { "\uE019 \uE00B \uE019",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char  *dmenucmd[]     = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]       = { "st", NULL };
static const char *volupcmd[]      = { "amixer", "-D", "pulse", "-q", "sset", "Master", "5%+", NULL };
static const char *voldncmd[]      = { "amixer", "-D", "pulse", "-q", "sset", "Master", "5%-", NULL };
static const char *voltogcmd[]     = { "amixer", "-D", "pulse", "-q", "sset", "Master", "toggle", NULL };
static const char *mbrupcmd[]      = { "xbacklight", "-inc", "5", NULL };
static const char *mbrdncmd[]      = { "xbacklight", "-dec", "5", NULL };

static Key keys[] = {
  /* modifier               key                       function        argument */
  { MODKEY,                 XK_p,                     spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,       XK_Return,                spawn,          {.v = termcmd } },
  { False,                  XF86XK_AudioRaiseVolume,  spawn,          {.v = volupcmd } },
  { False,                  XF86XK_AudioLowerVolume,  spawn,          {.v = voldncmd } },
  { False,                  XF86XK_AudioMute,         spawn,          {.v = voltogcmd } },
  { False,                  XF86XK_KbdBrightnessUp,   spawn,          {.v = mbrupcmd } },
  { False,                  XF86XK_KbdBrightnessDown, spawn,          {.v = mbrdncmd } },
  //{ MODKEY|ControlMask,     XK_b,                     togglebar,      {0} },
  { MODKEY,                 XK_j,                     focusstack,     {.i = +1 } },
  { MODKEY,                 XK_k,                     focusstack,     {.i = -1 } },
  //{ MODKEY,                 XK_i,                     incnmaster,     {.i = +1 } },
  //{ MODKEY,                 XK_d,                     incnmaster,     {.i = -1 } },
  //{ MODKEY,                 XK_h,                     setmfact,       {.f = -0.05} },
  //{ MODKEY,                 XK_l,                     setmfact,       {.f = +0.05} },
  { MODKEY,                 XK_Return,                zoom,           {0} },
  { MODKEY,                 XK_Tab,                   view,           {0} },
  { MODKEY|ShiftMask,       XK_c,                     killclient,     {0} },
  { MODKEY|ShiftMask,       XK_q,                     killclient,     {0} },
  { MODKEY,                 XK_t,                     setlayout,      {.v = &layouts[0]} },
  { MODKEY,                 XK_f,                     setlayout,      {.v = &layouts[1]} },
  //{ MODKEY,                 XK_m,                     setlayout,      {.v = &layouts[2]} },
  { MODKEY,                 XK_space,                 setlayout,      {0} },
  { MODKEY|ShiftMask,       XK_space,                 togglefloating, {0} },
  { MODKEY,                 XK_0,                     view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,       XK_0,                     tag,            {.ui = ~0 } },
  //{ MODKEY,                 XK_comma,                 focusmon,       {.i = -1 } },
  //{ MODKEY,                 XK_period,                focusmon,       {.i = +1 } },
  //{ MODKEY|ShiftMask,       XK_comma,                 tagmon,         {.i = -1 } },
  //{ MODKEY|ShiftMask,       XK_period,                tagmon,         {.i = +1 } },
  TAGKEYS(                  XK_1,                             0)
  TAGKEYS(                  XK_2,                             1)
  TAGKEYS(                  XK_3,                             2)
  TAGKEYS(                  XK_4,                             3)
  TAGKEYS(                  XK_5,                             4)
  TAGKEYS(                  XK_6,                             5)
  TAGKEYS(                  XK_7,                             6)
  TAGKEYS(                  XK_8,                             7)
  TAGKEYS(                  XK_9,                             8)
  { MODKEY|ShiftMask|ControlMask,       XK_q,         quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        toggleview,     {0} },
  { ClkTagBar,            0,              Button3,        view,           {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

