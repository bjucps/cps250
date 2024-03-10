PROGS = mono \
	fork_bad \
	fork \
	prefork_bad \
	prefork

CFLAGS = -g -Wall -Wextra

release: all

debug: CFLAGS += -fsanitize=address
debug: all

all: $(PROGS)

$(PROGS):%:%.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o

