/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu Sans Mono:size=12" };
static const char dmenufont[]       = "DejaVu Sans Mono:size=12";

static const char col_black[]       = "#000000";
static const char col_green[]       = "#00ee00";
static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_green, col_black, col_green},
        [SchemeSel]  = { col_black, col_green,  col_green},
        [SchemeTitle] = { col_green, col_black, col_green},
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { " CO ", " PO ", "term", "web", "chat", "rand" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       	tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       	0,            1,           -1 },
	{ NULL,				NULL,		"USR_WIN10-IT (CO)",	    1 << 0,		  0,		   -1 },
	{ NULL,				NULL,		"USR-WIN10-IT",	1 << 1,		  0,		   -1 },
	{ "screen-256color",	NULL,	NULL,    		1 << 2,		  0,		   -1 },
	//{ NULL,				NULL,		"st",    		1 << 2,		  0,		   -1 },
	{ "st-256color",	NULL,		NULL,    		1 << 2,		  0,		   -1 },
	{ "XTerm",			NULL,		NULL,    		1 << 2,		  0,		   -1 },
	{ "Xfce4-terminal",			NULL,		NULL,    		1 << 2,		  0,		   -1 },
	{ "Firefox",	NULL,       NULL,       	1 << 3,       0,           -1 },
	{ "Mattermost", 	NULL,  		NULL,       	1 << 4,		  0,		   -1 },
	{ "Signal", 		NULL,		NULL,       	1 << 4,		  0,		   -1 },
	{ "Bitwarden", 		NULL,		NULL,       	1 << 5,		  0,		   -1 },
	{ "Steam", 		NULL,		NULL,       	1 << 5,		  0,		   -1 },
	{ "Zathura", 		NULL,		NULL,       	1 << 5,		  0,		   -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
//static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[]=",      tile },    
	{ "[W]",      monocle }, 
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define XF86MonBrightnessUp 0x1008ff02
#define XF86MonBrightnessDown 0x1008ff03

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char dmenuprompt[] = ">";
 static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_green, "-sb", col_green, "-sf", col_black, "-p", dmenuprompt, NULL };


/* commands */
static const char *termcmd[]  	= { "dwm_terminal.sh",	 		NULL };
static const char *audioup[] 	= { "audio_up.sh", 			NULL };
static const char *audiodown[] 	= { "audio_down.sh", 		NULL };
static const char *audiomute[] 	= { "audio_mute.sh", 		NULL };
static const char *scrot[] 		= { "dwm_scrot.sh",				NULL };
static const char *screenlock[] = { "dwm_lock.sh",				NULL };
static const char *mpcplay[]	= { "mpc_play.sh",				NULL };
static const char *mpcnext[]	= { "mpc_next.sh",				NULL };
static const char *mpcprev[]	= { "mpc_prev.sh",				NULL };
static const char *mpcrand[]	= { "mpc_rand.sh",				NULL };
static const char *xbup[]		= { "xbacklight_inc.sh",		NULL };
static const char *xbdown[]		= { "xbacklight_dec.sh",		NULL };
static const char *click[]		= { "click.sh",			NULL };

static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_p,      		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 		spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F11,    		togglebar,      {0} },
	{ MODKEY,                       XK_j,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      		killclient,     {0} },
	{ MODKEY,                       XK_t,      		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_w,      		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      		setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	//TAGKEYS(                        XK_7,                      		6)
	//TAGKEYS(                        XK_8,                      		7)
	//TAGKEYS(                        XK_9,                      		8)
	{ MODKEY|ShiftMask,             XK_z,      		quit,           {0} },
	// custom
	{ MODKEY,						XK_equal,  		spawn,		   	{.v = audioup } },
	{ MODKEY,						XK_minus,  		spawn,		   	{.v = audiodown } },
	{ MODKEY,						XK_backslash,	spawn,	   		{.v = audiomute } },
	{ MODKEY|ShiftMask, 			XK_Print,  		spawn,		   	{.v = scrot } },
	{ ControlMask|MODKEY,			XK_l,			spawn,			{.v = screenlock } },
	{ MODKEY,						XK_m,			spawn,			{.v = mpcplay } },
	{ MODKEY,						XK_n,			spawn,			{.v = mpcnext } },
	{ MODKEY,						XK_b,			spawn,			{.v = mpcprev } },
	{ MODKEY,						XK_u,			spawn,			{.v = mpcrand } },
	{ 0,	XF86MonBrightnessUp,					spawn,			{.v = xbup } },
	{ 0, XF86MonBrightnessDown,					spawn,			{.v = xbdown } },
	{ ControlMask|MODKEY,			XK_i,			spawn,			{.v = click } },
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
