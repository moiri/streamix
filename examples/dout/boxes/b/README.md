# Streamix Box Implementation `b`

This box implementation ...

## Configuration

The following configuration options are possible:

An example configuration can be found in `/opt/smx/conf/b.json`.

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

## Testing

The folder `test` contains a testing environment.
In order set up test the following steps must be taken:
 1. Add test data to the node `test_data` in the configuration file `test.json`.
 2. Describe the data conversion from JSON data to Streamix messages in the function `b_in_data_conversion()` of the file `test_b.c`.
 3. Describe the data conversion from a Streamix messages to JSON data and evaluate the result in the function `b_out_data_conversion()` of the file `test_b.c`.
 4. Compile the program with the command `make`.
 5. Run the test with either of the following commands
   - `./b`
   - `make run`.

## Dependencies

The box has the following dependencies:
 - [libsmxrts](https://github.com/moiri/streamix-rts)
 - [libxml2](http://xmlsoft.org/)
