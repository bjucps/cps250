build: prog progsuid

install: prog progsuid
	chmod a+r *
	chmod a+rx prog progsuid
	chmod u+s progsuid
	chmod o-r stuff.txt

prog progsuid: prog.c
	gcc -O2 -o $@ $^

clean:
	rm -f prog progsuid
