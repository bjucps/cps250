CFLAGS = -g -Wall -Werror -fno-omit-frame-pointer

APPS = cat_syscall cat_stdio sys_hello
LOGS = strace_stdio.log strace_syscall.log
DATA = biggishfile

BS = 1K
COUNT = 32

all: $(APPS)

$(APPS): %: %.c
	gcc $(CFLAGS) -o $@ $^


biggishfile:
	dd if=/dev/random bs=$(BS) count=$(COUNT) | base64 >$@
	
$(LOGS): strace_%.log: cat_% biggishfile
	bash -c "time strace -o $@ ./$< biggishfile >/dev/null"

demo: $(LOGS)

clean:
	rm -f $(APPS) $(LOGS) $(DATA)
