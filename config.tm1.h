/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = 
    { "Fira Code:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = 
    "Fira Code:size=12:antialias=true:autohint=true";

static const char col_black[]      = "black";
static const char col_white[]      = "gray90";
static const char col_gray[]       = "gray50";
static const char col_field[]      = "#8959a8";
static const char col_border[]     = "#eab700";

// DARK
static const char *colors[][3]      = {
        /*               fg          bg         border   */
        [SchemeNorm]  = { col_white, col_black, col_gray},
        [SchemeInv]   = { col_white, col_black,  col_black},
        [SchemeSel]   = { col_white, col_field,  col_border},
};


/* tagging */
static const char *tags[] = {"1","2","3","4","5","6","7","8","9","0"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance title       	tagsMask  float  monitor */
	{ "xterm-16color",  NULL,	 NULL,    		0,	        0,    -1 },
	{ "Microsoft-edge", NULL,    NULL,          1 << 3,     0,    -1 },
	{ "Slack",          NULL,    NULL,          1 << 3,     0,    -1 },
    { "zoom",           NULL,    NULL,          1 << 3,     0,    -1 },
	{ "Bitwarden", 		NULL,	 NULL,       	1 << 4,     0,    -1 },
	{ "1Password", 		NULL,	 NULL,       	1 << 4,     0,    -1 },
	{ "Nxplayer.bin",   NULL,    NULL,          1 << 5,     0,    -1 },
	{ "firefox",        NULL,    NULL,       	0,          0,    -1 },
	{ "Signal", 		NULL,	 NULL,          1 << 7,     0,    -1 },
    { NULL,             NULL,    "HandBrake",   1 << 8,     0,    -1 },
	{ "Zathura", 		NULL,	 NULL,          1 << 8,     0,    -1 },
    { "feh",            NULL,    NULL,          1 << 8,     0,    -1 },
    { "libreoffice",    NULL,    NULL,          1 << 8,     0,    -1 },
    { NULL,             NULL,    "LibreOffice", 1 << 8,     0,    -1 },
	{ "Steam", 		    NULL,	 NULL,       	1 << 9,     0,    -1 },
	{ "steam", 		    NULL,	 NULL,       	1 << 9,     0,    -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
//static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[]=",      tile },    
	{ "[W]",      monocle }, 
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_field, "-sf", col_white, "-p", dmenuprompt, NULL };


/* commands */
static const char *termcmd[]  	  = { "dwm_terminal.sh",	NULL };
//static const char *termcmd[]  	  = { "tdrop.sh",	NULL };
static const char *audioup[] 	  = { "audio_up.sh", 		NULL };
static const char *audiodown[] 	  = { "audio_down.sh", 		NULL };
static const char *audiomute[] 	  = { "audio_mute.sh", 		NULL };
static const char *screenlock[]   = { "dwm_lock.sh",		NULL };
static const char *mpcplay[]	  = { "mpc_play.sh",		NULL };
static const char *mpcnext[]	  = { "mpc_next.sh",		NULL };
static const char *mpcprev[]	  = { "mpc_prev.sh",		NULL };
static const char *mpcrand[]	  = { "mpc_rand.sh",		NULL };
static const char *print_screen[] = { "print_screen.sh",    NULL };
static const char *area_screen[]  = { "area_screen.sh",     NULL };
static const char *clipmenu[]  = { "clipmenu_dwm.sh",     NULL };

static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_p,      		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 		spawn,           {.v = termcmd } },
	//{ MODKEY|ShiftMask,             XK_Return, 		view,           {.ui = 1 << 2 } },
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
	{ MODKEY,                       XK_r,      		setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_e,      		setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	//{ MODKEY,                       XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,	tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusnthmon,       {.i = 0 } },
	{ MODKEY,                       XK_period, 		focusnthmon,       {.i = 1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagnthmon,         {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagnthmon,         {.i = 1 } },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	TAGKEYS(                        XK_7,                      		6)
	TAGKEYS(                        XK_8,                      		7)
	TAGKEYS(                        XK_9,                      		8)
    TAGKEYS(                        XK_0,                           9)
	{ MODKEY|ShiftMask,             XK_z,      		quit,           {0} },
	// custom
	{ MODKEY,						XK_equal,  		spawn,		   	{.v = audioup } },
	{ MODKEY,						XK_minus,  		spawn,		   	{.v = audiodown } },
	{ MODKEY,						XK_backslash,	spawn,	   		{.v = audiomute } },
	{ 0,	                        XK_Print,  		spawn,		   	{.v = area_screen } },
	{ ShiftMask,                    XK_Print,  		spawn,		   	{.v = print_screen } },
	{ MODKEY,	                    XK_F9,  		spawn,		   	{.v = area_screen } },
	{ MODKEY|ShiftMask,             XK_F9,  		spawn,		   	{.v = print_screen } },
	{ ControlMask|MODKEY,			XK_l,			spawn,			{.v = screenlock } },
	{ MODKEY,						XK_m,			spawn,			{.v = mpcplay } },
	{ MODKEY,						XK_n,			spawn,			{.v = mpcnext } },
	{ MODKEY,						XK_b,			spawn,			{.v = mpcprev } },
	{ MODKEY,						XK_u,			spawn,			{.v = mpcrand } },
	{ MODKEY|ShiftMask,             XK_p,  		    spawn,		   	{.v = clipmenu } },
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

