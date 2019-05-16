#ifndef BOXIMPL_H
#define BOXIMPL_H

int a( void*, void* );
void a_cleanup( void* state );
int a_init( void* handler, void** state );
int b( void*, void* );
void b_cleanup( void* state );
int b_init( void* handler, void** state );

#endif /* ifndef BOXIMPL_H */
