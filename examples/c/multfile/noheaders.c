typedef struct FILE FILE;
int fprintf(FILE *, const char *, ...);
extern FILE *stdout;

int main() {
	fprintf(stdout, "look, Ma, no header files!\n");
	return 0;
}
