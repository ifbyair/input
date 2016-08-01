CC=gcc
CFLAGS=-I.
SRCS=xx.c
OBJS=$(SRCS:.c=.o)
DEPS=xx.h
LIBS=
EXEC=xx

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

clean: 
	rm -f $(OBJS) $(EXEC)
