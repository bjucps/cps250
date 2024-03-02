CFLAGS = -Wall -Wextra

release: override CFLAGS += -O2
release: all

debug: override CFLAGS += -g -fsanitize=address
debug: all

all: client server

client: client.o common.o
	gcc $(CFLAGS) -o client $^

server: server.o common.o
	gcc $(CFLAGS) -o server $^

client.o: client.c common.h
	gcc $(CFLAGS) -c client.c

common.o: common.c
	gcc $(CFLAGS) -c common.c

clean:
	rm -f server client *.o
