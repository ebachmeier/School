# Hooli Drive
A file synchronization client and server system written in C that allows users back up their files from any
of their devices via the command-line interface.

![Hooli Drive](http://ericbachmeier5.github.io/assets/css/images/hooli.jpg)

## Overview
Hooli Drive functions on three main programs - the client, a database server, and a file upload server . I built this system to run on a Linux machine. I have, however, tested it on both Mac OS X 10.9 and Ubuntu 14.04.

The client program recursively scans a specified directory tree for files and calculates their checksum (for version control). Then,
the list of files is sent with their checksums to the HMDS (database server) using a TCP connection. Here, the checksum for each file is compared to the existing metadata that is stored in a Redis server. Once HMDS has determined a list of files that have been modified, it sends a response to the client requesting the files to upload to the server (HFTPD). The client then sends the specified files over a reliable UDP connection.

## How to use
### Dependencies
Hooli Drive requires the following dependencies to be installed:
* zlib (checksums) `sudo apt-get install zlib1g-dev`
* Redis server `sudo apt-get install redis-server`
* Redis C Library `sudo apt-get install libhiredis-dev`

### Running HMDS
Within the *hmds* folder, type `make`.

The database server accepts three optional parameters:

* `-p PORT` / `--port PORT`
  Specifies the port on which to listen. If not given, defaults to `9000`.

* `-r HOSTNAME` / `--redis HOSTNAME`
  Specifies the hostname of the Redis server. If not given, defaults to `localhost`.

* `-v`/ `--verbose`
  Enables verbose output.

Therefore, HMDS can be executed as follows:

`./hmds`

or:

`./hmds -p 5555 -r example.com -v`

### Running HFTPD
Within the *hftpd* folder, type `make`.

HFTPD accepts five optional parameters:
* `-p / --port PORT`
  Specifies the port on which to listen for HFTP messages. If not given, defaults to `10000`.

* `-r HOSTNAME / --redis HOSTNAME`
  Specifies the hostname of the Redis server. If not given, defaults to `localhost`.

* `-d / --dir ROOT`
  Specifies the directory in which uploaded files are stored.  Files are stored as `ROOT/username/relative/path/to/file`.
  If not given, defaults to `/tmp/hftpd`. If the directory does not exist, it will be created.

* `-t / --timewait SECONDS`
  The number of seconds HFTPD should spend in the *TIME_WAIT* state before exiting. If not given, defaults to `10`.

  Note: The *TIME_WAIT* state occurs after HFTPD has acknowledged a termination request by the client. In case the acknowledging message is lost, HFTPD waits to ensure the client does not resend a termination request.

* `-v / --verbose`
  Enable verbose output (see description later).  If not given, defaults to non-verbose output.

Therefore, HFTPD might be executed as follows:

`./hftpd`

or:

`./hftpd -p 8888 -r example2.com -d ~/storefiles -t 15 -v`

### Running Client
Note that before executing the client, HMDS and HFTPD must be running and awaiting communication from the client.
Within the *client* folder, type `make`.

The client accepts six optional parameters (and two required ones):
* `-s HOSTNAME` / `--server HOSTNAME`
  Specifies the database server's hostname (hmds). If not given, defaults to `localhost`.

* `-p PORT` / `--port PORT`
  Specifies the database server's port (hmds). If not given, defaults to `9000`.

* `-d DIR` / `--dir DIR`
  Specifies the Hooli root directory to be scanned for files. If not given, defaults to `~/hooli`.

* `-f / --fserver HOSTNAME`
  Specifies the HFTP server's hostname. If not given, default to `localhost`.

* `-o / --fport PORT`
  Specifies the HFTP server's port. If not given, defaults to `10000`.

* `-v`/ `--verbose`
  Enables verbose output.

Therefore, the client might be executed as follows:

`./client eric password`

or:

`./client -s example.com -p 5555 -d ~/myfiles -f example2.com -o 8888 -v`
