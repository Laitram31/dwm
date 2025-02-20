/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 5;        /* snap pixel */
static unsigned int gaps      = 8;       /* gaps pixel */
static int enablegaps         = 1;        /* 0 means no gaps */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh	= 30;
static int barborders         = 1;        /* 0 means no borders in bar */
static const int alpha		= 0xec;
static const char *fonts[]    = {
	"Cousine:size=12", /* this is for nerd font icons with cousine nerd font */
	"monospace:size=17"
};
static char normbgcolor[]         = "#282a36";
static char normbordercolor[]     = "#ebdbb2";
static char normfgcolor[]         = "#ebdbb2"; /* 1 */
static char selbgcolor[]          = "#282a36";
static char selbordercolor[]      = "#ff8c69";
static char selfgcolor[]          = "#ffc0cb"; /* 2 */
static char blue[]                = "#458588"; /* 3 (purple in dracula theme) */
static char green[]               = "#b8bb26"; /* 4 */
static char orange[]              = "#fe8019"; /* 5 */
static char red[]                 = "#cc241d"; /* 6 */
static char yellow[]              = "#fabd2f"; /* 7 */
static char magenta[]             = "#b16286"; /* 8 (pink in dracula theme) */
static char cyan[]                = "#689D6A"; /* 9 */
static char last[]                = "#6272a4";
static char *colors[][3]          = {
	/*                  fg           bg           border          */
	[SchemeNorm]    = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]     = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeBlue]    = { blue,        normbgcolor, normbordercolor },
	[SchemeGreen]   = { green,       normbgcolor, normbordercolor },
	[SchemeOrange]  = { orange,      normbgcolor, normbordercolor },
	[SchemeRed]     = { red,         normbgcolor, normbordercolor },
	[SchemeYellow]  = { yellow,      normbgcolor, normbordercolor },
	[SchemeMagenta] = { magenta,      normbgcolor, normbordercolor },
	[SchemeCyan]    = { cyan,        normbgcolor, normbordercolor },
};
static const unsigned int alphas[][3]   = {
	/*                  fg      bg    border */
	[SchemeNorm]    = { OPAQUE, alpha, OPAQUE },
	[SchemeSel]     = { OPAQUE, alpha, OPAQUE },
	[SchemeBlue]    = { OPAQUE, alpha, OPAQUE },
	[SchemeGreen]   = { OPAQUE, alpha, OPAQUE },
	[SchemeOrange]  = { OPAQUE, alpha, OPAQUE },
	[SchemeRed]     = { OPAQUE, alpha, OPAQUE },
	[SchemeYellow]  = { OPAQUE, alpha, OPAQUE },
	[SchemeMagenta] = { OPAQUE, alpha, OPAQUE },
	[SchemeCyan]    = { OPAQUE, alpha, OPAQUE },
};

static const unsigned int tagalpha[] = { OPAQUE, alpha };

/* tagging */
static const char *tags[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };

static char *tagsel[][2] = {
	{ normfgcolor, blue },
	{ normfgcolor, magenta },
	{ normfgcolor, red },
	{ normfgcolor, orange },
	{ normbgcolor, yellow },
	{ normbgcolor, green },
	{ normbgcolor, cyan },
	{ normbgcolor, normfgcolor },
	{ normfgcolor, last },
};

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
	{ "borderpx",         INTEGER, &borderpx },
	{ "snap",             INTEGER, &snap },
	{ "gaps",             INTEGER, &gaps },
	{ "enablegaps",       INTEGER, &enablegaps }, /* bool */
	{ "showbar",          INTEGER, &showbar },    /* bool */
	{ "topbar",           INTEGER, &topbar },     /* bool */
	{ "barborders",       INTEGER, &barborders }, /* bool */
	{ "normbgcolor",      STRING,  &normbgcolor },
	{ "normbordercolor",  STRING,  &normbordercolor },
	{ "normfgcolor",      STRING,  &normfgcolor },
	{ "selbgcolor",       STRING,  &selbgcolor },
	{ "selbordercolor",   STRING,  &selbordercolor },
	{ "selfgcolor",       STRING,  &selfgcolor },
	{ "color4",           STRING,  &blue },
	{ "color2",           STRING,  &green },
	{ "orange",           STRING,  &orange },
	{ "color1",           STRING,  &red },
	{ "color3",           STRING,  &yellow },
	{ "color5",           STRING,  &magenta },
	{ "color6",           STRING,  &cyan },
	{ "last",             STRING,  &last }
};

