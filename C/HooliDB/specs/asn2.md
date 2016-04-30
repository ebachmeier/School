**Computer Science 3357**  
**Fall 2015 - Assignment 2**

## Overview

In this assignment, you'll be delving into TCP socket programming to exchange
*metadata* between the Hooli client and server.

Using the Hooli Metadata Protocol (HMDP), your client will first authenticate
with a Hooli Metadata Server (HMDS), after which it will transfer its list of
files and checksums to the server.

The server will compare the list received against the list it has stored in
its database.  It will then send the client back an HMDP response message,
containing a list of the files that it needs the client to upload (i.e. files
that it doesn't currently have, or files that have changed since they were
last uploaded).

**Before moving on, please go read the 
[HMDP Protocol Specification](https://gist.github.com/jsuwo/e9f4c35e0e78a9662e59).**

## Objectives

This assignment will give you experience with:

* Implementing a protocol from a specification
* Socket programming with TCP
* Argument parsing with `getopt_long`
* Program logging with `syslog`
* Programming and debugging in C

## Labs

For this assignment, you will likely want to read labs 2 and 3, which cover
`syslog`/`getopt_long` and TCP socket programming, respectively.  I am
updating these labs and they will be posted later this week.

If you want to get started early, you can see 
[Beej's Guide to Network Programming](http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html)
for an introduction to socket programming.  Furthermore, Google can teach you about 
`syslog` and `getopt_long`.  Labs are provided as a courtesy, but please note that
you *are* capable of independent learning: I believe in you.

## A Word on Assignment 1

In this assignment, you have a choice of whether or not to build upon your
assignment 1 code.  You have two choices:

**Option 1: Build upon your assignment 1 code.**

In this case, you must complete part 0 and are eligible for a bonus of up to
10%.

**Option 2: Use the provided libraries that implement the assignment 1 functionality**

In this case, you must skip part 0, and are not eligible for a bonus.  The
provided libraries implement not only the code required for assignment 1, but
also the code in part 0 of this assignment.

**[Download the libraries here](https://gist.github.com/jsuwo/ff9e7a77a77c5f20649f)**

Now for the legalese.  If you choose to use your assignment 1 code:

* **It must be working to spec**

  You may need to make corrections, if you have bugs left over from
  assignment 1.  We will **try** to get your assignment 1 code returned to you
  at least 3-4 days prior to the submission of assignment 2.
  
* **Outstanding bugs may affect your assignment 2 mark**

  If you have bugs left over from assignment 1, they might affect the
  functionality of your assignment 2 submission.  We will not take into account
  *when* a bug was introduced (assignment 1 or assignment 2) when marking your
  code: a bug is a bug.

* **The bonus is *up to* 10%**

  You do not immediately get 10% for using your previous code.  It must be high 
  quality code, reasonably devoid of bugs, and the rest of your assignment must 
  achieve a grade of at least 80% to get any sort of bonus.  You must also
  implement part 0 (two simple functions).
  
For those choosing to use my library, it will be posted, along with some 
documentation on how to use it, later this week.

## Part 0 - Bonus (up to 10%)

*This part is for those using their assignment 1 code.  It is worth a bonus of
up to 10%.  If you are using my library code, skip this part.*

Modify `libhdb` to add the following functions:

```
char* hdb_authenticate(hdb_connection* con, const char* username, const char* password);
```

This function authenticates a user by password, and exchanges his/her username
and password for a randomly-generated, 16-byte token that will be passed by
the client in subsequent requests made after authentication.

If the specified username has a password stored in Redis, verify the specified
password.  If valid, generate and store a **unique**, random, 16-character,
alphanumeric (i.e. letters and numbers) token in Redis, associated with the
user.  Finally, return that token.

If the specified user does not exist, store the user and associated password
in Redis.  Then, generate a token as usual and return it.

Past tokens should not be preserved -- a newly-generated token should
overwrite an existing token for a given user, effectively invalidating any old
tokens that might exist after a user authenticates.

When storing the user's password and token in Redis, you will need to think of
a way to map usernames to passwords, and tokens to usernames, in such a way
that this storage does not clash with the storage of files and checksums.
For example, if the user's password is `hello`, and the user uploads a file
named `hello`, this file record should not overwrite the user's password.

This probably means you'll need separate hashes for passwords and tokens.

```
char* hdb_verify_token(hdb_connection* con, const char* token);
```

Verify the specified token, returning the username associated with the token,
if it is a valid token, or `NULL`, if it is not valid.

## Part 1 - Client (50%)

In this part, you'll modify your client to communicate using the HMDP protocol with a Hooli Metadata Server.

### Directory

In your GitHub repository, you should already have a directory `client`.  You 
should also already have a `Makefile` capable of building an executable `client`
within this directory, simply by typing `make`.

If your directory is not named `client`, you will lose marks.  If the
executable generated by your `Makefile` is not named `client`, or is not
generated in the `client` directory, you will lose marks.  Please follow
directions carefully.  This allows us to use scripts to partially automate our
marking.  This way, everyone wins.  We mark the assignments faster, which
makes us happy, and you get your assignment back faster, which makes you happy
(hopefully).

### Command line arguments

**Use the `getopt_long` function** to modify your client to accept the
following short and long options:

* `-s HOSTNAME` / `--server HOSTNAME`

  Specifies the server's hostname.  If not given, default to `localhost`.

* `-p PORT` / `--port PORT`

  Specifies the server's port.  If not given, default to `9000`.

* `-d DIR` / `--dir DIR`

  Specifies the Hooli root directory.  If not given, default to `~/hooli`.

* `-v`/ `--verbose`

  Enable verbose output: set the syslog level to `DEBUG`.  Otherwise, it should default to `INFO`.

Your client should also *require* two arguments: `USERNAME` and `PASSWORD`.

For instance, we should be able to invoke your client as follows:

```
./client jeff password
```

This will connect to the server at `localhost` on port `9000`, authenticating with username
`jeff` and password `password`.  It should then send the file data from the directory tree
rooted at `~/hooli`.

Alternatively, we might invoke it as follows:

```
./client -v -s example.com --port 5555 --dir /tmp jeff password
```

It would then connect to the server at `example.com` on port `5555`, log
output in verbose mode, and authenticate with username `jeff` and password
`password.`  Finally, it would send the file data from the directory tree
rooted at `/tmp`.

Notice the mix of short and long options above.  Also, note that options can appear in
any order (but, of course, the username and password arguments always come at the end
in the given order).  `getopt_long` makes all of this easy for you.

Being required arguments, if the username and password arguments are missing, an appropriate 
error should be printed with an appropriate, non-zero return value to the operating system.

### Functionality

Modify your client to:

* Scan the Hooli root directory (as in assignment 1), generating a list of files/checksums.
  Preferably, you would generate a linked list in memory rather than generating an output
  file (as in assignment 1).  However, if you wish, you may write the file list to a 
  temporary file and then read it into memory prior to transmission to the server.

  **NOTE**: your client should no longer accept an output filename as an argument.  If 
  you're going to write the file list to a file, generate a 
  [temporary file](http://www.gnu.org/software/libc/manual/html_node/Temporary-Files.html).

* Establish a TCP connection with the Hooli server.

* Issue an `AUTH` request.

* Send the list of files/checksums in a `LIST` request to the server.  Again, this can
  (preferably) come from a linked list in memory, or can be read from the temporary
  file you generated.

* Close the connection.

* Print the list of files requested by the server.  If the server requests no files,
  print an appropriate message.

### Program output

In this assignment, we will not yet be uploading files, so your client should
simply print a list of the files requested by the server.

All program output must use `syslog`, and should be printed to the console
(see the syslog lab).  Any debugging information should use the `DEBUG` syslog
level.  This way, when you need to troubleshoot, you can pass the `--verbose`
flag to your program.  When we want to mark and don't want to see all the
noise, we can simply omit the flag.

Regular program output should generally use the `INFO` level, should be clean,
and should be informative.  For example, in verbose mode, your program might
print something like the following:

```
Oct 10 05:00:00 cs3357 client[9392]: Scanning Hooli directory: ~/hooli
Oct 10 05:00:00 cs3357 client[9392]: * bin/program.bin (FACEB00C)
Oct 10 05:00:00 cs3357 client[9392]: * doc/resume.txt (CAFED00D)
Oct 10 05:00:10 cs3357 client[9392]: Connecting to server
Oct 10 05:00:11 cs3357 client[9392]: Sending credentials
Oct 10 05:00:12 cs3357 client[9392]: Authentication successful
Oct 10 05:00:13 cs3357 client[9392]: Uploading file list
Oct 10 05:00:15 cs3357 client[9392]: Server requested the following files:
Oct 10 05:00:15 cs3357 client[9392]: bin/program.bin
Oct 10 05:00:15 cs3357 client[9392]: doc/resume.txt
```

On the other hand, when `--verbose` is not given, your program output would
be, accordingly, less verbose, but still informative:

```
Oct 10 05:00:00 cs3357 client[9392]: Scanning Hooli directory: ~/hooli
Oct 10 05:00:10 cs3357 client[9392]: Connecting to server
Oct 10 05:00:11 cs3357 client[9392]: Authentication successful
Oct 10 05:00:12 cs3357 client[9392]: Uploading file list
Oct 10 05:00:14 cs3357 client[9392]: Server requested the following files:
Oct 10 05:00:14 cs3357 client[9392]: bin/program.bin
Oct 10 05:00:14 cs3357 client[9392]: doc/resume.txt
```

In either case, you **MUST** print the list of files requested by the server.

## Part 2 - Metadata Server (50%)

In this part, you'll create the Hooli Metadata Server.

### Directory

In your GitHub repository, create a directory `hmds`.  You must create a
`Makefile` that is capable of building an executable `hmds` within this
directory, simply by typing `make`.

If your directory is not named `hmds`, you will lose marks.  If the executable
generated by your `Makefile` is not named `hmds`, or is not generated in the
`hmds` directory, you will lose marks.

### Command line arguments

**Use the `getopt_long` function** to allow your server to accept the
following short and long options:

* `-p PORT` / `--port PORT`

  Specifies the port on which to listen.  If not given, default to `9000`.

* `-r HOSTNAME` / `--redis HOSTNAME`

  Specifies the hostname of the Redis server.  If not given, default to
  `localhost`.

* `-v`/ `--verbose`

  Enable verbose output: set the syslog level to `DEBUG`.  Otherwise, it
  should default to `INFO`.

For instance, we should be able to invoke your server as follows:

```
./hmds
```

This will start the server, listening on the default port `9000`.  The server
will connect to the Redis server at `localhost`.

Alternatively, we might invoke it as follows:

```
./hmds -v --port 5555 -r example.com
```

It would then start listening on port 5555, log output in verbose mode, and
connect to the Redis server at `example.com`.

Once again, notice the mix of short and long options above and note that
options can appear in any order: use `getopt_long`.

### Functionality

Your server should:

* Listen on the specified port for TCP connections.

* When a connection comes in, print the connecting IP address.

* If an `AUTH` request comes in, print the username, then verify the
  username/password using

```
char* hdb_authenticate(char* username, char* password)
```

* If successful, return a `200` response containing the token returned by 
  `hdb_authenticate`.  See the `HMDP Protocol` document for details on the
  `200` message (and all other messages).

* If unsuccessful, return a `401` response.

* If a `LIST` message comes in, verify the given token using 
  
```
bool hdb_verify_token(const char* token)
```

  * If not valid, return a `401` response.

  * Otherwise, print the list of files sent by the client (in `verbose` mode)

  * Compare the user's files stored in Redis against the list sent by the
    client.  Do **NOT** change the user's files in Redis.  We only store data
    when the files actually get uploaded in assignment 3 (why?).

  * If the client sent any files that are not in Redis, or that have checksums
    that are different than those in Redis, return the list of said filenames in
    a `302` response.

  * If there are no new or modified files, return a `204` response.

* Print the list of files the server is requesting.  If the server requests no
  files, print an appropriate message.

* Close the connection

### Program output

As with the client, all program output must use `syslog`, and should be
printed to the console (see the syslog lab).  Any debugging information should
use the `DEBUG` syslog level.

Regular program output should generally use the `INFO` level, should be clean,
and should be informative.  For example, in verbose mode, your program might
print something like the following:

```
Oct 10 05:00:00 cs3357 hmds[9392]: Server listening on port 9000
Oct 10 05:00:05 cs3357 hmds[9392]: Incoming connection from 127.0.0.1
Oct 10 05:00:06 cs3357 hmds[9392]: Username: jeff
Oct 10 05:00:07 cs3357 hmds[9392]: Authentication successful
Oct 10 05:00:08 cs3357 hmds[9392]: Receiving file list
Oct 10 05:00:08 cs3357 hmds[9392]: * bin/program.bin, CAFED00D
Oct 10 05:00:08 cs3357 hmds[9392]: * doc/resume.txt, FACEB00C
Oct 10 05:00:10 cs3357 hmds[9392]: Requesting files:
Oct 10 05:00:10 cs3357 hmds[9392]: * bin/program.bin
Oct 10 05:00:10 cs3357 hmds[9392]: * doc/resume.txt
Oct 10 05:00:11 cs3357 hmds[9392]: Connection terminated
```

On the other hand, when `--verbose` is not given, your program output would
be, accordingly, less verbose, but still informative:

```
Oct 10 05:00:00 cs3357 hmds[9392]: Server listening on port 9000
Oct 10 05:00:05 cs3357 hmds[9392]: Incoming connection from 127.0.0.1
Oct 10 05:00:06 cs3357 hmds[9392]: Username: jeff
Oct 10 05:00:08 cs3357 hmds[9392]: Receiving file list
Oct 10 05:00:10 cs3357 hmds[9392]: Requesting files:
Oct 10 05:00:10 cs3357 hmds[9392]: * bin/program.bin
Oct 10 05:00:10 cs3357 hmds[9392]: * doc/resume.txt
Oct 10 05:00:11 cs3357 hmds[9392]: Connection terminated
```

In both cases, you **MUST** print the list of files requested by the server.

## General requirements

### Repository structure

I'm including this paragraph because I know at least 20% of you will do this.

Do *NOT* copy your code from assignment 1 to a new directory.  In a source
code repository, you simply edit the existing code, and push the changes to
GitHub.  You will lose 5% of your mark if you create, for example, an `asn2`
directory and copy all your code into it.  Why?  Because, by doing so, you're
communicating to me that you've totally missed the point of source control.

Long story short: just edit the code you already have in your GitHub
repository.  Do not copy code.

Your directory structure should be:

```
client/     - All client code
common/     - If you have any shared code between the client and server, it goes here
hdb/        - Your database library
hmds/       - Your server code
```

### Commenting / Style

* Same rules apply as assignment 1:
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
it probably does... ba-dum-tssshhh!)
