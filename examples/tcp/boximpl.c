#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

enum com_state_e { SYN, SYN_ACK, ACK, DONE };


void* msg_init()
{
    int* init = malloc( sizeof( int ) );
    *init = 42;
    return ( void* )init;
}

void msg_destroy( void* data )
{
    free( ( int* )data );
}

void* a( void* handler )
{
    int state = SYN;
    smx_msg_t* msg;
    while( state != DONE ) {
        switch( state ) {
            case SYN:
                msg = SMX_CHANNEL_READ( handler, A, syn );
                dzlog_info( "a, received data: %d", *( int* )msg->data );
                state = SYN_ACK;
                break;
            case SYN_ACK:
                *( int* )msg->data -= 3;
                sleep(1);
                SMX_CHANNEL_WRITE( handler, A, syn_ack, msg );
                state = ACK;
                break;
            case ACK:
                msg = SMX_CHANNEL_READ( handler, A, ack );
                dzlog_info( "a, received data: %d", *( int* )msg->data );
                state = DONE;
                break;
            default:
                state = DONE;
        }
    }
    SMX_MSG_DESTROY( msg );
    return NULL;
}

void* b( void* handler )
{
    int state = SYN;
    smx_msg_t* msg = SMX_MSG_CREATE( msg_init, NULL, msg_destroy );

    while( state != DONE ) {
        switch( state ) {
            case SYN:
                sleep(1);
                SMX_CHANNEL_WRITE( handler, B, syn, msg );
                state = SYN_ACK;
                break;
            case SYN_ACK:
                msg = SMX_CHANNEL_READ( handler, B, syn_ack );
                dzlog_info( "b, received data: %d", *( int* )msg->data );
                state = ACK;
                break;
            case ACK:
                *( int* )msg->data += 5;
                sleep(1);
                SMX_CHANNEL_WRITE( handler, B, ack, msg );
                state = DONE;
                break;
            default:
                state = DONE;
        }
    }
    return NULL;
}
