/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-nyc-medium-*-*-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#111113";
static const char normbgcolor[]     = "#111113";
static const char normfgcolor[]     = "#888a85";
static const char selbordercolor[]  = "#2e3436";
static const char selbgcolor[]      = "#111113";
static const char selfgcolor[]      = "#eeeeec";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* statuscolors-6.0 - shittiest patch ever */
#define NUMCOLORS 14
const char colors[NUMCOLORS][ColLast][8] = {
    /* border     foreground background */
    { "#111113", "#888a85", "#111113" }, /* (01) section 0 norm */
    { "#2e3436", "#eeeeec", "#111113" }, /* (02) section 0 sel */
    { "#111113", "#2e3436", "#111113" }, /* (03) section 0 misc */
    { "#111113", "#19191c", "#111113" }, /* (04) divider 1 */
    { "#19191c", "#555753", "#19191c" }, /* (05) section 1 grey */
    { "#19191c", "#3465a4", "#19191c" }, /* (06) section 1 blue */
    { "#19191c", "#73d216", "#19191c" }, /* (07) section 1 green */
    { "#19191c", "#edd400", "#19191c" }, /* (08) section 1 yellow */
    { "#ffffff", "#ffffff", "#ffffff" }, /* (09) shit is broken */
    { "#ffffff", "#ffffff", "#ffffff" }, /* (0a) shit is broken */
    { "#19191c", "#cc0000", "#19191c" }, /* (0b) section 1 red */
    { "#19191c", "#babdb6", "#19191c" }, /* (0c) divider 2 */
    { "#babdb6", "#19191c", "#babdb6" }, /* (0d) section 2 black */
    { "#babdb6", "#7f967c", "#babdb6" }, /* (0e) section 2 grey */
};

/* tagging */
static const char *tags[] = { "u", "d", "t", "q" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

/* bstack-6.0 */
#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "`t",      tile },    /* first entry is default */
	{ "`f",      NULL },    /* no layout function means floating behavior */
	{ "`m",      monocle },
    { "`s",      bstack },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *nyccmd[]   = { "urxvt", "-fn", "xft:nyc:pixel=10"};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = nyccmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
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
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

