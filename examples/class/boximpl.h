#ifndef BOXIMPL_H
#define BOXIMPL_H

int l( void* h, void* state );
void l_cleanup( void* h, void* state );
int l_init( void* h, void** state );
int m( void* h, void* state );
void m_cleanup( void* h, void* state );
int m_init( void* h, void** state );
int r( void* h, void* state );
void r_cleanup( void* h, void* state );
int r_init( void* h, void** state );

#endif /* ifndef BOXIMPL_H */
