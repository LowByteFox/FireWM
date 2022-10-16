void
firesetalpha(const Arg *arg)
{
	int i;
	for (i = 0; i < 2; i++) alphas[i][1] = arg->ui;

	scheme_old = scheme;
	scheme = ecalloc(LENGTH(colors), sizeof(Clr *));
	if (scheme_old != scheme) {
		free(scheme_old);
	}
	for (i = 0; i < LENGTH(colors); i++)
		scheme[i] = drw_scm_create(drw, colors[i], alphas[i], 3);

	updatebars();
	updatestatus();
	updatebarpos(selmon);
	updatesystray(0);

}

void
firesetgaps(const Arg *arg)
{
	selmon->gappx = arg->ui;
	arrange(selmon);
}

void
firesetbarpadding(const Arg *arg)
{
	int sidepad = arg->ui;
	int vertpad = arg->ui;
	sp = sidepad;
	vp = (topbar == 1) ? vertpad : - vertpad;
	barpadding = arg->ui;

	Screen *src = ScreenOfDisplay(dpy, screen);

	XMoveWindow(dpy, selmon->barwin, barpadding, barpadding);
	XResizeWindow(dpy, selmon->barwin, src->width - 2 * barpadding, user_bh ? user_bh : drw->fonts->h + 2);
	updatesystray(1);
	arrange(selmon);
}

void
firesetbarcolor(const Arg *arg)
{
	char *tempColor = (char*) arg->v;
	if (checkColor(tempColor))
		memcpy(col_activebar, tempColor, 7);

	scheme_old = scheme;
	scheme = ecalloc(LENGTH(colors), sizeof(Clr *));
	if (scheme_old != scheme) {
		free(scheme_old);
	}
	for (int i = 0; i < LENGTH(colors); i++)
		scheme[i] = drw_scm_create(drw, colors[i], alphas[i], 3);
}

void
firesetbordercolor(const Arg *arg)
{
	char *tempColor = (char*) arg->v;
	if (checkColor(tempColor))
		memcpy(col_border, tempColor, 7);

	scheme_old = scheme;
	scheme = ecalloc(LENGTH(colors), sizeof(Clr *));
	if (scheme_old != scheme) {
		free(scheme_old);
	}
	for (int i = 0; i < LENGTH(colors); i++)
		scheme[i] = drw_scm_create(drw, colors[i], alphas[i], 3);
}

void
firesetbarlayout(const Arg *arg)
{
	char *tmpLay = (char*) arg->v;
	if (strlen(tmpLay) > 6) return;

	memcpy(barlayout, tmpLay, 6);
	drawbars();
}

void
firesetbarcenter(const Arg *arg)
{
	char *tmpCenter = (char*) arg->v;
	if (strlen(tmpCenter) == 0) return;

	center = *tmpCenter;
}