APPS = icat inert report sigiodemo spawner2 spawner

OBJS = safe_snprintf/safe_snprintf.o
HEDS = safe_snprintf/safe_snprintf.h


all: $(APPS) 

$(APPS):%:%.c $(OBJS)
	gcc -g -std=gnu11 -Wall -Werror -I safe_snprintf/ -o $@ $^

$(OBJS):%.o:%.c $(HEDS)
	gcc -g -c -std=gnu11 -Wall -Werror -o $@ $<

clean:
	rm -f $(APPS) $(OBJS)
