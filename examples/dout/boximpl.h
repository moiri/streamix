#ifndef BOXIMPL_H
#define BOXIMPL_H

#include <stdio.h>

typedef struct a_state_s
{
    FILE* fp;
    int   sleep;
} a_state_t;

int a( void* h, void* state );
void a_cleanup( void* h, void* state );
int a_init( void* h, void** state );
int b( void* h, void* state );
void b_cleanup( void* h, void* state );
int b_init( void* h, void** state );

#endif /* ifndef BOXIMPL_H */
