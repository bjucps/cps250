#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>

const char banner[] = "Hello there!  Good bye!\n";

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	int sock = -1;
	int conn = -1;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		goto cleanup;
	}
	
	struct sockaddr_in listen_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(3003),
		.sin_addr = {
			.s_addr = htonl(INADDR_LOOPBACK),
		},
	};

	if (bind(sock, (const struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0) {
		perror("bind");
		goto cleanup;
	}

	if (listen(sock, 5) < 0) {
		perror("listen");
		goto cleanup;
	}
	
	struct sockaddr_in conn_addr;
	socklen_t ca_len = sizeof(conn_addr);
	if ((conn = accept(sock, (struct sockaddr *)&conn_addr, &ca_len)) < 0) {
		perror("accept");
		goto cleanup;
	}
	printf("Got connection (fd=%d) from IP4 0x%08x (port=%d)\n", conn, ntohl(conn_addr.sin_addr.s_addr), ntohs(conn_addr.sin_port));

	send(conn, banner, sizeof banner, 0);

	if (shutdown(conn, SHUT_RDWR) < 0) {
		perror("shutdown");
		goto cleanup;
	}

	ret = EXIT_SUCCESS;
cleanup:
	if (conn > -1) close(conn);
	if (sock > -1) close(sock);
	return ret;
}
