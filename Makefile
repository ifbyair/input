CC=gcc
CFLAGS=-I. -I../wiringPi/wiringPi -L/usr/local/lib
SRCS=smart.c
OBJS=$(SRCS:.c=.o)
DEPS=smart_lcd.h
LIBS=-lwiringPi
EXEC=smart

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

clean: 
	rm -f $(OBJS) $(EXEC)
