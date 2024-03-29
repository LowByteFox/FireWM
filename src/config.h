#ifndef CONFIG_H
#define CONFIG_H
/* See LICENSE.dwm file for copyright and license details. */

#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
#define BARPADDING_PATCH

#include <X11/XF86keysym.h>
#include <X11/keysymdef.h>
#include "firewm.h"
#include "ipc.h"

/* appearance */
unsigned int borderpx   = 1;        /* border pixel of windows */
unsigned int gappx      = 10;       /* gaps between windows */
unsigned int barpadding = 0;
unsigned int snap       = 32;       /* snap pixel */
int showbar             = 1;        /* 0 means no bar */
int topbar              = 1;        /* 0 means bottom bar */
char *buttonbar         = "#";
int user_bh             = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
int showsystray        = 1;   /* 0 means no systray */
static const int scalepreview       = 4;        /* tag preview scaling */
int corner_radius      = 0;   /* Radius of corners */

static const char *fonts[]          = { "Sans Serif:style=Bold:size=13" };
static const char dmenufont[]       = "Sans Serif:size=13";

/*
A - App button
T - Tags
L - layout
n - title
s - status
S - systray
*/

char barlayout[7] = "ATLnsS";
char center = '0';  /* Which "widget" should be in the center */

char bar_background[]    = "#222222";
char col_defborder[]     = "#444444";
char foreground[]        = "#bbbbbb";
char active_foreground[] = "#eeeeee";
char col_activebar[]     = "#0055aa";
char col_border[]        = "#0055aa";
char barfg[]			 = "#FFFFFF";
char barbg[]			 = "#000000";
char bar_btnfg[]         = "#FFFFFF";
char titlefg[]           = "#FFFFFF";
char systraybg[]         = "#000000";

char tagfgs[9][8] = {
	"#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF"
};  /* fg of tags */

char active_tagfgs[9][8] = {
	"#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF"
};  /* fg of active tag */


int tag_count = 5;
int showicon = 1;

char terminalEmulator[FILENAME_MAX] = "st";  /* terminal emulator executable */

static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

const unsigned int baralpha = 245;
static const unsigned int borderalpha = 255;

static const char *colors[][3]      = {
	/*               fg                 bg              border   */
	[SchemeNorm] = { foreground,        bar_background, col_defborder },
	[SchemeSel]  = { active_foreground, col_activebar,  col_border    }
};

static unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, 245, 255 },
	[SchemeSel]  = { OPAQUE, 245, 255 }
};

/* tagging */
const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     "Gimp",     NULL,       0,            1,           -1 },
	{ "Plank",    NULL,       NULL,       (1 << 9) - 1, 1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle }
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *roficmd[] = {"/home/jani/.config/rofi/launchers/type-1/launcher.sh", NULL};
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bar_background, "-nf", foreground, "-sb", col_activebar, "-sf", active_foreground, NULL };
static const char *termcmd[]  = { terminalEmulator, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0] } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1] } },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2] } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglealwaysontop, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
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
	{ MODKEY,                       XK_o,      winview,        {0} },
	{ MODKEY|ControlMask,			XK_r,      quit,           {1} }, 
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkButton,		    0,		        Button1,	    spawn,		    {.v = roficmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  firesetalpha,        1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  firesetgaps,         1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  firesetbarcolor,     1,      {ARG_TYPE_STR}    ),
  IPCCOMMAND(  firesetbordercolor,  1,      {ARG_TYPE_STR}    ),
  IPCCOMMAND(  firesetbarlayout,    1,      {ARG_TYPE_STR}    ),
  IPCCOMMAND(  firesetbarcenter,    1,      {ARG_TYPE_STR}    ),
  IPCCOMMAND(  firesetbarpadding,      1,      {ARG_TYPE_UINT}   )
};

#endif
