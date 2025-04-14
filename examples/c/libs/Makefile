CFLAGS = -g -Wall -Wextra

SRC_OBJS = \
	add.o \
	sub.o

STAT_OBJS = $(patsubst %.o,static-%.o,$(SRC_OBJS))
DYN_OBJS = $(patsubst %.o,dynamic-%.o,$(SRC_OBJS))

all: libmymath.a libmymath.so

$(STAT_OBJS):static-%.o:%.c
	gcc $(CFLAGS) -c -o $@ $^

libmymath.a: $(STAT_OBJS)
	ar rs $@ $^

$(DYN_OBJS):dynamic-%.o:%.c
	gcc $(CFLAGS) -fPIC -c -o $@ $^

libmymath.so: $(DYN_OBJS)
	gcc -shared $(CFLAGS) -o $@ $^

clean:
	rm -rf $(STAT_OBJS) $(DYN_OBJS) libmymath.a libmymath.so
