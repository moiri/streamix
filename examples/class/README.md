# Streamix Application `class`

This application ...

## Configuration

In general, a configuration file is of the following form:

```json
{
    "_name": "class",
    "_log": "app.zlog",
    "_nets": {
        "_default": {
            "profiler": false,
            "config": {}
        },
        "<box_name>": {
            "_default": {
                "profiler": null,
                "config": null
            },
            "<net_name>": {
                "_default": {
                    "profiler": null,
                    "config": null
                },
                "<net_id>": {
                    "profiler": null,
                    "config": null
                }
            }
        }
    }
}
```

The keys `<box_name>`, `<net_name>`, and `<net_id>` are replicated for all
corresponding elements as defined in the Streamix network `class.smx`.

The configuration options are split into two parts:
 1. The box-specific configuration which is defined in a `config` key. The box
    configuration depends on the box implementation. Refer to the respective
    box documentation to learn more. The key `config` either accepts
    - an object defining the configuration options of the respective net
      instance.
    - a string pointing to the file location of a net configuration file.
 2. General configuration options valid for every net. Currently the following
    options are available:
    - `profiler`: if set to `true` profile messages will be written to a
      [lttng](https://lttng.org/docs/v2.10/#doc-controlling-tracing) tracer
      (if one is set up). If set to `false` the profiler is disabled for this
      net.

Note that the configuration file is hierarchical. Always the most specific
configuration for a net instance is chosen. I.e. in the following list the
configuration is used which matches with
 1. the net instance id (`_nets.<box_name>.<net_name>.<net_id>`)
 2. the net instance name (`_nets.<box_name>.<net_name>._default`)
 3. the net instance box type (`<_nets>.<box_name>._default`)
 4. any net instance (`_nets._default`)

An example configuration of this application can be found in
`/opt/smx/conf/class.json`.

## Network

The application network is described in `class.smx` using the syntax of
the coordination language Streamix. Refer to the configuration file
`/opt/smx/conf/class.json` for a list of all nets used in the network.

## Usage

To display the command line options of the application type:
```
class - h
```

## Compiling and Installing

A Makefile is provided with the following commands (among others):
 - `make`: compile the app and all local box implementations to an executable
   `class`. Note that all local box implementations are linked statically
   while external ones (marked with `extern` in Streamix) are linked
   dynamically.
 - `make dpkg`: create a `deb` package including the binary, this document, and
   the default configuration file.
 - `sudo make install`: manually install to the target folders
 - `sudo make uninstall`: manually remove the app files from to the target
   folders
