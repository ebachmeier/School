**Computer Science 3357**  
**Fall 2015 - Assignment 3**

## Overview

We've studied reliable data transfer and have seen algorithms that might be
implemented at the transport layer to ensure that data sent is received
correctly. On the other hand, we've also seen that reliable transport
protocols like TCP incur greater overhead than unreliable protocols like UDP,
and are subject to the constraints of flow control and congestion control.

What if we want the performance of UDP — with its low-overhead, unreliable,
no-frills service — but the reliability of TCP? The answer is that we're going
to have to build in reliability at a higher layer: the application layer!

In assignment 2, we implemented the HMDP protocol to allow the client to send
a list of files to a Hooli Metadata Server, and for the server to reply with a
list of files it needs uploaded.  In this assignment, we'll add a second
server process, the Hooli File Server, to which the client will upload
requested files via the *Hooli File Transfer Protocol (HFTP)*, a UDP-based
reliable file transfer protocol.

The following diagram demonstrates our new architecture:

![Hooli Architecture](https://gist.githubusercontent.com/jsuwo/16ae38d7438a986eb8f0/raw/4a5e6f88c98b837341e5e587ee826d697ee768e5/cs3357-hooli-architecture.png)

The HFTP protocol is a Stop-and-Wait protocol, in which the client implements
the sender side of RDT 3.0, and the server implements the receiver side.  Of
course, as we've seen, Stop-and-Wait is not very efficient, but it still gives
us practice implementing a reliable data transfer protocol without having to
worry about multi-threading, as we would with Go-Back-N or Selective Repeat.

Along the way, we'll see how to emulate a "noisy" channel in Linux, creating a
queueing discipline that will corrupt, reorder, and lose packets. In this way,
we can accurately test the reliability of your programs and verify that we
have correctly implemented HFTP.

**Before moving on, please go read the 
[HFTP Protocol Specification](https://gist.github.com/jsuwo/a4b827136bb62bf64b74).**

## Objectives

This assignment will give you experience with:

* Implementing a protocol from a specification
* Implementing a binary protocol
* Understanding and implementing a reliable file transfer protocol
* Socket programming with UDP
* Argument parsing with `getopt_long`
* Program logging with `syslog`
* Programming and debugging in C

## Labs

For this assignment, you will likely want to read **[labs 4 and 5](http://jsuwo.github.io/cs3357/labs/)**, which cover
UDP socket programming.

## A Word on Assignment 2

In this assignment, you have a choice of whether or not to build upon your
assignment 2 code.  You have two choices:

**Option 1: Build upon your assignment 2 code.**

In this case, you must ensure your assignment 2 submission is working
correctly, and must fix any bugs that remain in it.

To encourage you to correct, refactor, and build upon your code, you
are eligible for a bonus of up to 10% if you do so.

**Option 2: Use the provided libraries that implement the assignment 2 functionality**

In this case, you are not eligible for a bonus.  The provided libraries
implement the code required for assignment 2.

** [Download libraries here](https://github.com/cs3357a-2015/cs3357-fall2015-asn3libs)

Now for the legalese.  If you choose to use your assignment 2 code:

* **It must be working to spec**

  You may need to make corrections, if you have bugs left over from
  assignment 2.  We will **try** to get your assignment 2 code returned to you
  at least 3-4 days prior to the submission of assignment 3.
  
* **Outstanding bugs may affect your assignment 3 mark**

  If you have bugs left over from assignment 2, they might affect the
  functionality of your assignment 3 submission.  We will not take into account
  *when* a bug was introduced (assignment 1, 2, or 3) when marking your
  code: a bug is a bug.

* **The bonus is *up to* 10%**

  You do not immediately get 10% for using your previous code.  It must be high 
  quality code, reasonably devoid of bugs, and the rest of your assignment must 
  achieve a grade of at least 80% to get any sort of bonus.  

* For those choosing to use my library, it will be posted, along with some 
documentation on how to use it, later this week.

## Part 1 - Client

The client implements the sender side of RDT 3.0 to transfer a file reliably over UDP to the server.

### Functionality

You must modify your client as follows:

* Communicate with an HMDP server to obtain an authentication token, and a
  list of files to be uploaded (already implemented)

* Initialize the next sequence number to `0`

* For each file requested, in sequence,

  * Send a type `1` control message to the Hooli File Server with the next 
    sequence number, and the rest of the file's details populating the
    appropriate fields

  * If the token is invalid, the server's response will contain an error.  In
    this case, print an appropriate error message, and exit.

  * Otherwise, send a data message containing the first chunk of the file, and
    wait for the appropriate ACK.

  * Then, send the next chunk and wait for the appropriate ACK.

  * Continue until the file is fully transferred.

  * If there is another file to send, send another type `1` control message,
    wait for an ACK, and then begin transferring that file

* Once all files have been transferred, send a type `2` control message and
  wait for an ACK.

* Once an ACK has been received, exit the program.

Note: you should be alternating between `0` and `1` for your sequence numbers.
The first message sent by the client should always have sequence number `0`.

### Finite state machine

The finite state machine for the client is based on the RDT 3.0 sender (figure
3.15 in the textbook, on page 215). Click the image to enlarge it.

![Client FSM](https://gist.githubusercontent.com/jsuwo/16ae38d7438a986eb8f0/raw/325b9bea45d74b907142942ffbea542e1dab1406/hftp-client-fsm.png)

Note: we are presenting the client's logic in a FSM to help you understand it.
You do not actually need to implement a FSM in code (it would add unnecessary
complexity to do so). Just use the FSM to guide your program logic.

### Command line arguments

Use the `getopt_long` function to parse arguments and add two **additional**
parameters to your client:

* `-f / --fserver HOSTNAME`

  Specifies the hostname on which the HFTP server is listening.  If not given,
  default to `localhost`.

* `-o / --fport PORT`

  Specifies the port on which the HFTP server is listening.  If not given,
  default to `10000`.

### Client Output

If verbose output has not been enabled, the client should regularly display
the following information in a neat and orderly manner:

* Current file being transferred
* Current file number (e.g. `1 of 5`)
* Number of bytes successfully transferred for the current file
* Total number of bytes for the current file
* Percent complete for the current file

Note the use of the term *regularly* above. This does not mean report an
update after every acknowledgement. Transferring a 4 GB file and producing
output on every 1464 byte chunk would make for extremely messy output.

A good idea might be to choose a certain data size `X` and to product output
each time `X` bytes have been successfully transferred and acknowledged. Use
your discretion. Make your output neat, but keep your program responsive and
informative.

If verbose output has been enabled, the client should display, upon every
message sent (this information should be in one line — do not print 3 lines
for every message, please):

* The type of message (do not print `Type 1` — assume the user doesn't know anything about this protocol)
* The sequence number of the message
* The amount of data in the message (if applicable)
* In verbose mode, upon every ACK received, the client should display (in one line):
  * The sequence number of the ACK
  * The value of the Error Code field

Finally, verbose mode should display the same output as non-verbose mode in
regular intervals.

## Part 2 - Server

The server implements the receiver side of RDT 2.2 to receive a file reliably
over UDP from the client.

### Functionality

The HFTP server runs in a separate process from the HMDS server.  Create
a directory `hftpd`.  In this directory, you should build your server.
A `Makefile` must be provided that builds an executable `hftpd`.

When executed, the server should:

* Create a UDP socket bound to the specified port

* Listen for incoming UDP messages

* When a message arrives, follow the logic shown in the finite state machine below.

* For each file successfully received, be sure to:

  * Store the file in the directory given by the `--root` option.  Files
    should be stored in a subdirectory `username`, followed by the relative path
    specified by the client.

    * For example, if `--root` is not given, we default to `/tmp/hftpd`.
      If the user `jeff` uploads a file `bin/code.c`, then the file would be
      stored as `/tmp/hftpd/jeff/bin/code.c`.

  * Update the file's checksum in the Redis server *after* the file has been
    successfully received.

The server **should not** exit after a session is complete.  Instead, it should
continue to wait for HFTP messages.

The server **must** cleanly close the socket, free any memory allocated, and exit
the program when the user types **Ctrl+C**.

### Finite state machine

The finite state machine for the server is based on the RDT 2.2 sender (figure
3.14 in the textbook, on page 214). Click the image to enlarge it.

![Server FSM](https://gist.githubusercontent.com/jsuwo/16ae38d7438a986eb8f0/raw/325b9bea45d74b907142942ffbea542e1dab1406/hftp-server-fsm.png)

Note: we are presenting the server's logic in a FSM to help you understand it.
You do not actually need to implement a FSM in code (it would add unnecessary
complexity to do so). Just use the FSM to guide your program logic.

### Command line arguments

Use the `getopt_long` function to parse the following arguments:

* `-p / --port PORT`

  Specifies the port on which to listen for HFTP messages.

* `-r HOSTNAME / --redis HOSTNAME`

  Specifies the hostname of the Redis server. If not given, default to `localhost`.
  
* `-d / --dir ROOT`

  Specifies the directory in which uploaded files are stored.  You should
  store files as `ROOT/username/relative/path/to/file`.  If not given, default
  to `/tmp/hftpd`.

  If the directory does not exist, your program should create it.

* `-t / --timewait SECONDS`

  The number of seconds to spend in the *TIME_WAIT* state before exiting.  If
  not given, default to `10`.

* `-v / --verbose`

  Enable verbose output (see description later).  If not given, default to
  non-verbose output.

### Server Output

The same requirements apply for the server output as with the client output.
The user should be regularly updated on the progress of the transfer. If
verbose mode is specified, the program should print information on each
message sent and received (see the Client Output section for more
information).

### The `TIME_WAIT` State

To understand the need for the `TIME_WAIT` state, consider what happens if we
ACK a type 2 control message, but the ACK gets lost. What will the client do?

## Hints

* To test your program, you **[can (and should) simulate a noisy channel](https://gist.github.com/jsuwo/9e58a477b8f5f4b17c49)**.
* Do lab 4 for information on UDP socket programming. 
* Don't forget about host order vs. network order! See Lab 4.
* Friendly tip: a pointer to a struct can be cast to a pointer to another type
  of struct, if the two struct types are of the same size.
* fopen, fread, fwrite, and fclose could be useful. See the man pages!
* You do not need to (and probably should not) use signals to implement a
  timer in this program. See the `poll` function.
* Start soon.

## General Requirements

### Repository structure

Do *NOT* copy your code from assignment 2 to a new directory.  In a source
code repository, you simply edit the existing code, and push the changes to
GitHub.  You will lose 5% of your mark if you create, for example, an `asn3`
directory and copy all your code into it.  Why?  Because, by doing so, you're
communicating to me that you've totally missed the point of source control.

Long story short: just edit the code you already have in your GitHub
repository.  Do not copy code.

Your directory structure should be:

```
client/     - All client code
common/     - If you have any shared code between programs, it goes here
hdb/        - Your database library
hmds/       - Your HMDP server code
hftpd/      - Your HFTP server code
```

Don't forget to include a `Makefile` in the `hftpd` directory that builds an
executable `hftpd`.

### Commenting / Style

* Same rules apply as assignments 1 and 2:
  * File header comments
  * Function header comments
  * Inline comments
  * Comment all variable declarations / constants

* No magic numbers!  Use `#define`.

* No global variables!

* Use whitespace.  This is incredibly unreadable, and I see a number of
  you doing this:

```
int main()
{
  // The user's age
  int age = 99;
  // Print a greeting
  printf("Hi user!\n");
  // Print the user's age
  printf("You are %d years old\n", age);
  // Exit the program
  exit(EXIT_SUCCESS);
}
```

* Use proper spelling, grammar, capitalization, and punctuation in your
  comments.

* If you're going to use end-of-line comments, align them:

**BAD**

```c
bool done = false; // Whether or not we're finished iterating
int age; // User's age
char* name = "jeff"; // User's name
```

**BETTER**

```c
bool done = false;   // Whether or not we're finished iterating
int age;             // User's age
char* name = "jeff"; // User's name
```

* Use 2 - 4 spaces for your indentation.  8 characters is *FAR* too much.

* Set your editor to expand tabs to spaces.  Tabs in existing code can be
  converted using the `expand` command.

* Lines should be no longer than about 78 characters.  Your editor can wrap
  your lines for you.

### Modularity

As always, your code should be as modular as possible.  If you can share code
between the client and server, do it.  Any common code should be placed in a
directory `common` in the root of your GitHub repository.

### Memory leaks

Don't forget to run all your code through `valgrind`.
Leaking memory = leaking marks. :)

### Error handling

At the third year level, you need to handle errors and exceptional events.
Examples include, but are not limited to:

* Invalid program arguments
* Missing required program arguments
* Connection errors
* Inability to allocate memory

Use the appropriate syslog levels, depending on the severity of the problem.

When possible, a program should gracefully recover and keep going.  For
instance, suppose your client is scanning a directory tree containing 1000
files.  Is it reasonable for the client to crash if it can't read a single
file due to a permission problem?

In this case, the proper course of action would be to print a warning (see the
`WARN` syslog level) and keep scanning.  Imagine if your operating system
crashed every time a minor error occurred (though, if you're using Windows,
it probably does... BAZINGA!)
