/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 15;       /* snap pixel */
static const unsigned int step      = 25;       /* resize step */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 4;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = {
    "monospace:size=9:weight=heavy",
    "Font Awesome 7 Free Solid:size=9",
    "Font Awesome 7 Free Regular:size=9",
    "Material Icons:pixelsize=15:antialias=true",
    "Material Design Icons:pixelsize=15:antialias=true",
};
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray2shade[]  = "#222222";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyanshade[]   = "#173542";
static const char *colors[][ColLast]      = {
	/*               fg         bg         bg_shade        border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2shade, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyanshade,  col_cyan  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" }; */
static const char *tags[] = {"󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶"};
// static const char *tags[] = {"󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶", "󰎹", "󰎼"};

#define RULE(...) { .monitor = -1, ##__VA_ARGS__ }

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class, instance, title, tags, isterminal, noswallow, iscentered, isfakefullscreen, isfloating, nopreserve, monitor } */
	/* { .class = "Firefox", .tags = 1<<5, .noswallow = -1, .isfakefullscreen = 1, .monitor = -1 }, */
	RULE( .class = "Chromium", .noswallow = -1, .isfakefullscreen = 1 ),
	RULE( .class = "TelegramDesktop", .nopreserve = 1 ),
	RULE( .class = "st-256color", .isterminal = 1 ),
	RULE( .instance = "noswallow", .isterminal = 0 ),
	RULE( .instance = "popup-center", .iscentered = 1, .isfloating = 1 ),
	RULE( .class = "Dragon-drop",     .iscentered = 1, .isfloating = 1 ),
	RULE( .title = "Volume Control",  .iscentered = 1, .isfloating = 1 ),
	RULE( .title = "Microsoft Teams Notification", .isfloating = 1 ),
	RULE( .title = "Event Tester", .noswallow = 1 ), /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol arrange function  */
	{ "󰙀", tile },    /* first entry is default */
	{ "", monocle },
	{ "󰌨", deck },
	{ "󰀽", NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *menucmd[] = { "/bin/sh", "-c", "if command -v fmenu_run; then fmenu_run; else dmenu_run; fi", NULL };
static const char *termcmd[]  = { "st", NULL };

/* for XF86XK_* keys */
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function              argument */
	{ MODKEY,                       XK_d,      spawn,                {.v = menucmd } },
	{ MODKEY,                       XK_Return, spawn,                {.v = termcmd } },
	{ MODKEY,                       XK_q,      killclient,           {0} },
	{ MODKEY,                       XK_j,      focusstack,           {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,             {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,               {0} },
	{ MODKEY|ControlMask,           XK_j,      focusmon,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_k,      focusmon,             {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_j,      tagmon,               {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      tagmon,               {.i = +1 } },
	{ MODKEY,                       XK_space,  zoom,                 {0} },
	{ MODKEY,                       XK_h,      setmfact,             {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,             {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,             {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,             {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,             {.f =  0.00} },
	{ MODKEY,                       XK_i,      incnmaster,           {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,           {.i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,            {0} },
	{ MODKEY,                       XK_t,      setlayout,            {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,            {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      setlayout,            {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,            {.v = &layouts[3]} },
	{ MODKEY,                       XK_Tab,    view,                 {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,       {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_0,      view,                 {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,                  {.ui = ~0 } },
	{ MODKEY,                       XK_F2,     quit,                 {0} },
	{ MODKEY|ControlMask,           XK_comma,  focusmon,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, focusmon,             {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_comma,  tagmon,               {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_period, tagmon,               {.i = +1 } },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	// TAGKEYS(                        XK_8,                             7)
	// TAGKEYS(                        XK_9,                             8)
	{ MODKEY,                       XK_Down,   moveresize,           {.v = (const int []){ 0,  1,  0,  0 }}},
	{ MODKEY,                       XK_Up,     moveresize,           {.v = (const int []){ 0, -1,  0,  0 }}},
	{ MODKEY,                       XK_Right,  moveresize,           {.v = (const int []){ 1,  0,  0,  0 }}},
	{ MODKEY,                       XK_Left,   moveresize,           {.v = (const int []){-1,  0,  0,  0 }}},
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,           {.v = (const int []){ 0,  0,  0,  1 }}},
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,           {.v = (const int []){ 0,  0,  0, -1 }}},
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,           {.v = (const int []){ 0,  0,  1,  0 }}},
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,           {.v = (const int []){ 0,  0, -1,  0 }}},
	{ 0,                  XF86XK_AudioPause,   spawn,                {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0,                  XF86XK_AudioPlay,    spawn,                {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0,                  XF86XK_AudioStop,    spawn,                {.v = (const char*[]){ "playerctl", "stop", NULL } } },
	{ 0,                  XF86XK_AudioNext,    spawn,                {.v = (const char*[]){ "playerctl", "next", NULL } } },
	{ 0,                  XF86XK_AudioPrev,    spawn,                {.v = (const char*[]){ "playerctl", "previous", NULL } } },
	{ 0,                  XF86XK_AudioForward, spawn,                {.v = (const char*[]){ "playerctl", "position", "10+", NULL } } },
	{ 0,                  XF86XK_AudioRewind,  spawn,                {.v = (const char*[]){ "playerctl", "position", "10-", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button4,        setlayout,      {.v = &layouts[3]} },
	{ ClkLtSymbol,          0,              Button5,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = (const char*[]){ "dunsttoggle", NULL } } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = (const char*[]){ "dunstdate", "curr", NULL } } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = (const char*[]){ "dunstdate", "prev", NULL } } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = (const char*[]){ "dunstdate", "next", NULL } } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

// vim:noexpandtab:
