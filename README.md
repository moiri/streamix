# streamix
Root repository for the Streamix project. This includes:
 - the Streamix compiler [`smxc`](https://github.com/moiri/streamix-c)
 - the Streamix runtime system [`smxrts`](https://github.com/moiri/streamix-rts)
 - the Streamix graph to C converter [`graph2c`](https://github.com/moiri/streamix-graph2c)
 - the Streamix network checker [`smxsia`](https://github.com/moiri/streamix-sia)

For details refer to each individual repository.

## Installation

    git clone --recursive git@github.com:moiri/streamix.git
    make
    sudo make install

Execuatables, libary files and include files will be installed into `/usr/local/bin/`, `/usr/local/lib/` and `/usr/local/include/`, respectively.
Make sure that `/usr/local/bin/` is in your `PATH` environment variable.

Requires
 - [`flex`](https://github.com/westes/flex) for lexing the Streamix code
 - [`bison`](https://www.gnu.org/software/bison/) for parsing the Streamix code
 - [`igraph`](http://igraph.org/c/) to build depedency graphs (make sure GraphML is enabled)
 - [`zlog`](https://github.com/HardySimpson/zlog)
 - [`pthread`](https://computing.llnl.gov/tutorials/pthreads/)

## Examples
To compile all examples run

    make examples

To run an example `cd` to the example directory and run

    make run
