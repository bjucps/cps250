/* CpS 250: Socket Lab (Client)
   Completed by YOUR NAME (YRLOGIN)
   Spring THISYEAR */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "common.h"

// create/connect a TCP client socket to the sockaddr_in `target`
// returns socket FD on success, -1 on failure (prints error messages to STDERR)
int connect_tcp(struct sockaddr_in *target) {
	// TODO
	return -1;
}

// main program
//--------------
// takes CLI arguments (IP, port, format_string)
// connects to target TCP server
// sends `format_string` as a line of input over the socket
// reads a line of output back from the server
// closes/terminates
int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;

	// handles to resources that may need cleanup
	int sock_fd = -1;
	FILE *readstream = NULL;
	char *readbuff = NULL;
	size_t readlen = 0u;
	
	// default: RFC 2822 date (from strftime(3) manpage)	
	char *time_fmt = "%a, %d %b %Y %T %z";	

	// check number of CLI args (show usage message if needed)
	if (argc < 3) {
		fprintf(stderr, "usage: %s IP PORT [TIME_FMT]\n", argv[0]);
		goto cleanup;
	}
	if (argc > 3) {
		time_fmt = argv[3];
	}

	// parse CLI args for IP/port into a sockaddr_in (or die)
	struct sockaddr_in target;
	if (!make_addr(argv[1], argv[2], &target)) {
		fprintf(stderr, "failed to parse IP/port pair\n");
		goto cleanup;
	}

	// connect a TCP socket to target (or die)
	if ((sock_fd = connect_tcp(&target)) < 0) {
		fprintf(stderr, "failed to connect to %s:%s\n", argv[1], argv[2]);
		goto cleanup;
	}

	// buffer the socket for _reads_ (writes will use unbuffered send_all)
	if ((readstream = streamify_sock(sock_fd)) == NULL) {
		fprintf(stderr, "failed to initialize buffered reads of socket\n");
		goto cleanup;
	}

	// send the time format string line (or die)
	// [hacky two-sends to avoid dynamic string concatenation]
	if (!send_all(sock_fd, time_fmt, strlen(time_fmt))) goto cleanup;
	if (!send_all(sock_fd, "\n", 1)) goto cleanup;

	// buffered-line-read of reply from server (or die)
	ssize_t len = getline(&readbuff, &readlen, readstream);
	if (len < 0) {
		perror("getline");
		goto cleanup;
	}

	// PRINT THE ANSWER
	puts(readbuff);

	ret = EXIT_SUCCESS;
cleanup:
	free(readbuff); // legal to free a NULL ptr (no-op)
	if (readstream != NULL) fclose(readstream); // NOT legal to fclose a NULL FILE *
	if (sock_fd >= 0) close(sock_fd);
	return ret;
}
