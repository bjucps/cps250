/* CpS 250: Socket Lab (Common Functions Header)
   by Dr. J
   Spring 2024 */
#ifndef CPS250_COMMON_H_
#define CPS250_COMMON_H_

#include <stdio.h>	// for FILE * type
#include <arpa/inet.h>	// for struct sockaddr_in * type

int make_addr(const char *ip_str, const char *port_str, struct sockaddr_in *sa);

int send_all(int sockfd, char *data, size_t dlen);

FILE *streamify_sock(int sock_fd);

#endif
