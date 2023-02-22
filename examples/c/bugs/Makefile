EXAMPLES = crash\
	   printf\
	   sample

all: $(EXAMPLES)

%: %.c
	gcc -g -o $@ $^

clean:
	rm -f $(EXAMPLES)
