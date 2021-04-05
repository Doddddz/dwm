/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int smartgraps         = 1;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=14" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#37474f";
static const char col_border[]      = "#42a5f5";

static const char col_nordfg[]        = "#434C5E";
static const char col_nordbg[]        = "#D8DEE9";
static const char col_nordborder[]    = "#D8DEE9";

static const char col_nordfgSel[]     = "#434C5E";
static const char col_nordbgSel[]     = "#88C0D0";
static const char col_nordborderSel[] = "#88C0D0";

static const char *colors[][3]      = {
	/*               fg              bg              border   */
	[SchemeNorm] = { col_nordfg,     col_nordbg,     col_nordborder },
	[SchemeSel]  = { col_nordfgSel,  col_nordbgSel,  col_nordborderSel  },
    [SchemeHid]  = { col_cyan,       col_nordfg,     col_cyan  },
};

static const unsigned int alphas[][3]      = {
   /*               fg      bg        border     */
   [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
   [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *termcmd[]  = { "konsole", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "konsole", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_Left,   viewtoleft,     {0} }, /* 切换标签 */
    { MODKEY,                       XK_Right,  viewtoright,    {0} },
    { MODKEY|ShiftMask,             XK_Left,   tagtoleft,      {0} }, /* 放到别的标签中 */                    
    { MODKEY|ShiftMask,             XK_Right,  tagtoright,     {0} },

	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } }, /* 创建浮动窗口 */ 

    { MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } }, /* 将 window 提升为 Main window */
    { MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },

    { MODKEY,                       XK_k,      focusstackvis,  {.i = +1 } }, /* swesomebar */
    { MODKEY,                       XK_j,      focusstackvis,  {.i = -1 } },
    // { MODKEY|ControlMask,           XK_j,      focusstackhid,  {.i = +1 } },
    // { MODKEY|ControlMask,           XK_k,      focusstackhid,  {.i = -1 } },

    // { MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, /* 切换焦点 */
    // { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } }, /* 切换布局 */

	{ MODKEY,                       XK_minus,  setmfact,       {.f = -0.05} }, /* 改变窗体长度 */
    { MODKEY,                       XK_equal,  setmfact,       {.f = +0.05} },

    { MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } }, /* 窗口间隔 */
    { MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
       
    { MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
    { MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
    { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
    { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
    { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
    { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, /* to there */

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[0]} },/* 三种视图模式 */
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       XK_space,  setlayout,      {0} }, /* 伪全屏 */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY,                       XK_f,      togglefullscr,  {0} }, /* 全屏 */

    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_s,      show,           {0} }, /* 暂时隐藏标签 */
    { MODKEY,                       XK_h,      hide,           {0} },
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,          {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

