SRC = main.c
HDR = cpu.h
CFLAGS = -Wall -O0 -std=gnu11
APPNAME = 6502
APP2NAME = halfass

default: ${APPNAME}

${APPNAME}.o: ${SRC} ${HDR}
	gcc ${CFLAGS} -c ${SRC} -o ${APPNAME}.o

${APPNAME}: ${APPNAME}.o
	gcc ${CFLAGS} ${APPNAME}.o -o ${APPNAME}

clean:
	-rm -f ${APPNAME}.o
	-rm -f ${APPNAME}
	-rm -f ${APP2NAME}
	-rm -f ${APP2NAME}.o

${APP2NAME}: ${APP2NAME}.c
	rm -rf ${APP2NAME}
	gcc ${APP2NAME}.c -o ${APP2NAME}
