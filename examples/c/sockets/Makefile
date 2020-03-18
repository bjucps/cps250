all: echoclient echoserver

echoclient: echoclient.c eznet.c
	gcc -g -std=gnu11 -fsanitize=address -Wall -Werror -DSHOW_LOG_ERROR -oechoclient echoclient.c eznet.c

echoserver: echoserver.c eznet.c
	gcc -g -std=gnu11 -fsanitize=address -Wall -Werror -DSHOW_LOG_ERROR -oechoserver echoserver.c eznet.c

clean:
	rm echoclient echoserver
