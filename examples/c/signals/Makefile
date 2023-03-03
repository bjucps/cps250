APPS = icat inert report sigiodemo spawner2 spawner
C99_APPs = icat-c99

all: $(APPS) $(C99_APPs)

$(APPS):%:%.c
	gcc -g -std=gnu11 -Wall -Werror -o $@ $^

$(C99_APPs):%-c99:%.c
	gcc -g -std=c99 -Wall -Werror -o $@ $^

clean:
	rm -f $(APPS)
