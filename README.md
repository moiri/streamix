# streamix
Root repository for the Streamix project. This includes:
 - the Streamix compiler [`smxc`](https://github.com/moiri/streamix-c)
 - the Streamix runtime system [`smxrts`](https://github.com/moiri/streamix-rts)
 - the Streamix graph to C converter [`graph2c`](https://github.com/moiri/streamix-graph2c)
 - the Streamix network checker [`smxsia`](https://github.com/moiri/streamix-sia)
 - the Streamix network checker language compiler [`sia2graph`](https://github.com/moiri/streamix-sia-lang)

Streamix is a coordination language targeting mixed-criticality cyber-physical systems.
For details refer to [this](https://uhra.herts.ac.uk/handle/2299/21094) document.

## 1. Installation and Requirements
The Streamix tools require [`flex`](https://github.com/westes/flex), [`bison`](https://www.gnu.org/software/bison/), [`igraph`](http://igraph.org/c/), and [`zlog`](https://github.com/HardySimpson/zlog) (for installation see below).

To install the Streamix tools type

    git clone --recursive https://github.com/moiri/streamix.git
    make
    sudo make install

Execuatables, libary files and include files will be installed into `/usr/local/bin/`, `/usr/local/lib/` and `/usr/local/include/`, respectively.
Make sure that `/usr/local/bin/` is in your `PATH` environment variable.

In order to install the Streamix tools, the following packages and libraries have to be installed:
### 1.1. [`flex`](https://github.com/westes/flex)
This is used for lexing the Streamix code. To install on an apt-based linux sytem type

    sudo apt update
    sudo apt install flex

### 1.2. [`bison`](https://www.gnu.org/software/bison/)
This is used for parsing the Streamix code. To install on an apt-based linux system type

    sudo apt update
    sudo apt install bison

### 1.3. [`igraph`](http://igraph.org/c/)
This is used to build depedency graphs.

    sudo apt update
    sudo apt install libigraph0-dev

If you want to compile it from source, make sure GraphML is enabled (see http://igraph.org/c/ for details)

    cd igraph
    ./configure
    make
    make check
    sudo make install

### 1.4 [`zlog`](https://github.com/HardySimpson/zlog)
This is used as a logger in the runtime system. To install type

    cd zlog
    make
    sudo make install

## 2. Examples
To compile all examples run

    make examples

To run an example `cd` to the example directory and run

    make run
