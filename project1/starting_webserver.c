/* Webserver Starting Code
 * (c) 2024, Bob Jones University
 */
#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Other standard library functions
#include <string.h>     // Standard string functions
#include <errno.h>      // Global errno variable

#include <stdarg.h>     // Variadic argument lists (for blog function)
#include <time.h>       // Time/date formatting function (for blog function)

#include <unistd.h>     // Standard system calls
#include <signal.h>     // Signal handling system calls (sigaction(2))


#define BLOG_MSG_LIMIT	256

// Macro version of blog adding file/line prefix (only with -DDEBUG, though)
#ifdef DEBUG
#define DEBUG_BLOG(fmt, ...) blog("%s:%d:" fmt, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#else
#define DEBUG_BLOG(fmt, ...) /* NOTHING */
#endif

// Generic log-to-stdout logging routine
// Message format: "timestamp:pid:user-defined-message"
void blog(const char *fmt, ...) {
    // Convert user format string and variadic args into a fixed string buffer
    char user_msg_buff[BLOG_MSG_LIMIT];
    va_list vargs;
    va_start(vargs, fmt);
    vsnprintf(user_msg_buff, sizeof(user_msg_buff), fmt, vargs);
    va_end(vargs);

    // Get the current time as a string
    time_t t = time(NULL);
    struct tm *tp = localtime(&t);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tp);

    // Print said string to STDOUT prefixed by our timestamp and pid indicators
    printf("%s|%d|%s\n", timestamp, getpid(), user_msg_buff);
    fflush(stdout);
}

// GLOBAL: settings structure instance
struct settings {
    const char *bindhost;   // Hostname/IP address to bind/listen on
    const char *bindport;   // Portnumber (as a string) to bind/listen on
} g_settings = {
    .bindhost = "localhost",    // Default: listen only on localhost interface
    .bindport = "6000",         // Default: listen on TCP port 5000
};

// Parse commandline options and sets g_settings accordingly.
// Returns 0 on success, -1 on false...
int parse_options(int argc, char * const argv[]) {
    int ret = -1; 

    char op;
    while ((op = getopt(argc, argv, "h:p:")) > -1) {
        switch (op) {
            case 'h':
                g_settings.bindhost = optarg;
                break;
            case 'p':
                g_settings.bindport = optarg;
                break;
            default:
                // Unexpected argument--abort parsing
				printf("Unexpected option '%s'\n\n", optarg);
                goto cleanup;
        }
    }

    ret = 0;
cleanup:
    return ret;
}

// GLOBAL: flag indicating when to shut down server
volatile sig_atomic_t server_running = 0;

// SIGINT handler that detects Ctrl-C and sets the "stop serving" flag
void sigint_handler(int signum) {
	(void)signum;
    server_running = 0;
}

int main(int argc, char **argv) {
    int ret = 1;

    // Handle our options
    if (parse_options(argc, argv)) {
        printf("usage: %s [-p PORT] [-h HOSTNAME/IP]\n", argv[0]);
        goto cleanup;
    }

    // Install signal handler for SIGINT
    struct sigaction sa_int = {
        .sa_handler = sigint_handler
    };
    if (sigaction(SIGINT, &sa_int, NULL)) {
        blog("sigaction(SIGINT, ...) -> '%s'", strerror(errno));
        goto cleanup;
    }

	/* TODO: create server socket and start listening for connections */

	blog("Listening for HTTP/1.0 connections on %s:%s\n", g_settings.bindhost, g_settings.bindport);

    server_running = 1;
    while (server_running) {
		/* TODO: accept/process connections */
    }
	blog("Received shutdown signal...\n");
    ret = 0;

cleanup:
	/* TODO: clean up resources, ensure clean/orderly shutdown */
    return ret;
}

