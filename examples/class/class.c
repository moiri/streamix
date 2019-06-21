/**
 * @file class.c
 *
 * THIS FILE WAS GENERATED BY THE STREAMIX TOOL `smxtrsp`. DO NOT EDIT THIS
 * FILE EDIT THE ORIGINAL STREAMIX-SOURCE FILE `class.smx` INSTEAD!
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN WHEN RECOMPILING THE
 * STREAMIX-SOURCE FILE!
 *
 * The main file which builds the streamix network and starts each net.
 */

#include "smxrts.h"
#include "l.h"
#include "m.h"
#include "r.h"
#include "smx_mongo.h"

int main( void )
{
    SMX_PROGRAM_INIT();

    SMX_NET_CREATE( 0, L, l );
    SMX_NET_INIT( 0, 0, 1 );
    SMX_NET_CREATE( 1, M, m );
    SMX_NET_INIT( 1, 1, 1 );
    SMX_NET_CREATE( 2, M, m );
    SMX_NET_INIT( 2, 1, 1 );
    SMX_NET_CREATE( 3, R, r );
    SMX_NET_INIT( 3, 1, 0 );
    SMX_NET_CREATE( 4, Profiler, smx_mongo );
    SMX_NET_INIT( 4, 1, 0 );
    SMX_NET_CREATE( 5, smx_profiler, smx_profiler );
    SMX_NET_INIT( 5, 0, 1 );
    SMX_NET_INIT_PROFILER( 5 );
    SMX_CHANNEL_CREATE( 0, 1, SMX_FIFO, x );
    SMX_CONNECT( 0, 0, l, x, out );
    SMX_CONNECT( 1, 0, m, x, in );
    SMX_CHANNEL_CREATE( 1, 1, SMX_FIFO, x );
    SMX_CONNECT( 1, 1, m, x, out );
    SMX_CONNECT( 2, 1, m, x, in );
    SMX_CHANNEL_CREATE( 2, 1, SMX_FIFO, x );
    SMX_CONNECT( 2, 2, m, x, out );
    SMX_CONNECT( 3, 2, r, x, in );
    SMX_CHANNEL_CREATE( 3, 100, SMX_FIFO, profiler );
    SMX_CONNECT( 5, 3, smx_profiler, profiler, out );
    SMX_CONNECT( 4, 3, smx_mongo, data, in );
    SMX_NET_FINALIZE_PROFILER( 5 );

    SMX_PROGRAM_INIT_RUN();

    SMX_NET_RUN( 0, l, 0 );
    SMX_NET_RUN( 1, m, 0 );
    SMX_NET_RUN( 2, m, 0 );
    SMX_NET_RUN( 3, r, 0 );
    SMX_NET_RUN( 4, smx_mongo, 0 );
    SMX_NET_RUN( 5, smx_profiler, 0 );

    SMX_NET_WAIT_END( 0 );
    SMX_NET_WAIT_END( 1 );
    SMX_NET_WAIT_END( 2 );
    SMX_NET_WAIT_END( 3 );
    SMX_NET_WAIT_END( 4 );
    SMX_NET_WAIT_END( 5 );

    SMX_CHANNEL_DESTROY( 0 );
    SMX_CHANNEL_DESTROY( 1 );
    SMX_CHANNEL_DESTROY( 2 );
    SMX_CHANNEL_DESTROY( 3 );
    SMX_NET_DESTROY( 0 );
    SMX_NET_DESTROY( 1 );
    SMX_NET_DESTROY( 2 );
    SMX_NET_DESTROY( 3 );
    SMX_NET_DESTROY( 4 );
    SMX_NET_DESTROY_PROFILER( 5 );
    SMX_NET_DESTROY( 5 );

    SMX_PROGRAM_CLEANUP();
}