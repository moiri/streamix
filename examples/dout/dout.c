/**
 * @file dout.c
 *
 * THIS FILE WAS GENERATED BY THE STREAMIX TOOL `smxtrsp`. DO NOT EDIT THIS
 * FILE EDIT THE ORIGINAL STREAMIX-SOURCE FILE `dout.smx` INSTEAD!
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN WHEN RECOMPILING THE
 * STREAMIX-SOURCE FILE!
 *
 * The main file which builds the streamix network and starts each net.
 */

#include "smxrts.h"
#include "a.h"
#include "b.h"

int main( void )
{
    SMX_PROGRAM_INIT();

    SMX_NET_CREATE( 0, A, a );
    SMX_NET_INIT( 0, 0, 1 );
    SMX_NET_CREATE( 1, B, b );
    SMX_NET_INIT( 1, 1, 0 );
    SMX_CHANNEL_CREATE( 0, 1, SMX_D_FIFO, x );
    SMX_CONNECT( 0, 0, a, x, out );
    SMX_CONNECT( 1, 0, b, x, in );

    SMX_PROGRAM_INIT_RUN();

    SMX_NET_RUN( 0, a, 0 );
    SMX_NET_RUN( 1, b, 0 );

    SMX_NET_WAIT_END( 0 );
    SMX_NET_WAIT_END( 1 );

    SMX_CHANNEL_DESTROY( 0 );
    SMX_NET_DESTROY( 0 );
    SMX_NET_DESTROY( 1 );

    SMX_PROGRAM_CLEANUP();
}
