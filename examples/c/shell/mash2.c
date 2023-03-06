// MASH2: My Academic SHell, Part II
// A more advanced variant of MASH that can perform primitive pipelining of shell utilities
// (c) 2016-2023, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXWORDS 32
const char *PROMPT = "! ";
const char *DELIMS = " \t\r\n";

int spawn_child(char **argv, int fdin, int fdout) {
    int kid = fork();
    if (kid == 0) {
        // CHILD PROCESS
        if ((fdin > -1) && (dup2(fdin, 0) < 0)) {
            perror("dup2 stdin");
            exit(1);
        }
        if ((fdout > -1) && (dup2(fdout, 1) < 0)) {
            perror("dup2 stdout");
            exit(1);
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }
    return kid;
}

void reap_child() {
	int status, who = wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
		printf("[child %d exited with status %d]\n", who, WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("[child %d exited with signal %d]\n", who, WTERMSIG(status));
	}
}

int main() {
    int status = 1;
    char *linebuf = NULL;
    size_t linelen = 0u;
    int pipe_fds[2] = { -1, -1 };
    int next_stdin = -1;
    int kids = 0;

    fputs(PROMPT, stdout);
    while (getline(&linebuf, &linelen, stdin) > 0) {
        char *words[MAXWORDS] = { 0 };
        char **wpp = words, **wpmax = words + MAXWORDS - 1;
        char *token = strtok(linebuf, DELIMS);

        while (token) {
            if (wpp >= wpmax) {
                fputs("too many words\n", stderr); goto cleanup;
            }

            if (strcmp(token, "|") == 0) {
                if (!words[0] || (strcmp(words[0], "cd") == 0) || (strcmp(words[0], "exit") == 0)) {
                    fputs("syntax error\n", stderr);
                    break;
                }
                if (pipe(pipe_fds)) {
                    perror("pipe");
                    goto cleanup;
                }

                if (spawn_child(words, next_stdin, pipe_fds[1]) < 0) {
                    perror("fork");
                    goto cleanup;
                }
                ++kids;

                // Parent process is done with the WRITE end of the last pipe
                if (close(pipe_fds[1])) { perror("close"); goto cleanup; }

                // Next process will be launched with READ end of pipe
                // as STDIN (and we are done with the old STDIN, if it was
                // part of a pipe)
                if ((next_stdin > -1) && (close(next_stdin))) { perror("close"); goto cleanup; }
                next_stdin = pipe_fds[0];

                // Reset pipe fd array to "invalid" fds to prevent double-closes
                pipe_fds[0] = -1;
                pipe_fds[1] = -1;

                // Reset argument array pointer to start of words
                // (we'll be parsing a new command at this point)
                memset(words, 0, sizeof(words));
                wpp = words;
            } else {
                *wpp++ = token;
            }
            token = strtok(NULL, DELIMS);
        }

        // Handle built-in commands
        if (words[0] == NULL) {
            // NOOP (empty line)
        } else if (strcmp(words[0], "cd") == 0) {
            if (chdir(words[1])) {
                perror("cd");
                // Not a fatal error...
            }
        } else if (strcmp(words[0], "exit") == 0) {
            // Clean exit
            break;
        } else {
            // ...otherwise, fork/exec the requested program
            if (spawn_child(words, next_stdin, -1) < 0) {
                perror("fork");
                goto cleanup;
            }
            ++kids;

            // Close last pipe READ end (if any)
            // and reinitialize next-stdin to true STDIN
            if ((next_stdin > -1) && (close(next_stdin))) { perror("close"); goto cleanup; }
            next_stdin = -1;
        }
        for (; kids > 0; --kids) reap_child(); 
        fputs(PROMPT, stdout);
    }

    status = 0;
cleanup:
    while (kids-- > 0) reap_child();
    if (next_stdin > -1) close(next_stdin);
    if (pipe_fds[0] > -1) close(pipe_fds[0]);
    if (pipe_fds[1] > -1) close(pipe_fds[1]);
    free(linebuf);
    return status;
}

