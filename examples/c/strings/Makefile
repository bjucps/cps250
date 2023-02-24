ASAN_TARGETS= dragons uhoh
BSD_TARGETS= concat dynmemory
ETC_TARGETS= snprintfdemo stringlist stringlist2 split

all: $(ASAN_TARGETS) $(BSD_TARGETS) $(ETC_TARGETS)

dragons: dragons.c
uhoh: uhoh.c

$(ASAN_TARGETS):
	gcc -g -fsanitize=address -o $@ $^

concat: concat.c
dynmemory: dynmemory.c

$(BSD_TARGETS):
	gcc -g -o $@ $^ -lbsd

snprintfdemo: snprintfdemo.c
stringlist: stringlist.c
stringlist2: stringlist2.c
split: split.c

$(ETC_TARGETS):
	gcc -g -o $@ $^


clean:
	rm -f $(ASAN_TARGETS) $(BSD_TARGETS) $(ETC_TARGETS)
