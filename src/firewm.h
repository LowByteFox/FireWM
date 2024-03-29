#ifndef FIREWM_H
#define FIREWM_H

#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <Imlib2.h>
#include <ctype.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#include <X11/extensions/shape.h>
#include <X11/Xft/Xft.h>
#include <json-c/json.h>

#include "drw.h"

/* macros */
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
#define CLEANMASK(mask)         (mask & ~(numlockmask|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
#define INTERSECT(x,y,w,h,m)    (MAX(0, MIN((x)+(w),(m)->wx+(m)->ww) - MAX((x),(m)->wx)) \
                               * MAX(0, MIN((y)+(h),(m)->wy+(m)->wh) - MAX((y),(m)->wy)))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
#define LENGTH(X)               (sizeof X / sizeof X[0])
#define TAGMASK					(((1 << LENGTH(tags)) - 1))
#define MOUSEMASK               (BUTTONMASK|PointerMotionMask)
#define WIDTH(X)                ((X)->w + 2 * (X)->bw)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw)
#define TEXTW(X)                (drw_fontset_getwidth(drw, (X)) + lrpad)
#define RESET_FG(Scheme)		(drw_clr_create(drw, &drw->scheme[ColFg], colors[Scheme][ColFg], alphas[Scheme][ColFg]))
#define RESET_BG(Scheme)		(drw_clr_create(drw, &drw->scheme[ColBg], colors[Scheme][ColBg], alphas[Scheme][ColBg]))
#define SET_BG(Scheme, color, alpha)   (drw_clr_create(drw, &drw->scheme[ColBg], color, alpha))
#define SET_FG(Scheme, color, alpha)   (drw_clr_create(drw, &drw->scheme[ColFg], color, alpha))

#define OPAQUE                  0xffU

#define SYSTEM_TRAY_REQUEST_DOCK    0
#define _NET_SYSTEM_TRAY_ORIENTATION_HORZ 0

/* XEMBED messages */
#define XEMBED_EMBEDDED_NOTIFY      0
#define XEMBED_WINDOW_ACTIVATE      1
#define XEMBED_FOCUS_IN             4
#define XEMBED_MODALITY_ON         10

#define XEMBED_MAPPED              (1 << 0)
#define XEMBED_WINDOW_ACTIVATE      1
#define XEMBED_WINDOW_DEACTIVATE    2

#define VERSION_MAJOR               0
#define VERSION_MINOR               0
#define XEMBED_EMBEDDED_VERSION (VERSION_MAJOR << 16) | VERSION_MINOR


/* enums */
enum { CurNormal, CurResize, CurMove, CurLast }; /* cursor */
enum { SchemeNorm, SchemeSel }; /* color schemes */
enum { NetSupported, NetSystemTray, NetSystemTrayOP, NetSystemTrayOrientation, NetSystemTrayVisual,
       NetWMName, NetWMIcon, NetWMState, NetWMCheck,
       NetWMFullscreen, NetActiveWindow, NetWMWindowType, NetWMWindowTypeDesktop, NetWMWindowTypeDock, NetSystemTrayOrientationHorz,
       NetWMWindowTypeDialog, NetClientList, NetLast }; /* EWMH atoms */
enum { Manager, Xembed, XembedInfo, XLast }; /* Xembed atoms */
enum { DWMTags, DWMLast };
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast }; /* default atoms */
enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkButton, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

typedef struct TagState TagState;
struct TagState {
	int selected;
	int occupied;
	int urgent;
};

typedef struct ClientState ClientState;
struct ClientState {
	int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
};

typedef union {
	long i;
	unsigned long ui;
	float f;
	const void *v;
} Arg;

typedef struct {
	unsigned int click;
	unsigned int mask;
	unsigned int button;
	void (*func)(const Arg *arg);
	Arg arg;
} Button;

typedef struct Monitor Monitor;
typedef struct Client Client;
struct Client {
	char name[256];
	float mina, maxa;
	int x, y, w, h;
	int oldx, oldy, oldw, oldh;
	int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
	int bw, oldbw;
	unsigned int tags;
	int isfixed, iscentered, isfloating, isalwaysontop, isurgent, neverfocus, oldstate, isfullscreen;
	int issteam;
	unsigned int icw, ich; Picture icon;
	Client *next;
	Client *snext;
	Monitor *mon;
	Window win;
	ClientState prevstate;
};

typedef struct {
	unsigned int mod;
	KeySym keysym;
	void (*func)(const Arg *);
	const Arg arg;
} Key;

typedef struct {
	const char *symbol;
	void (*arrange)(Monitor *);
} Layout;

typedef struct Pertag Pertag;
struct Monitor {
	char ltsymbol[16];
	char lastltsymbol[16];
	float mfact;
	int nmaster;
	int num;
	int by;               /* bar geometry */
	int mx, my, mw, mh;   /* screen size */
	int wx, wy, ww, wh;   /* window area  */
	int gappx;            /* gaps between windows */
	unsigned int seltags;
	unsigned int sellt;
	unsigned int tagset[2];
	TagState tagstate;
	int showbar;
	int topbar;
	Client *clients;
	Client *sel;
	Client *lastsel;
	Client *stack;
	Monitor *next;
	Window barwin;
    Window tagwin;
    int previewshow;
    Pixmap tagmap[9];
	const Layout *lt[2];
	const Layout *lastlt;
	int ltcur; /* current layout */
	Pertag *pertag;
};

