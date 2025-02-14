
/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx	    = 6;
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:size=11", "Siji:size=11", "FontAwesome:size=9" };
static const char dmenufont[]       = "Droid Sans:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { "#9acd32", col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { "#9acd32", col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1  ", "2  ", "3  ", "4  ", "5  ", "6  ", "7  ", "8  ", "9  " };
static const char *new_tags[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Google-chrome",  NULL,       NULL,       2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *browsercmd[]  = { "google-chrome-stable", NULL };
static const char scratchpadname[] = "st 终端";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY, 	                XK_x, spawn,               {.v = termcmd } },
	{ MODKEY, 	                XK_Return, spawn,          SHCMD("st") },
	{ MODKEY|ShiftMask, 	        XK_s, spawn,               SHCMD("prompt \"关机?\" \"systemctl poweroff\"") },
	{ MODKEY|ShiftMask, 	        XK_e, spawn,               SHCMD("prompt \"休眠?\" \"systemctl hibernate\"") },
	{ MODKEY|ShiftMask, 	        XK_r, spawn,               SHCMD("prompt \"重启?\" \"systemctl reboot\"") },
	{ MODKEY, 	                XK_w,	   spawn,          {.v = browsercmd } },
        { MODKEY,                       XK_bracketleft,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,	                XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_u,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      tagmon,         {.i = -1 } },
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
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },

	{ 0,	XF86XK_AudioMute,	spawn,		SHCMD("amixer sset Master toggle ; pkill -RTMIN+10 dwmblocks") },
	{ 0,	XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer sset Master 5%+ ; pkill -RTMIN+10 dwmblocks") },
	{ 0,	XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer sset Master 5%- ; pkill -RTMIN+10 dwmblocks") },
	{ 0,	XF86XK_AudioPrev,	spawn,		SHCMD("mpc prev") },
	{ 0,	XF86XK_AudioNext,	spawn,		SHCMD("mpc next") },
	{ 0,	XF86XK_AudioPause,	spawn,		SHCMD("mpc pause") },
	{ 0,	XF86XK_AudioPlay,	spawn,		SHCMD("mpc play") },
	{ 0,	XF86XK_AudioStop,	spawn,		SHCMD("mpc stop") },
	{ 0,	XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0,	XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0,	XF86XK_AudioMedia,	spawn,		SHCMD("st -e ncmpcpp") },
	{ 0,	XF86XK_PowerOff,	spawn,		SHCMD("prompt \"Shutdown computer?\" \"sudo -A shutdown -h now\"") },
	{ 0,	XF86XK_Calculator,	spawn,		SHCMD("st -e bc -l") },
/*
	{ 0,	XF86XK_Sleep,		spawn,		SHCMD("prompt \"Hibernate computer?\" \"sudo -A zzz -Z\"") },
*/
	{ 0,	XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0,	XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0,	XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0,	XF86XK_TaskPane,	spawn,		SHCMD("st -e htop") },
	{ 0,	XF86XK_Mail,		spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0,	XF86XK_MyComputer,	spawn,		SHCMD("st -e $FILE /") },
	{ 0,	XF86XK_Battery,		spawn,		SHCMD("notify-send \"Battery status\" \"$(batstat)\"") },
	{ 0,	XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0,	XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,	XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0,	XF86XK_TouchpadOn,	spawn,		SHCMD("synclient TouchpadOff=0") },
/*
	{ 0,	XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0,	XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },

*/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

