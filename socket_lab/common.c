/* CpS 250: Socket Lab (Common Functions)
   Completed by YOUR NAME (YRLOGIN)
   Spring THISYEAR */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

// populate `sa` with
//		the IPv4 address parsed from `ip_str` and
//		the port parsed from `port_str`
// return 1 on success, 0 on error (prints messages to STDERR automatically)
int make_addr(const char *ip_str, const char *port_str, struct sockaddr_in *sa) {
	// TODO
	return 0;
}

// send all `dlen` bytes of `data` buffer over the `sockfd`
// returns 1 on success, 0 on socket error (after printing error messages to STDERR)
int send_all(int sockfd, char *data, size_t dlen) {
	// TODO
	return 0;
}

// wrap `sock_fd` in a stdio FILE* stream for easy buffered input
// returns valid FILE* on success, NULL on error (after printing errors to stderr)
// (dup's `sock_fd` so that it won't be closed with the FILE * is fclose'd)
FILE *streamify_sock(int sock_fd) {
	// TODO
	return NULL;
}

