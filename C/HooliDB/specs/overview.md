**Computer Science 3357**  
**Fall 2015 - Overview of Fall 2015 Assignments**

## Background - A Letter from the Hooli CEO

> Dear Sir/Madam,
> 
> Welcome, new employee, to Hooli!  As a multi-billion dollar corporation,
> and the brains behind some of the Internet's most cutting-edge services,
> you have no doubt heard of us and are probably intimately familiar with
> many of our offerings.  We're excited now to have you on board to help us
> innovate and remain a market leader in the coming years.
>
> In the last decade, we've seen "the cloud" enter the public lexicon.
> Users have come to expect instant access to files and services from any
> device they might be using.  Services like DropBox have proven abundantly
> popular, providing users a simple way to back up their files, and sync them
> amongst all their devices.  While Hooli has pioneered many Internet services,
> we are, admittedly, late to the personal file synchronization market.
> 
> That's where you come in.  As Program Manager of the Hooli Drive division,
> you'll be overseeing the development of our new file synchronization tool,
> allowing users an unparalleled ability to quickly and easily back up their
> most important data, and sync them amongst all their devices seamlessly.
> 
> I've enclosed a tentative game plan for implementing Hooli Drive over the
> course of the next few months (subject to change, of course).  Please review
> it at your earliest leisure.  We look forward to having you on board.
> 
> Yours Truly,
> 
> Gavin Belson  
> Hooli CEO

## Building Hooli Drive

### Terminology

Before we go further, let's define more precisely two terms that we'll be
using a lot in this course: *client* and *server*.

**Server**

A program that runs on a system, waiting for connections.  When it receives a
connection, it typically provides some sort of service to the connecting
program.  For instance, a *Web server* might serve up a Web page.  An *email
server* might allow someone to download all of their new mail.

**Client**

A program that runs on a computer that makes a connection to a *server*, and
consumes its services.  While the server sits around waiting for connections,
it is the client that initiates the connection to the server.

A Web browser is an example of a client.  It connects to a Web server,
requests a Web page, downloads the page from the server, and displays it to
the user.

### Planning the System

Think for a moment about how a file synchronization system should work.  For
now, don't worry about syncing files back to the client from the server.
We'll just worry about one-way synchronization -- from the client up to the
server.

#### Naïve implementation

A first attempt might look like this (shown in *pseudocode*):

**Client**

```ruby
filenames = scan_directory(dir)  # Get list of all files in directory 'dir'

for f in filenames do            # For each file found
  upload_file(f)                 # Upload the file to the server
end
```

Our server implementation would then be quite simple:

**Server**

```ruby
while (true)
  file = wait_for_uploaded_file()  # Wait for an incoming file
  save_file(file)                  # When received, save it on the server
end
```

This works, but it's wasteful.  If a large file has not changed since we last
synced it, we don't want to waste time uploading it again.  So, we need a way
to determine whether or not a file has changed.  If and only if it has
changed, we upload it to the server.

#### Detecting File Changes

How can we detect when a file has changed?  We could check the file's size,
but that's not necessarily a reliable way to detect changes.  Think how a
file's size would change if one bit in the file was flipped from 0 to 1, for
example.  We could instead use the file's last modification timestamp, but
dates on files are easily manipulated.

Instead, we'll use a *checksum*, a value that we compute from a chunk of data
(in this case, the contents of a file) that allows us to determine whether or
not the data has changed.  As we'll see later in the course, checksums are
used in computer networking to determine if data was corrupted (changed) in
transmission:

**Sender**

```ruby
D = get_data()      # Some data that we want to send
C = checksum(D)     # Compute its checksum

send(D,C)           # Send both the data and checksum
```

**Receiver**

```ruby
D, C = receive_data_and_checksum()       # Receive the data and checksum
C_prime = checksum(D)                    # Compute the checksum of the data

if C == C_prime                          # If computed checksum matches received checksum
  print "Data was received successfully" # Conclude data has *probably* not changed
else                                    
  print "Error!  Data has changed!"      # Otherwise, data was changed in transmission
end
```

In implementing Hooli Drive, we'll use checksums not so much for error
detection, but instead to determine whether files have changed and need to be
re-uploaded to the server.  For example, suppose a user has two files:

* `file1.txt` with checksum `AAAAAAAA`
* `file2.txt` with checksum `BBBBBBBB`

Suppose now that these files are uploaded to the Hooli Drive server.  The
server will store the files on disk, and store the filenames and their
corresponding checksums in a database.

Now suppose that the user edits his/her copy of `file1.txt`.  The checksum
therefore changes, say, to `CCCCCCCC`.  The user now has the following files:

* `file1.txt` with checksum `CCCCCCCC`
* `file2.txt` with checksum `BBBBBBBB`

However, the server has the following files:

* `file1.txt` with checksum `AAAAAAAA`
* `file2.txt` with checksum `BBBBBBBB`

When the user runs the Hooli Drive client on his/her computer, the client will
send a list of filenames and checksums to the server.  The server will check
its database, and send back a list of files that need to be (re-)uploaded.

