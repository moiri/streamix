#ifndef BOXIMPL_H
#define BOXIMPL_H

#include <stdio.h>

typedef struct merge_msg_s
{
    int     id;
    char    data;
} merge_msg_t;

typedef struct a_state_s
{
    FILE* fp;
    int   idx;
} a_state_t;

typedef struct b_state_s
{
    FILE* fp1;
    int   idx1;
    FILE* fp2;
    int   idx2;
} b_state_t;

int a( void*, void* );
void a_cleanup( void* state );
int a_init( void* handler, void** state );
int b( void*, void* );
void b_cleanup( void* state );
int b_init( void* handler, void** state );

#endif /* ifndef BOXIMPL_H */
