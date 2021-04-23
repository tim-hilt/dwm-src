/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const unsigned int gappih    = 60;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 60;       /* vert inner gap between windows */
static const unsigned int gappoh    = 60;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 60;       /* vert outer gap between windows and screen edge */
static const int vertpad            = 24;       /* vertical padding of bar */
static const int sidepad            = 60;       /* horizontal padding of bar */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#191c21";
static const char col_gray2[]       = "#282c34";
static const char col_gray3[]       = "#bbc2cf";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#51afef";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray3, col_gray2, col_cyan  },
};

static const char *const autostart[] = {
	"autorandr", "--change", NULL,
	"hsetroot", "-cover", "/home/tim/Pictures/background.jpg", NULL,
	"sh", "-c", "while :; do xsetroot -name \"$(LC_ALL=de_DE.utf8 date +\'%A, %d. %B %Y, %R \'), $(cat /sys/class/power_supply/BAT0/status)%\";"
	"if [[ \"$(cat /sys/class/power_supply/BAT0/status)\" = \"Discharging\" && $(cat /sys/class/power_supply/BAT0/capacity) -lt 10 ]];"
	"then dunstify \"Battery at $(cat /sys/class/power_supply/BAT0/capacity)%!\"; fi; sleep 60; done", NULL,
	"xset", "b", "off", NULL, "mpris-proxy", NULL, "udiskie", NULL, "dunst", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title          tags mask     isfloating   monitor */
	{ "Gimp",          NULL,       NULL,          0,            1,           -1 },
	{ "Alacritty",     NULL,       "float",       0,            1,           -1 },
	{ "Firefox",       NULL,       NULL,          1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define HOLDKEY 0xffe4 // Right Control-Key
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMINAL "alacritty"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray3, NULL };
static const char *termcmd[]     = { TERMINAL, NULL };
static const char *floatingterm[]= { TERMINAL, "-t", "float", NULL };
static const char *ranger[]      = { TERMINAL, "-e", "ranger", NULL };
/* static const char *literature[]  = { TERMINAL, "-e", "ranger", "/home/tim/Literatur/", NULL }; */
/* static const char *studying[]    = { TERMINAL, "-e", "ranger", "/home/tim/Studium/", NULL }; */
/* static const char *julia[]       = { TERMINAL, "-e", "julia", NULL }; // Temporarily deactivated, because not needed*/
static const char *python[]      = { TERMINAL, "-e", "ipython", NULL };
static const char *htop[]        = { TERMINAL, "-e", "htop", NULL};
static const char *screenshot[]  = { "spectacle",  NULL };
static const char *lum_up[]      = { "light", "-A", "5", NULL};
static const char *lum_down[]    = { "light", "-U", "5", NULL};
static const char *vol_up[]      = { "amixer", "set", "Master", "unmute", "3%+", "-q", NULL };
static const char *vol_down[]    = { "amixer", "set", "Master", "unmute", "3%-", "-q", NULL };
static const char *vol_mute[]    = { "amixer", "set", "Master", "toggle", "-q", NULL };
static const char *player_toggle[] = { "playerctl", "play-pause", NULL };
static const char *player_next[] = { "playerctl", "next", NULL };
static const char *player_prev[] = { "playerctl", "previous", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = floatingterm } },
	{ MODKEY,                       XK_r,      spawn,          {.v = ranger } },
	/* { MODKEY,                       XK_s,      spawn,          {.v = studying } }, */
	/* { MODKEY,                       XK_l,      spawn,          {.v = literature } }, */
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = python } },
	/* { MODKEY|ShiftMask,             XK_j,      spawn,          {.v = julia } }, */
	{ MODKEY,                       XK_h,      spawn,          {.v = htop } },
	/* { MODKEY,                       XK_b,      togglebar,      {0} }, */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_plus,   incrgaps,       {.i = +5 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -5 } },
	{ MODKEY,                       XK_o,      incrogaps,      {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_o,      incrogaps,      {.i = -5 } },
	{ MODKEY,                       XK_i,      incrigaps,      {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_i,      incrigaps,      {.i = -5 } },
	{ MODKEY,                       XK_0,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_0,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_c,      center,         {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, // Send client to different monitor
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            0x1008ff13,spawn,          {.v = vol_up } },
	{ 0,                            0x1008ff11,spawn,          {.v = vol_down } },
    { 0,                            0x1008ff02,spawn,          {.v = lum_up } },
    { 0,                            0x1008ff03,spawn,          {.v = lum_down } },
    { 0,                            0x1008ff12,spawn,          {.v = vol_mute } },
	{ 0,                            0x1008ff14,spawn,          {.v = player_toggle} },
	{ 0,                            0x1008ff31,spawn,          {.v = player_toggle} },
	{ 0,                            0x1008ff17,spawn,          {.v = player_next} },
	{ 0,                            0x1008ff16,spawn,          {.v = player_prev} },
    { 0,                            XK_Print,  spawn,          {.v = screenshot } },
	{ 0,                            HOLDKEY,   holdbar,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