In this case, the server would send a message to the client indicating that it
should upload `file1.txt`, because it does not already have a copy of
`file1.txt` with checksum `CCCCCCCC`.  However, it already has a copy of
`file2.txt` with checksum `BBBBBBBB`, so the client does not need to waste
time uploading a file it already has.

As we'll see later in the course, checksums are not perfect -- some changes
can go undetected -- but, for our purposes, they'll do just fine.

#### Second Attempt at an Implementation

Let's see how our client/server implementation might look now:

**Client**

```ruby
filenames = scan_directory(dir)        # Get list of all files in directory 'dir'
files_and_cksums = []                  # Array to store filenames and their checksums

for f in filenames do                  # For each file found
  files_and_cksums += [f, checksum(f)] # Store entry containing the filename and its checksum
end

upload_list(files_and_cksums)          # Upload the filenames and checksums to the server
files_to_upload = wait_for_list()      # Wait for server to return list of filenames it needs

for f in files_to_upload do            # For each such file
  upload_file(f)                       # Upload it to the server
end
```

Our server implementation might then be as follows:

**Server**

```ruby
while (true) do
  files_and_cksums = wait_for_file_list()  # Wait for client to send list of files/checksums
  files_needed = []                        # Array to store files needed from client
  
  # For each <filename, checksum> pair received
  for each [filename, checksum] in files_and_cksums do
    
    # If the file is either not in the database, or the checksum we're storing
    # for it does not match that sent by the client, then make a note that
    # we'll need the client to (re-)upload the file.
    if (! database.has_file(filename)) ||
       (database.load_checksum(filename) != checksum)
      files_needed += filename
    end
    
  end
  
  upload_list(files_needed)          # Send the list of files needed to the client
  
  # Wait for each file needed
  for i = 1 to files_needed.count do 
  
    file = wait_for_uploaded_file()  # Wait for an incoming file
    save_file(file)                  # When received, save it to disk
    
    # Store the filename and its checksum in the database
    database.store(file.name, checksum(file))
  end
  
end
```

Study this pseudocode until you understand what's going on.  This will be the
simple algorithm we'll use to build Hooli Drive.  In practice, things would be
much more complex.  For instance, we might checksum *chunks* of files, so that
we didn't have to re-upload an entire file when only a small piece of it had
changed.  However, for this course, we'll start small.

## Overview of Assignments

Here's a tenative overview of what we'll be doing in the assignments this
semester.

### Assignment 1 - C Refresher / Hooli Drive foundation

We understand that you're probably a little rusty in C.  That's OK.  In
Assignment 1, you'll get started on the foundation code needed for Hooli
Drive.  In the process, you'll review your C programming and debugging skills.
You won't write any networking code quite yet -- that's for later -- but
you'll get started on both the Hooli Drive client and server code.

You'll learn about checksums and you'll generate CRC-32 checksums with a
popular library, zlib.  You'll also make use of Redis, a popular,
network-based, key-value store, to provide lightning-fast data storage for the
Hooli Drive server.

### Assignment 2 - Basic socket programming

In this assignment, you'll get your client and server talking.  Your client
will send a list of files and their corresponding checksums to the server.
The server will compare this information with the files it has stored in
Redis, and will tell the client which files it should send.

You'll learn about socket programming with TCP, implement a basic network
protocol, parse arguments with `getopt_long`, and add logging with `syslog`.

Along the way, you'll also learn how to debug your client and server with GDB,
inspect network communication with Wireshark, and learn how to use the popular
tool `tmux` to help you develop your client and server effectively.

### Assignment 3 - Fast, reliable file synchronization

DropBox is great.  Hooli Drive wants to be *better*.  More importantly, Hooli
Drive wants to be *faster*.  At Hooli, we don't accept barriers -- we break
them down.  TCP wants to limit our file transfer speeds?  Then forget TCP.
We'll use UDP.  Still, we need our file transfers to be ultra-reliable.  We
can't have users losing data, after all.  So, we'll need to be crafty about
how we make use of UDP, being an unreliable protocol.

In the assignment, you'll make the world a better place... through minimal,
message-oriented transport layers. You'll implement reliable file transfer
over UDP so that files can be exchanged between the client and server with
lightning speed.  In doing so, you'll learn about socket programming with UDP,
implement a binary network protocol, and better understand the Go-Back-N ARQ.

By thinking outside the box, we'll leave Dropbox in the dust.

### Assignment 4 - Concurrency in the cloud

We're almost ready to bring Hooli Drive to market.  But there's just a tiny
hitch: our server only supports one client at a time.  To scale, we need to
support millions of client syncing concurrently.  We've also been developing
on our local systems so far.  We need an infrastructure capable of rapid
scaling.  It's time to deploy our server to the cloud!

In this assignment, you'll learn about how a single process can support
multiple (many!) connections using the `epoll` system call.  You'll then
modify your server to accept multiple connections with `epoll`.  Along the
way, you'll set up an instance (virtual server) in the cloud using Amazon
Elastic Compute Cloud (EC2) and deploy your Hooli Drive server to your EC2
instance.