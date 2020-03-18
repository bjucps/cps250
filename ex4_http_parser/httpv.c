// File: httpv.c
// Submitted by: 
//

#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#define RC_OK 1
#define RC_ILLEGAL_STREAM -1
#define RC_IO_ERROR -2
#define RC_MALLOC_FAILURE -3
#define RC_ILLEGAL_VERB -4
#define RC_ILLEGAL_PATH -5
#define RC_MISSING_VERSION -6
#define RC_OTHER_ERR -7

#define MAX_HEADERS 10

typedef struct http_header {
    char *name;
    char *value;
} http_header_t;

typedef struct http_request {
    char *verb;
    char *path;
    char *version;
    int num_headers;
    http_header_t headers[MAX_HEADERS];
} http_request_t;


FILE *parseArgs(int argc, char **argv)
{
    
}

// Returns RC_OK on success,
// RC_ILLEGAL_STREAM on invalid HTTP request,
// RC_IO_ERROR on I/O error,
// RC_MALLOC_FAILURE on malloc failure
int parseHttp(FILE *in, http_request_t **request) 
{
    http_request_t *req = NULL;
    int rc = RC_OTHER_ERR;

    // TODO: Allocate memory for req

    // TODO: Read HTTP request from <in>


    // TODO: On success, return req

    rc = RC_OK;
    return rc;

cleanup:

    free(req);  // It's OK to free() a NULL pointer 
    return rc;

}

int main(int argc, char **argv)
{
    FILE *f = parseArgs(argc, argv);
    if (f == NULL) {
        exit(1);
    }

    http_request_t *request = NULL;
    int result = 0;

    // TODO: Invoke parseHttp

    switch (result) {
    case RC_OK:
        printf("Verb: %s\n", request->verb);
        printf("Path: %s\n", request->path);
        printf("Version: %s\n", request->version);
        printf("\n%d header(s):\n", request->num_headers);
        for (int i = 0; i < request->num_headers; ++i) {
             printf("* %s is %s\n", request->headers[i].name, request->headers[i].value);
        }
        break;
    case RC_ILLEGAL_STREAM:
        fprintf(stderr, "** ERROR: Illegal HTTP stream.\n");
        break;
    case RC_IO_ERROR:
        fprintf(stderr, "** ERROR: I/O error while reading request.\n");
        break;
    case RC_MALLOC_FAILURE:
        fprintf(stderr, "** ERROR: malloc failure.\n");
        break;
    default:
        printf("Unexpected return code %d.\n", result);
    }

    fclose(f);
}
