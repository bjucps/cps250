CFLAGS = -g

# debug target
debug: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -DDEBUG
debug: myprog

# release target
release: myprog

# executable
myprog: main.o util.o
	gcc $(CFLAGS) main.o util.o -omyprog

# individual modules
main.o: main.c util.h
	gcc $(CFLAGS) -c main.c

util.o: util.c util.h
	gcc $(CFLAGS) -c util.c

clean:
	rm *.o myprog
