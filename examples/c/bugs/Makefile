EXAMPLES = crash\
           printf\
           sample\
           dangle\
           smash\
           leaky\
           printf-asan\
           smash-asan\
           leaky-asan

all: $(EXAMPLES)

# generic build rule (always include debug symbols)
%: %.c
	gcc -g -fno-omit-frame-pointer -o $@ $^

# special build rules for ASAN targets
%-asan: %.c
	gcc -g -fno-omit-frame-pointer -fsanitize=address -o $@ $^

clean:
	rm -f $(EXAMPLES)
