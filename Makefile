# firewm - dynamic window manager
# See LICENSE.dwm file for copyright and license details.

include config.mk

SRC = drw.c firewm.c util.c
OBJ = ${SRC:.c=.o}
USER? = "root"

all: options firewm firewm-msg

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

firewm-msg: firewm-msg.o
	${CC} -o $@ $< ${LDFLAGS}

clean:
	rm -f firewm firewm-msg ${OBJ} firewm-${VERSION}.tar.gz config.h

dist: clean
	mkdir -p firewm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		firewm.1 drw.h util.h ${SRC} firewm.png transient.c firewm-${VERSION}
	tar -cf firewm-${VERSION}.tar firewm-${VERSION}
	gzip firewm-${VERSION}.tar
	rm -rf firewm-${VERSION}

install: all
	@mkdir -p /home/${USER}/.config/firewm/
	@chown ${USER}:${USER} /home/${USER}/.config/firewm/
	@cp config.conf /home/${USER}/.config/firewm/
	@chown ${USER}:${USER} /home/${USER}/.config/firewm/config.conf
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f firewm firewm-msg ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/firewm
	chmod 755 ${DESTDIR}${PREFIX}/bin/firewm-msg
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < firewm.1 > ${DESTDIR}${MANPREFIX}/man1/firewm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/firewm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/firewm\
		${DESTDIR}${MANPREFIX}/man1/firewm.1

.PHONY: all options clean dist install uninstall
