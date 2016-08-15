CC=gcc
CFLAGS=-I. -I../wiringPi/wiringPi -I../wiringPi/devLib
SRCS=smart.c
OBJS=$(SRCS:.c=.o)
DEPS=smart_lcd.h lcd.h smart.h
LIBS=-lwiringPi -lwiringPiDev
EXEC=smart

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

clean: 
	rm -f $(OBJS) $(EXEC) lcdtest

lcdtest:
	$(CC) $(CFLAGS) lcd1.c -o $@ $(LIBS)
