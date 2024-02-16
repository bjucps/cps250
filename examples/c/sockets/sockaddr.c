#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;

	if (argc < 3) {
		printf("usage: %s IP PORT\n", argv[0]);
		goto cleanup;
	}

	char *input_ip = argv[1];
	struct sockaddr_in sai = { .sin_family = AF_INET };
	
	if (!inet_aton(input_ip, &sai.sin_addr)) {
		printf("inet_aton: invalid IPv4 address '%s'\n", input_ip);
		goto cleanup;
	}

	char *input_port = argv[2];
	errno = 0;
	unsigned long host_port = strtoul(input_port, NULL, 10);
	if (errno != 0) {
		perror("strtoul");
		goto cleanup;
	}
	sai.sin_port = htons(host_port);

	char output_ip[32];
	snprintf(output_ip, sizeof output_ip, "%s", inet_ntoa(sai.sin_addr));

	printf("sockaddr_in {\n"
		   "    .sin_family = %d,\n"
		   "    .sin_port = 0x%04x,\n"
		   "    .sin_addr = 0x%08x (%s),\n"
		   "}\n", 
		   sai.sin_family, 
		   ntohs(sai.sin_port),
		   ntohl(sai.sin_addr.s_addr),
		   output_ip);

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}
