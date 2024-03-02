/* CpS 250: Socket Lab (Server)
   Completed by YOUR NAME (YRLOGIN)
   Spring THISYEAR */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/socket.h>

#include "common.h"

// create/bind/listen a IPv4/TCP socket on the given listening sockaddr_in `endpoint`
//		passes `backlog` into the listen(2) syscall
// returns socket FD on success, -1 on failure (prints error messages to STDERR)
int listen_tcp(struct sockaddr_in *endpoint, int backlog) {
	// TODO
	return -1;
}

// accept a single connection on a listening TCP socket `fd`
//		populating the given `addrbufptr`/`addrbuflen` C string with the client IP address/port
// returns FD on success, -1 on error (having printed errors to STDERR)
int accept_tcp(int fd, char *addrbufptr, size_t addrbuflen) {
	// TODO
	return -1;
}

// perform the server logic for a connected client socket `fd`
//		- read a line from client
//		- pass that line to strftime(3) as a time-format-string
//		- write the resulting output of strftime(3) back to the connected socket
//		- close/teardown
// returns 1 on success, 0 on error (prints messages to STDERR)
//      (is responsible for CLOSING `fd` before returning)
int handle_client(int fd) {
	int ret = 0;
	FILE *readstream = NULL;
	char *readbuff = NULL;
	size_t readlen = 0u;

	// TODO: buffer the socket for _reads_ (writes will use unbuffered send_all)
	// TODO: buffered-line-read of format string from client (or die)
	// TODO: get current time (in a form suitable for use with strftime(3))
	// TODO: format the time into a string (with strftime(3))
	// TODO: send it back to the client
	
	// DONE (success)
	ret = 1;
cleanup:
	// TODO: cleanup all [possibly] unclaimed/owned resources
	return ret;
}

// main program
//--------------
// takes CLI arguments (IP, port)
// listens for connections on that endpoint
// 		for each connections, perform the read-format-write-timestring transaction and close
// (never terminates unless error)
int main(int argc, char **argv) {
	// handles to resources that may need cleanup
	int serv_fd = -1;
	int conn_fd = -1;
	
	// check number of CLI args (show usage message if needed)
	if (argc < 3) {
		fprintf(stderr, "usage: %s IP PORT\n", argv[0]);
		goto cleanup;
	}

	// parse CLI args for IP/port into a sockaddr_in (or die)
	struct sockaddr_in endpoint;
	if (!make_addr(argv[1], argv[2], &endpoint)) {
		fprintf(stderr, "failed to parse IP/port pair\n");
		goto cleanup;
	}

	// listen for incoming IPv4/TCP connections on our endpoint (or die)
	if ((serv_fd = listen_tcp(&endpoint, 5)) < 0) {
		fprintf(stderr, "failed to listen on %s:%s\n", argv[1], argv[2]);
		goto cleanup;
	}

	// ENTER THE ETERNAL SERVER LOOP
	//-------------------------------
	for (;;) {
		char addrbuf[32];

		// wait for the next connection (or die)
		if ((conn_fd = accept_tcp(serv_fd, addrbuf, sizeof addrbuf)) < 0) {
			fprintf(stderr, "failed to accept a connection\n");
			goto cleanup;
		}

		// log this connection to STDOUT
		printf("BEGIN: connection from %s\n", addrbuf);

		// pass it off to the "client logic" function (which takes ownership of it) [or die]
		if (!handle_client(conn_fd)) {
			fprintf(stderr, "unexpected error during client handling\n");
			goto cleanup;
		}

		// log termination
		printf("END: connection from %s\n", addrbuf);

		// no longer our problem to clean up this FD
		conn_fd = -1;
	
	}

cleanup:
	if (conn_fd >= 0) close(conn_fd);
	if (serv_fd >= 0) close(serv_fd);
	return EXIT_FAILURE;
}
