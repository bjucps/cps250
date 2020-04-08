all: echoclient echoserver echoserver_fork

echoclient: echoclient.c eznet.c
	gcc -g -std=gnu11 -fsanitize=address -Wall -Werror -DSHOW_LOG_ERROR -oechoclient echoclient.c eznet.c

echoserver: echoserver.c eznet.c
	gcc -g -std=gnu11 -fsanitize=address -Wall -Werror -DSHOW_LOG_ERROR -oechoserver echoserver.c eznet.c

echoserver_fork: echoserver_fork.c eznet.c
	gcc -g -std=gnu11 -fsanitize=address -Wall -Werror -DSHOW_LOG_ERROR -oechoserver_fork echoserver_fork.c eznet.c

clean:
	rm echoclient echoserver
