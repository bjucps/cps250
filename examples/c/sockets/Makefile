APPS = echoclient1 echoclient2 echoserver echoserver_fork 

CFLAGS = -g -std=gnu11 -Wall -Werror -DSHOW_LOG_ERROR


all: $(APPS)

asan: CFLAGS += -fsanitize=address
asan: all

# all apps depend on the networking library
$(APPS): eznet.c eznet.h

# all apps' main logic is a single eponymous source file
$(APPS):%:%.c
	gcc $(CFLAGS) -o $@ $(filter %.c, $^)

clean:
	rm -f $(APPS)
