# streamix
Root repository for the Streamix project. This includes:
 - the Streamix compiler [`smxc`](https://github.com/moiri/streamix-c)
 - the Streamix runtime system [`smxrts`](https://github.com/moiri/streamix-rts)
 - the Streamix graph to C converter [`graph2c`](https://github.com/moiri/streamix-graph2c)
 - the Streamix network checker [`smxsia`](https://github.com/moiri/streamix-sia)

For deatils refer to each individual repository.

## Installation

    git clone --recursive git@github.com:moiri/streamix.git
    make
    sudo make install

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
