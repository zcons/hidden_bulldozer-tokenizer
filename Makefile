CC = clang
CFLAGS = -g

SRCS = linkedlist.c main.c talloc.c
HDRS = linkedlist.h value.h talloc.h
OBJS = $(SRCS:.c=.o)

talloctest: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm talloctest
