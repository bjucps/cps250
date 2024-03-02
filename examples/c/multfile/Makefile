CFLAGS = -Wall -Wextra

# release target
release: override CFLAGS += -O2 -fomit-frame-pointer
release: all

# debug target
debug: override CFLAGS += -fsanitize=address -fno-omit-frame-pointer -DDEBUG
debug: all

all: myprog pp cpp.out

# executable
myprog: main.o util.o
	gcc $(CFLAGS) main.o util.o -omyprog

# individual modules
main.o: main.c util.h
	gcc $(CFLAGS) -c main.c

util.o: util.c util.h
	gcc $(CFLAGS) -c util.c

pp: preprocessme.c
	gcc $(CFLAGS) -o pp preprocessme.c

cpp.out: preprocessme.c
	gcc $(CFLAGS) -E -o $@ $^

clean:
	rm -f *.o myprog pp cpp.out
