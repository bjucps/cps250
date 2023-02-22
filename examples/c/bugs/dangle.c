#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char *readline(void) {
	char buff[128];
	char *sneaky = NULL, *pete = (char*)&buff;

	if (fgets(buff, sizeof(buff), stdin) == NULL) {
		perror("fgets");
		return NULL;
	}
	buff[strlen(buff) - 1] = '\0';
	memcpy(&sneaky, &pete, sizeof sneaky);
	return sneaky;
}

// helper function to simplify
// running a command-line and
// getting its STDOUT as a 
// string (like $(...) in bash)
char *runget(const char *cmd) {
	char *ret = NULL;
	FILE *pf = NULL;
	char *buf = NULL;
	size_t blen = 0;

	// run command with STDOUT going to readable pipe
	if ((pf = popen(cmd, "r")) == NULL) {
		perror("popen");
		goto cleanup;
	}

	// slurp to EOF from pipe
	if (getdelim(&buf, &blen, EOF, pf) < 0) {
		perror("getdelim");
		goto cleanup;
	}

	// trim trailing WS
	size_t len = strlen(buf);
	while (isspace(buf[len-1])) {
		buf[len - 1] = '\0';
		--len;
	}

	// return string
	ret = buf;
	buf = NULL;
cleanup:
	if (buf) free(buf);
	if (pf) fclose(pf);
	return ret;
}


int main(int argc, char **argv) {
	printf("please enter your name: ");
	
	// read name into local buffer (DANGLE ADDRESS)
	char *name = readline();	

	// trash over that buffer's space with new function call that uses 
	// a bit of stack)
	char *whoami = runget("whoami"); 

	// read it and weep...
	printf("pleased to meet you, %s!\nI see your name is stored at %p...\noddly, the OS thinks your name is '%s'\n", name, name, whoami);
	free(whoami);
}
