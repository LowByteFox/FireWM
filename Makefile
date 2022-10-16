# firewm - dynamic window manager
# See LICENSE.dwm file for copyright and license details.

include config.mk

SRC = drw.c firewm.c util.c
OBJ = ${SRC:.c=.o}
USER? = "root"

all: options firewm firewmctl

options:
	@echo firewm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

firewm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

firewmctl: firewmctl.o
	${CC} -o $@ $< ${LDFLAGS}

compositor:
	gcc -o compositor composite.c -lX11 -lXext -lXdamage -lXfixes -lXtst -lXrender -lXcomposite -Llib -lFoxBox

clean:
	rm -f firewm firewmctl ${OBJ} firewm-${VERSION}.tar.gz config.h firewmctl.o

dist: clean
	mkdir -p firewm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		drw.h util.h ${SRC} firewm.png transient.c firewm-${VERSION}
	tar -cf firewm-${VERSION}.tar firewm-${VERSION}
	gzip firewm-${VERSION}.tar
	rm -rf firewm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f firewm firewmctl ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/firewm
	chmod 755 ${DESTDIR}${PREFIX}/bin/firewmctl
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/firewm\
		${DESTDIR}${MANPREFIX}/man1/firewm.1

config:
	@mkdir -p -v ${HOME}/.config/firewm/
	@cp -i -v config.conf ${HOME}/.config/firewm/

.PHONY: all options clean dist install uninstall config
