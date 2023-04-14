/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 5;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int barborders         = 1;        /* 0 means no borders in bar */
static const char *fonts[]          = {
	"Agave:size=10", /* this is for nerd font icons with agave nerd font */
	"monospace:size=14",
	"Noto Emoji:size=8",
};
static const char normbgcolor[]         = "#282a36";
static const char normbordercolor[]     = "#44475a";
static const char normfgcolor[]         = "#f8f8f2"; /* 1 */
static const char selbgcolor[]          = "#282a36";
static const char selbordercolor[]      = "#bd93f9";
static const char selfgcolor[]          = "#bd93f9"; /* 2 */
static const char purple[]              = "#bd93f9"; /* 3 */
static const char green[]               = "#50fa7b"; /* 4 */
static const char orange[]              = "#ffb86c"; /* 5 */
static const char red[]                 = "#ff5555"; /* 6 */
static const char yellow[]              = "#f1fa8c"; /* 7 */
static const char pink[]                = "#ff79c6"; /* 8 */
static const char cyan[]                = "#8be9fd"; /* 9 */
static const char *colors[][9]          = {
	/*                  fg           bg           border          */
	[SchemeNorm]    = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]     = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemePurple]  = { purple,      normbgcolor, normbordercolor },
	[SchemeGreen]   = { green,       normbgcolor, normbordercolor },
	[SchemeOrange]  = { orange,      normbgcolor, normbordercolor },
	[SchemeRed]     = { red,         normbgcolor, normbordercolor },
	[SchemeYellow]  = { yellow,      normbgcolor, normbordercolor },
	[SchemePink]    = { pink,        normbgcolor, normbordercolor },
	[SchemeCyan]    = { cyan,        normbgcolor, normbordercolor },
};
static const unsigned int alphas[][9]   = {
	/*                  fg      bg    border */
	[SchemeNorm]    = { OPAQUE, 0xd9, OPAQUE },
	[SchemeSel]     = { OPAQUE, 0xd9, OPAQUE },
	[SchemePurple]  = { OPAQUE, 0xd9, OPAQUE },
	[SchemeGreen]   = { OPAQUE, 0xd9, OPAQUE },
	[SchemeOrange]  = { OPAQUE, 0xd9, OPAQUE },
	[SchemeRed]     = { OPAQUE, 0xd9, OPAQUE },
	[SchemeYellow]  = { OPAQUE, 0xd9, OPAQUE },
	[SchemePink]    = { OPAQUE, 0xd9, OPAQUE },
	[SchemeCyan]    = { OPAQUE, 0xd9, OPAQUE },
};

static const unsigned int tagalpha[] = { OPAQUE, 0xd9 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tagsel[][2] = {
	{ "#f8f8f2", purple    },
	{ "#f8f8f2", pink      },
	{ "#f8f8f2", red       },
	{ "#f8f8f2", orange    },
	{ "#282a36", yellow    },
	{ "#282a36", green     },
	{ "#282a36", cyan      },
	{ "#282a36", "#f8f8f2" },
	{ "#f8f8f2", "#6272a4" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *    WM_CLASS(STRING) = instance, class
	 *    WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "dummy",    NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile }, /* first entry is default */
	{ "TTT",      bstack },
	{ "><>",      NULL }, /* no layout function means floating behavior */
	{ NULL,       NULL }, /* this is for the cyclelayout patch */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } */

static const Key keys[] = {
	/* modifier              key                       function          argument */
	{ MODKEY|ShiftMask,      XK_b,                     togglebar,        {0} },
	{ MODKEY,                XK_f,                     togglefullscr,    {0} },
	{ MODKEY,                XK_j,                     focusstack,       {.i = +1 } },
	{ MODKEY,                XK_k,                     focusstack,       {.i = -1 } },
	{ MODKEY,                XK_i,                     incnmaster,       {.i = +1 } },
	{ MODKEY,                XK_o,                     incnmaster,       {.i = -1 } },
	{ MODKEY,                XK_h,                     setmfact,         {.f = -0.05} },
	{ MODKEY,                XK_l,                     setmfact,         {.f = +0.05} },
	{ MODKEY|ShiftMask,      XK_Return,                zoom,             {0} },
	{ MODKEY|ShiftMask,      XK_j,                     zoom,             {0} },
	{ MODKEY|ShiftMask,      XK_k,                     zoom,             {0} },
	{ MODKEY,                XK_Tab,                   view,             {0} },
	{ MODKEY|ShiftMask,      XK_q,                     killclient,       {0} },
	{ MODKEY,                XK_space,                 cyclelayout,      {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_space,                 togglefloating,   {0} },
	{ MODKEY,                XK_0,                     view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,      XK_0,                     tag,              {.ui = ~0 } },
	{ MODKEY,                XK_comma,                 focusmon,         {.i = -1 } },
	{ MODKEY,                XK_period,                focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_comma,                 tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_period,                tagmon,           {.i = +1 } },
	TAGKEYS(                 XK_1,                                       0)
	TAGKEYS(                 XK_2,                                       1)
	TAGKEYS(                 XK_3,                                       2)
	TAGKEYS(                 XK_4,                                       3)
	TAGKEYS(                 XK_5,                                       4)
	TAGKEYS(                 XK_6,                                       5)
	TAGKEYS(                 XK_7,                                       6)
	TAGKEYS(                 XK_8,                                       7)
	TAGKEYS(                 XK_9,                                       8)
	{ MODKEY|ShiftMask,      XK_e,                     quitprompt,       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        cyclelayout,    {.i = +1 } },
	/* { ClkWinTitle,          0,                Button2,        zoom,           {0} }, */
	/* { ClkStatusText,        0,                Button2,        spawn,          {.v = termcmd } }, */
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};
