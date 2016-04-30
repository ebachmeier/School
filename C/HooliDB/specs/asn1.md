**Computer Science 3357**  
**Fall 2015 - Assignment 1, Part 1**

## Assignment 1, Part 1 - Client (35%)

### Overview

In the first part of this assignment, you'll lay down the foundation for what
will become the Hooli Drive *client* -- that is, the program that will run on
a user's computer to sync all of his/her files with the Hooli Drive *server*.

Because we need a little more background knowledge before we get into network
programming, you won't be doing any network programming yet.  Instead, you'll
be writing the non-networking code that you'll need when it comes time to
communicate over the network.

This is a good practice in any event.  Socket (network) programming adds a
layer of complexity to a program.  Where possible, it is ideal to isolate your
networking code from the rest of the program.  This way, you can develop and
test the two largely independently of one another.

Hence, in this assignment, you'll write a relatively simple program that recursively scans a directory tree, computing CRC-32 checksums for each file found in the tree.  Your program will then dump a list of the files and their corresponding checksums to a comma-separated file.  Eventually, this information will be sent over the network to the Hooli Drive server.

### Prerequisites

* Ensure that you have set up the course VM and cloned the course starter repository.  See the Lab Manual for more details.

* Read the "Overview of Fall 2015 Assignments" document to familiarize yourself with what we're building this semester.

### Task

Notice the directory `client` in the root of your repository.  In this directory, create a file `client.c` that performs the following tasks:

* Accepts two arguments: a directory and a filename

* Scans the specified directory recursively, computing a CRC-32 checksum for each file in the directory or any of its subdirectories.

* Writes a comma-separated list of files and their corresponding CRC-32 checksums to the file specified on the command line.

* The filenames must be *relative* to the specified directory (see the sample output below)

* If any arguments are missing or invalid, prints an appropriate error message to `stderr` and exits with code `EXIT_FAILURE` (see `stdlib.h`).

* If no errors occur, your program should print nothing and exit with code `EXIT_SUCCESS`.

* Your program may ignore symbolic links -- it need only consider regular files.

### Sample output

Assume we have a directory tree `/home/vagrant/hooli` with the following files/structure:

```
$ tree ~/hooli

/home/vagrant/hooli
|-- code
|   |-- bin
|   |   `-- hello.o
|   `-- hello.c
|-- documents
|   `-- resume.pdf
`-- tax-returns
    |-- 2013-tax-return.pdf
    `-- 2014-tax-return.pdf
```

Executing the program on `~/hooli`:

```
$ ./client ~/hooli files.txt
$ cat files.txt
code/bin/hello.o,12345678
code/hello.c,87654321
documents/resume.pdf,11111111
tax-returns/2013-tax-return.pdf,22222222
tax-returns/2014-tax-return.pdf,33333333
```

Observe that the files listed in the text file are relative to `~/hooli` -- they do not include the prefix `/home/vagrant/hooli`.

**Note**: the order of the files in the text file is not important.  As long as all files and correct checksums are listed, the order is unimportant.

### Important notes

* You *MUST* create a file `Makefile` in the `client` directory that is capable of building your code simply by typing `make`.  
  * See the `hdb` directory for an example.

* The executable generated *MUST* be named `client`.

* You *MUST* use the following compilation flags: `-Wall` and `-Werror`.  `-Wall` turns on all warnings, and `-Werror` treats all warnings as errors.  Repeat this mantra: **WARNINGS ARE ERRORS.  WARNINGS ARE ERRORS.  WARNINGS ARE ERRORS**.
  * Yes, your favourite open-source software probably emits a slew of warnings during compilation.
  * When you become a prolific open-source developer managing a high-profile project, you can allow all the compiler warnings you like.
  * Until then, we code to a higher standard. :)

* You *MAY* use other compilation flags, but you *MUST* not disable any warnings or errors.

* You *MAY* use the `-std=gnu11` option to enable new C11 features and GNU extensions.  It's not 1980 anymore.  Let's join year 2015.

* You *SHOULD* use the `-g` option to compile your program with debugging symbols.  This allows you to use GDB to debug your code, and allows `valgrind` (more later) to print line numbers from which memory errors originated.

* You *SHOULD* compile your code with `-O0` during debugging to ensure that the compiler does not optimize out any lines, leading to confusion when running your code through GDB.

For example, you might invoke `gcc` as follows:

```
gcc -Wall -Werror -g -O0 -std=gnu11 -o client client.c -lz
```

* You *MUST* comment your code (I know, I know), including header comments at the top of each file, comments at the top of each function, and inline comments.  Each variable declaration should also be commented, briefly describing its purpose.

* Your final submission *MUST NOT* include any `.o` files, any executables, test data, or other binary files.  Keep your repository clean (this is worth marks).  See the discussion of the `.gitignore` file in the Git lab.  Use this file to your advantage.

### Tips

* To scan the directory tree, look up the functions `opendir`, `readdir`, and `closedir`.

* Use the `zlib` library to compute CRC-32 checksums.  Do not reinvent the wheel.
  * Install `zlib` and its header files in your VM by typing `sudo apt-get install zlib1g-dev`
  * See the `crc32` function in the zlib manual: http://www.zlib.net/manual.html#Checksum
  * You'll need to `#include <zlib.h>` in your program.
  * You'll need to add `-lz` at the end of your `gcc` command to link with the zlib library.
  
* Check your executable with `valgrind`, a memory-leak detector (among other things):
  *  Install it: `sudo apt-get install valgrind`
  *  Test your code: `valgrind --leak-check=full --show-leak-kinds=all ./client`
  *  Be sure to fix any memory leaks found, as they will lose you marks.
  *  #1 cause of memory leaks: forgetting to `free` memory that was `malloc`-ed.
  *  `valgrind` will tell you exactly which line number allocated the memory that was not freed.
  
* Modularize your code, where possible
  * `client.c` is where the `main` function should be found, but should not necessarily be the only file.  Use additional `.c` and `.h` files, when appropriate.
  * Putting all your code in `main` or in 1 or 2 functions will earn you a low grade.
  * Your functions should be short and tight.  Large functions performing all sorts of tasks will lose you marks.
  * In general, each function should perform a single task.  Refactor, refactor, refactor.  Refactor until your have a collection of short, cohesive functions.  
  * Finding that your functions aren't cohesive (i.e. they don't really relate to each other)?  Ask yourself if some of them should be grouped in a different file.

* See the `support` directory:
  * There is a file `crc32.rb` in this directory that you can use to compute a CRC-32 checksum on a file, to verify that your program is correctly calculating them
    * You may *NOT* simply `system` out and run this program from your code -- it is to help you validate the correctness of your output
    * Run the Ruby program as follows `ruby crc32.rb /path/to/some/file`