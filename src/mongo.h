/* mongo.h */

#ifndef _MONGO_H_
#define _MONGO_H_

#include "bson.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

typedef struct mongo_connection_options {
    char host[255];
    int port;
} mongo_connection_options;

typedef struct {
    mongo_connection_options options;
    struct sockaddr_in sa;
    socklen_t addressSize;
    int sock;
    int connected;
} mongo_connection;

typedef struct {
    int len;
    int id;
    int responseTo;
    int op;
    char data;
} mongo_message;

enum mongo_operations {
    mongo_op_msg = 1000,    /* generic msg command followed by a string */
    mongo_op_update = 2001, /* update object */
    mongo_op_insert = 2002,
    mongo_op_query = 2004,
    mongo_op_get_more = 2005,
    mongo_op_delete = 2006,
    mongo_op_kill_cursors = 2007
};


/* ----------------------------
   CONNECTION STUFF
   ------------------------------ */

/**
 * @param options can be null
 */
int mongo_connect( mongo_connection * conn , mongo_connection_options * options );
int mongo_disconnect( mongo_connection * conn );
int mongo_destory( mongo_connection * conn );



/* ----------------------------
   CORE METHODS - insert update remove query getmore
   ------------------------------ */

int mongo_insert( mongo_connection * conn , const char * ns , bson * data );
int mongo_insert_batch( mongo_connection * conn , const char * ns , bson ** data , int num );

void mongo_query( mongo_connection * conn , const char * ns , bson * query , bson * fields , int nToReturn , int nToSkip , int options );

/* ----------------------------
   HIGHER LEVEL - indexes - command helpers eval
   ------------------------------ */

/* ----------------------------
   COMMANDS
   ------------------------------ */


/* ----------------------------
   UTILS
   ------------------------------ */

void mongo_exit_on_error( int ret );

#endif