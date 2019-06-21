/**
 * @author  smxrtsp
 * @file    l_sig.h
 *
 * THIS FILE WAS GENERATED BY THE STREAMIX TOOL `smxtrsp`. DO NOT EDIT THIS
 * FILE EDIT THE ORIGINAL STREAMIX-SOURCE FILE INSTEAD!
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN WHEN RECOMPILING THE
 * STREAMIX-SOURCE FILE!
 *
 * The header file of the implementation of the streamix box l.
 *
 * The box has the following signature:
 *
 *   - out x (use SMX_CHANNEL_WRITE( h, l, x, msg ) to write)
 */

#ifndef BOX_l_SIG_H
#define BOX_l_SIG_H

/**
 * The input signature of l
 */
enum ports_l_in_e
{
    SMX_PORT_IDX_l_in_EMPTY,
};

/**
 * The output signature of l
 */
enum ports_l_out_e
{
    SMX_PORT_IDX_l_out_x,
};

#endif
