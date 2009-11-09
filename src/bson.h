/* bson.h */

#ifndef _BSON_H_
#define _BSON_H_

#include "platform_hacks.h"

typedef enum {
    bson_eoo=0 ,
    bson_double=1,
    bson_string=2,
    bson_object=3,
    bson_array=4,
    bson_bindata=5,
    bson_undefined=6,
    bson_oid=7,
    bson_bool=8,
    bson_date=9,
    bson_null=10,
    bson_regex=11,
    bson_dbref=12,
    bson_code=13,
    bson_symbol=14,
    bson_codewscope=15,
    bson_int = 16,
    bson_timestamp = 17,
    bson_long = 18
} bson_type;


typedef struct {
    char * data;
    int owned;
} bson;

typedef struct {
    const char * cur;
    int first;
} bson_iterator;

typedef struct {
    char * buf;
    char * cur;
    int bufSize;
    int finished;
    char* stack[32];
    int stackPos;
} bson_buffer;

typedef short bson_bool_t;

/* ----------------------------
   READING
   ------------------------------ */

bson * bson_init( bson * b , char * data , int mine );
int bson_size( bson * b );
void bson_destory( bson * b );

void bson_print( bson * b );
void bson_print_raw( const char * bson , int depth );

void bson_iterator_init( bson_iterator * i , const char * bson );

int bson_iterator_more( bson_iterator * i );
bson_type bson_iterator_next( bson_iterator * i );

bson_type bson_iterator_type( bson_iterator * i );
const char * bson_iterator_key( bson_iterator * i );
const char * bson_iterator_value( bson_iterator * i );

/* these convert to the right type */
double bson_iterator_double( bson_iterator * i );
int bson_iterator_int( bson_iterator * i );
int64_t bson_iterator_long( bson_iterator * i );

/* false: boolean false, 0 in any type, or null */
/* true: anything else (even empty strings and objects) */
bson_bool_t bson_iterator_bool( bson_iterator * i );

/* these assume you are using the right type (return 0 if non-numeric) */
double bson_iterator_double_raw( bson_iterator * i );
int bson_iterator_int_raw( bson_iterator * i );
int64_t bson_iterator_long_raw( bson_iterator * i );
bson_bool_t bson_iterator_bool_raw( bson_iterator * i );
const char * bson_iterator_string( bson_iterator * i );
int bson_iterator_string_len( bson_iterator * i );

/* ----------------------------
   BUILDING
   ------------------------------ */

bson_buffer * bson_buffer_init( bson_buffer * b );
bson_buffer * bson_ensure_space( bson_buffer * b , const int bytesNeeded );

/**
 * @return the raw data.  you either should free this OR call bson_destory not both
 */
char * bson_finish( bson_buffer * b );
void bson_destroy( bson_buffer * b );

bson_buffer * bson_append_int( bson_buffer * b , const char * name , const int i );
bson_buffer * bson_append_double( bson_buffer * b , const char * name , const double d );
bson_buffer * bson_append_string( bson_buffer * b , const char * name , const char * str );
bson_buffer * bson_append_bool( bson_buffer * b , const char * name , const bson_bool_t v );
bson_buffer * bson_append_null( bson_buffer * b , const char * name );

bson_buffer * bson_append_start_object( bson_buffer * b , const char * name );
bson_buffer * bson_append_start_array( bson_buffer * b , const char * name );
bson_buffer * bson_append_finish_object( bson_buffer * b );



void bson_fatal( char * msg , int ok );

#endif