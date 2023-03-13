// MASH: My Academic SHell v1.1
// A demonstration of Unix system programming basics (fork, exec, wait, etc.)
// Additionally shows very simple I/O redirection (just '>' and '<' for stdout/stdin)
// (c) 2016-2023, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

const char *PROMPT = "! ";
const char *DELIMS = " \t\r\n";

int main() {
    int status = 1;
    char *linebuf = NULL;
    size_t linelen = 0u;

    fputs(PROMPT, stdout);
    while (getline(&linebuf, &linelen, stdin) > 0) {
        char *words[16] = { 0 };
        char **wpp = words, **wpmax = words + 15;
        char *token = strtok(linebuf, DELIMS);
		char *redir_stdin = NULL;
		char *redir_stdout = NULL;

        // Tokenize command line entered by user
        while (token && (wpp < wpmax)) {
			if (token[0] == '>') {
				redir_stdout = &token[1];
			} else if (token[0] == '<') {
				redir_stdin = &token[1];
			} else {
				*wpp++ = token;
			}
            token = strtok(NULL, DELIMS);
        }

        // Handle built-in commands
        if (strcmp(words[0], "cd") == 0) {
            if (chdir(words[1])) {
                perror("cd");
                // Not a fatal error...
            }
        } else if (strcmp(words[0], "exit") == 0) {
            // Clean exit
            break;
        } else {
            // ...otherwise, fork/exec the requested program
            pid_t child = fork();
            
            if (child < 0) {
                // ERROR BRANCH
                perror("fork fail");
                goto cleanup;
            } else if (child == 0) {
                // CHILD BRANCH
				//------------------
			
				// First, set up I/O redirection (if we had any)
				if (redir_stdout) {	
					int out = open(redir_stdout, O_WRONLY|O_CREAT|O_TRUNC, 0644);
					if (out < 0) {
						perror("open"); // carry on
					} else if (dup2(out, STDOUT_FILENO) < 0) {
						perror("dup2"); // carry on
					}
					close(out); // either fail, or close an extra handle not needed
				}
				if (redir_stdin) {	
					int in = open(redir_stdin, O_RDONLY);
					if (in < 0) {
						perror("open");
					} else if (dup2(in, STDIN_FILENO) < 0) {
						perror("dup2");
					}
					close(in);
				}

				// Now run the target program
                if (execvp(words[0], words)) {
                    perror("exec fail");
                    goto cleanup;
                }
            } else {
                // PARENT BRANCH
                if (wait(NULL) < 0) {
                    perror("wait");
                    goto cleanup;
                }
		
            }
        }
        fputs(PROMPT, stdout);
    }

    status = 0;
cleanup:
    free(linebuf);
    return status;
}