static const Rule rules[] = {
	/* xprop(1):
	 *    WM_CLASS(STRING) = instance, class
	 *    WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating		canfocus	 monitor */
	{ "arttime",    NULL,       NULL,       1,       1,           1,	-1},
	{ NULL,		NULL,		"mpv",	1,	1,		1,	-1},
	{ NULL,		NULL,	"GLava",	1,	1,	0,	-1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ "[]=",     tile }, /* first entry is default */
	{ "TTT",     bstack },
	{ "><>",     NULL }, /* no layout function means floating behavior */
	{ NULL,      NULL }, /* this is for the cyclelayout patch */
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
	/* modifier            key            function          argument */
	{ MODKEY|ShiftMask,    XK_b,          togglebar,        {0} },
	{ MODKEY,              XK_f,          togglefullscr,    {0} },
	{ MODKEY,              XK_j,          focusstack,       {.i = +1 } },
	{ MODKEY,              XK_k,          focusstack,       {.i = -1 } },
	{ MODKEY,              XK_i,          incnmaster,       {.i = +1 } },
	{ MODKEY,              XK_o,          incnmaster,       {.i = -1 } },
	{ MODKEY,              XK_h,          setmfact,         {.f = -0.05} },
	{ MODKEY,              XK_l,          setmfact,         {.f = +0.05} },
	{ MODKEY|ShiftMask,    XK_g,          togglegaps,       {0} },
	{ MODKEY|ShiftMask,    XK_Return,     zoom,             {0} },
	{ MODKEY|ShiftMask,    XK_j,          zoom,             {0} },
	{ MODKEY|ShiftMask,    XK_k,          zoom,             {0} },
	{ MODKEY,              XK_Tab,        view,             {0} },
	{ MODKEY|ShiftMask,    XK_q,          killclient,       {0} },
	{ MODKEY,              XK_space,      togglefloating,   {0} },
	{ MODKEY|ShiftMask,    XK_space,      cyclelayout,      {.i = +1 } },
	{ MODKEY,              XK_agrave,          view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_agrave,          tag,              {.ui = ~0 } },
	{ MODKEY,              XK_comma,      focusmon,         {.i = -1 } },
	{ MODKEY,              XK_semicolon,     focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,      tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_semicolon,     tagmon,           {.i = +1 } },
	TAGKEYS(               XK_ampersand,                            0)
	TAGKEYS(               XK_eacute,                            1)
	TAGKEYS(               XK_quotedbl,                            2)
	TAGKEYS(               XK_apostrophe,                            3)
	TAGKEYS(               XK_parenleft,                            4)
	TAGKEYS(               XK_minus,                            5)
	TAGKEYS(               XK_egrave,                            6)
	TAGKEYS(               XK_underscore,                            7)
	TAGKEYS(               XK_ccedilla,                            8)
	{ MODKEY|ShiftMask,    XK_e,          quitprompt,       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click             event mask        button      function        argument */
	{ ClkLtSymbol,       0,                Button1,    cyclelayout,    {.i = +1 } },
	/* { ClkWinTitle,       0,                Button2,    zoom,           {0} }, */
	/* { ClkStatusText,     0,                Button2,    spawn,          {.v = termcmd } }, */
	{ ClkClientWin,      MODKEY,           Button1,    movemouse,      {0} },
	{ ClkClientWin,      MODKEY|ShiftMask, Button1,    resizemouse,    {0} },
	{ ClkClientWin,      MODKEY,           Button2,    togglefloating, {0} },
	{ ClkClientWin,      MODKEY,           Button3,    resizemouse,    {0} },
	{ ClkTagBar,         0,                Button1,    view,           {0} },
	{ ClkTagBar,         0,                Button3,    toggleview,     {0} },
	{ ClkTagBar,         MODKEY,           Button1,    tag,            {0} },
	{ ClkTagBar,         MODKEY,           Button3,    toggletag,      {0} },
};