typedef struct {
	const char *class;
	const char *instance;
	const char *title;
	unsigned int tags;
	int isfloating;
	int monitor;
} Rule;

typedef struct Systray Systray;
struct Systray {
	Window win;
	Client *icons;
};

void applyrules(Client *c);
int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact);
void arrange(Monitor *m);
void arrangemon(Monitor *m);
void attach(Client *c);
void attachstack(Client *c);
void buttonpress(XEvent *e);
void checkotherwm(void);
void cleanup(void);
void cleanupmon(Monitor *mon);
void clientmessage(XEvent *e);
void configure(Client *c);
void configurenotify(XEvent *e);
void configurerequest(XEvent *e);
Monitor *createmon(void);
void destroynotify(XEvent *e);
void detach(Client *c);
void detachstack(Client *c);
Monitor *dirtomon(int dir);
void drawbar(Monitor *m);
void drawbars(void);
void enternotify(XEvent *e);
void expose(XEvent *e);
void focus(Client *c);
void focusin(XEvent *e);
void focusmon(const Arg *arg);
void focusstack(const Arg *arg);
Atom getatomprop(Client *c, Atom prop);
Picture geticonprop(Window w, unsigned int *icw, unsigned int *ich);
int getrootptr(int *x, int *y);
long getstate(Window w);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
unsigned int getsystraywidth();
void grabbuttons(Client *c, int focused);
void grabkeys(void);
int ispanel(Client *c);
int handlexevent(struct epoll_event *ev);
void incnmaster(const Arg *arg);
void keypress(XEvent *e);
void killclient(const Arg *arg);
void manage(Window w, XWindowAttributes *wa);
void mappingnotify(XEvent *e);
void maprequest(XEvent *e);
void monocle(Monitor *m);
void motionnotify(XEvent *e);
void movemouse(const Arg *arg);
Client *nexttiled(Client *c);
void pop(Client *);
void propertynotify(XEvent *e);
void quit(const Arg *arg);
Monitor *recttomon(int x, int y, int w, int h);
void resize(Client *c, int x, int y, int w, int h, int interact);
void resizeclient(Client *c, int x, int y, int w, int h);
void resizemouse(const Arg *arg);
void removesystrayicon(Client *i);
void resizerequest(XEvent *e);
void restack(Monitor *m);
void run(void);
void scan(void);
int sendevent(Window w, Atom proto, int m, long d0, long d1, long d2, long d3, long d4);
void sendmon(Client *c, Monitor *m);
void setclientstate(Client *c, long state);
void setfocus(Client *c);
void setfullscreen(Client *c, int fullscreen);
void setlayout(const Arg *arg);
void setlayoutsafe(const Arg *arg);
void setmfact(const Arg *arg);
void setup(void);
void setupepoll(void);
void seturgent(Client *c, int urg);
void showhide(Client *c);
void sighup(int unused);
void sigterm(int unused);
void spawn(const Arg *arg);
Monitor *systraytomon(Monitor *m);
void tag(const Arg *arg);
void tagmon(const Arg *arg);
void tile(Monitor *);
void togglebar(const Arg *arg);
void togglefloating(const Arg *arg);
void togglealwaysontop(const Arg *arg);
void toggletag(const Arg *arg);
void toggleview(const Arg *arg);
void freeicon(Client *c);
void unfocus(Client *c, int setfocus);
void unmanage(Client *c, int destroyed);
void unmapnotify(XEvent *e);
void updatebarpos(Monitor *m);
void updatebars(void);
void updateclientlist(void);
int updategeom(void);
void updatenumlockmask(void);
void updatesizehints(Client *c);
void updatestatus(void);
void updatesystray(int updatebar);
void updatesystrayicongeom(Client *i, int w, int h);
void updatesystrayiconstate(Client *i, XPropertyEvent *ev);
void updatetitle(Client *c);
void updateicon(Client *c);
void updatewindowtype(Client *c);
void updatewmhints(Client *c);
void view(const Arg *arg);
Client *wintoclient(Window w);
Monitor *wintomon(Window w);
void winview(const Arg* arg);
Client *wintosystrayicon(Window w);
int xerror(Display *dpy, XErrorEvent *ee);
int xerrordummy(Display *dpy, XErrorEvent *ee);
int xerrorstart(Display *dpy, XErrorEvent *ee);
void xinitvisual();
void drawroundedcorners(Client *c);
void zoom(const Arg *arg);
void settagsatom(Window w, unsigned int tags);

// FireWM custom functions

int checkColor(char* color);
int betterstatus_length(char *text);
char* betterstatus(char *text, int x);

// FireWM related API

void firesetalpha(const Arg *arg);
void firesetgaps(const Arg *arg);
void firesetbarcolor(const Arg *arg);
void firesetbordercolor(const Arg *arg);
void firesetbarlayout(const Arg *arg);
void firesetbarcenter(const Arg *arg);
void firesetbarpadding(const Arg *arg);

#endif
