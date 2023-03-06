// MASH: My Academic SHell
// A demonstration of Unix system programming basics (fork, exec, wait, etc.)
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

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

        // Tokenize command line entered by user
        while (token && (wpp < wpmax)) {
            *wpp++ = token;
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

