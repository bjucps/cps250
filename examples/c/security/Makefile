all: args-boom args-safe

args-boom: args.c
	gcc -g -no-pie -z execstack -o $@ $^

args-safe: args.c
	gcc -g -fstack-protector-all -o $@ $^

clean:
	rm -f args-safe args-boom
