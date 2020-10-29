# Streamix Box Implementation `b`

This box implementation ...

## Configuration

The following configuration options are possible:

An example configuration can be found in `/opt/smx/conf/b.xml`.

## Signature

The box has the following input ports:

The box has the following output ports:

## Using the library

When a box `b` is spawned as a net in a Streamix network, the box must
be marked as `extern` in the Streamix code and the application must be compiled
with `-lb` (add this to the `EXT_LIBS` variable in the app Makefile).

## Compiling and Installing

A Makefile is provided that allows to
 - compile the box implementation to a library `libb` (`make`)
 - create `deb` packages including the library, this document, and the default configuration file (`make dpkg`)
 - manually install to the target folders (`sudo make install`)

## Dependencies

The box has the following dependencies:
 - [libsmxrts](https://github.com/moiri/streamix-rts)
 - [libxml2](http://xmlsoft.org/)
