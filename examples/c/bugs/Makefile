EXAMPLES = crash\
           printf\
           sample\
           dangle\
           smash\
	   leaky

ASAN_EXAMPLES = printf-asan\
                smash-asan\
                leaky-asan\

all: $(EXAMPLES) $(ASAN_EXAMPLES)

# generic build rule (always include debug symbols)
%: %.c
	gcc -g -fno-omit-frame-pointer -o $@ $^

# special dependency info for the ASAN targets
smash-asan: smash.c
printf-asan: printf.c
leaky-asan: leaky.c

# special build rules for ASAN targets
$(ASAN_EXAMPLES):
	gcc -g -fno-omit-frame-pointer -fsanitize=address -o $@ $^

clean:
	rm -f $(EXAMPLES) $(ASAN_EXAMPLES)
