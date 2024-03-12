PROGS = mono \
	fork_bad \
	fork \
	prefork_bad \
	prefork

TPROGS = thread \
	threadpool

CFLAGS = -g -Wall -Wextra

release: all

debug: CFLAGS += -fsanitize=address
debug: all

all: $(PROGS) $(TPROGS)

$(PROGS):%:%.c
	gcc $(CFLAGS) -o $@ $^

$(TPROGS):%:%.c
	gcc $(CFLAGS) -D_GNU_SOURCE -o $@ $^ -lpthread

clean:
	rm -f $(PROGS) $(TPROGS) *.o

