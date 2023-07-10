SRC = main.c
HDR = cpu.h
CFLAGS = -Wall -O0 -std=gnu11
APPNAME = 6502

default: ${APPNAME}

${APPNAME}.o: ${SRC} ${HDR}
	gcc ${CFLAGS} -c ${SRC} -o ${APPNAME}.o

${APPNAME}: ${APPNAME}.o
	gcc ${CFLAGS} ${APPNAME}.o -o ${APPNAME}

run: ${APPNAME}
	./${APPNAME}

rerun:
	$(MAKE) clean
	$(MAKE) run

clean:
	-rm -f ${APPNAME}.o
	-rm -f ${APPNAME}
