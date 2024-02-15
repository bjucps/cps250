APPS := basics wordplay

FLAGS := -g -Werror -Wextra -fno-omit-frame-pointer

release: $(APPS)

debug: FLAGS += -fsanitize=address
debug: $(APPS)

$(APPS):%:%.c uthash.h
	gcc -o $@ $(FLAGS) $(filter %.c, $^) -lbsd

clean:
	rm -f $(APPS)
