THREAD_APPS = hello sharedbad sharedok waitbad waitok
ETC_APPS = functionptr

all: $(THREAD_APPS) $(ETC_APPS)

$(THREAD_APPS):%:%.c
	gcc -g -o $@ $^ -lpthread

$(ETC_APPS):%:%.c
	gcc -g -o $@ $^

clean:
	rm -f $(THREAD_APPS) $(ETC_APPS)
