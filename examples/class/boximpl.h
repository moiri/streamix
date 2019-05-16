#ifndef BOXIMPL_H
#define BOXIMPL_H

int l( void* handler, void* state );
void l_cleanup( void* state );
int l_init( void* handler, void** state );
int m( void* handler, void* state );
void m_cleanup( void* state );
int m_init( void* handler, void** state );
int r( void* handler, void* state );
void r_cleanup( void* state );
int r_init( void* handler, void** state );

#endif /* ifndef BOXIMPL_H */
