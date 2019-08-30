# Streamix Box Implementation `a`

This box implementation ...

## Configuration

The following configuration options are possible:

An example configuration can be found in `/opt/smx/conf/a.json`.

## Signature

The box has the following input ports:

The box has the following output ports:

## Using the library

When a box `a` is spawned as a net in a Streamix network, the box must
be marked as `extern` in the Streamix code and the application must be compiled
with `-la` (add this to the `EXT_LIBS` variable in the app Makefile).

## Compiling and Installing

A Makefile is provided that allows to
 - compile the box implementation to a library `liba` (`make`)
 - create `deb` packages including the library, this document, and the default configuration file (`make dpkg`)
 - manually install to the target folders (`sudo make install`)

## Testing

The folder `test` contains a testing environment.
In order set up test the following steps must be taken:
 1. Add test data to the node `test_data` in the configuration file `test.json`.
 2. Describe the data conversion from JSON data to Streamix messages in the function `a_in_data_conversion()` of the file `test_a.c`.
 3. Describe the data conversion from a Streamix messages to JSON data and evaluate the result in the function `a_out_data_conversion()` of the file `test_a.c`.
 4. Compile the program with the command `make`.
 5. Run the test with either of the following commands
   - `./a`
   - `make run`.

## Dependencies

The box has the following dependencies:
 - [libsmxrts](https://github.com/moiri/streamix-rts)
 - [libxml2](http://xmlsoft.org/)
