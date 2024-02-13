APPS := basics

FLAGS := -g -Werror -Wextra -fno-omit-frame-pointer

release: $(APPS)

debug: FLAGS += -fsanitize=address
debug: $(APPS)

$(APPS):%:%.c list.h
	gcc -o $@ $(FLAGS) $(filter %.c, $^) -lbsd

clean:
	rm -f $(APPS)
