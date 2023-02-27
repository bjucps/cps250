CFLAGS = -g

ASAN_TARGETS= dragons uhoh
BSD_TARGETS= concat dynmemory
ETC_TARGETS= snprintfdemo stringlist stringlist2 split

all: $(ASAN_TARGETS) $(BSD_TARGETS) $(ETC_TARGETS)

$(ASAN_TARGETS):%:%.c
	gcc $(CFLAGS) -fsanitize=address -o $@ $^ 

$(BSD_TARGETS):%:%.c
	gcc $(CFLAGS) -o $@ $^ -lbsd

$(ETC_TARGETS):%: %.c
	gcc $(CFLAGS) -o $@ $^ 

clean:
	rm -f $(ASAN_TARGETS) $(BSD_TARGETS) $(ETC_TARGETS)

