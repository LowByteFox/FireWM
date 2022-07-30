/*
 * FireWM - Window Manager made in pure C, created on top of DWM
 * Copyright (C) 2022 Fire-The-Fox
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	sidepad = selmon->gappx;
	vertpad = selmon->gappx;
	sp = sidepad;
	vp = (topbar == 1) ? vertpad : - vertpad;

	Screen *src = ScreenOfDisplay(dpy, screen);

	XMoveWindow(dpy, selmon->barwin, selmon->gappx, selmon->gappx);
	XResizeWindow(dpy, selmon->barwin, src->width - 2 * selmon->gappx, user_bh ? user_bh : drw->fonts->h + 2);
	updatesystray(1);
	arrange(selmon);
}

void
firesetcyan(const Arg *arg)
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