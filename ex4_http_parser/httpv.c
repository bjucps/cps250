// File: httpv.c
// Submitted by: 
//

#include <bsd/string.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define RC_OK 1
#define RC_ILLEGAL_STREAM -1
#define RC_IO_ERROR -2
#define RC_MALLOC_FAILURE -3
#define RC_ILLEGAL_VERB -4
#define RC_ILLEGAL_PATH -5
#define RC_MISSING_VERSION -6
#define RC_OTHER_ERR -7

typedef struct http_header {
    char *name;
    char *value;
	struct list_head entry;	// entry link in linked-list
} http_header_t;

typedef struct http_request {
    char *verb;
    char *path;
    char *version;
    int num_headers;
	struct list_head headers;	// head of linked-list of headers
} http_request_t;


FILE *parse_args(int argc, char **argv)
{
    
}

// Returns RC_OK on success,
// RC_ILLEGAL_STREAM on invalid HTTP request,
// RC_IO_ERROR on I/O error,
// RC_MALLOC_FAILURE on malloc failure
int parse_http(FILE *in, http_request_t **request) 
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
    FILE *f = parse_http(argc, argv);
    if (f == NULL) {
        exit(1);
    }

    http_request_t *request = NULL;
    int result = 0;

    // TODO: Invoke parse_http

    switch (result) {
    case RC_OK:
        printf("Verb: %s\n", request->verb);
        printf("Path: %s\n", request->path);
        printf("Version: %s\n", request->version);
        printf("\n%d header(s):\n", request->num_headers);
		http_header_t *hp;
		list_for_each_entry(hp, &request->headers, entry) {
             printf("* %s is %s\n", hp->name, hp->value);
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
