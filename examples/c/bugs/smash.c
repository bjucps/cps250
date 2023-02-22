#include <stdio.h>
#include <string.h>

char *mygets(char *buff) {
	int c;
	char *p = buff;

	while ((c = getchar()) != '\n')
		*p++ = c;

	*p = '\0';
	return buff;
}

char *getname(char *buf, size_t len) {
	char tmpbuf[128];

	do {
		printf("enter your name: ");
		mygets(tmpbuf);
	} while ((strlen(tmpbuf) <= 1) || (strlen(tmpbuf) >= len));

	strcpy(buf, tmpbuf);
	return buf;	
}

int main(int argc, char **argv) {
	char name[64];

	printf("hello, %s!\n", getname(name, sizeof name));
	return 0;
}
