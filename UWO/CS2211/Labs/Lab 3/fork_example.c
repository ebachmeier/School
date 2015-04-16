#include <unistd.h>   /* Symbolic Constants */
#include <stdio.h>    /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>   /* General Utilities */
#include <string.h>   /* General Utilities */

int main()
{
  char buf[100];
  int  childpid; /* variable to store the child's pid */
  int  retval;   /* child process: user-provided return code */
  int  status;   /* parent process: child's exit status */

  /* only 1 int variable is needed because each process would have its own
     instance of the variable.  Here, 2 int variables are used for clarity */

  /* now create new process */
  childpid = fork();

  if (childpid >= 0) /* fork succeeded */
  {
    if (childpid == 0) /* fork() returns 0 to the child process */
    {
      sprintf(buf, "<> <> CHILD: I am the child process!\n");
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "<> <> CHILD: Here's my PID: %d\n", (int) getpid());
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "<> <> CHILD: My parent's PID is: %d\n", (int) getppid());
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "<> <> CHILD: The value of my copy of childpid is: %d\n", childpid);
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "<> <> CHILD: Sleeping for 1 second...\n");
      fwrite(buf, strlen(buf), 1, stdout);

      sleep(1); /* sleep for 1 second */

      sprintf(buf, "<> <> CHILD: Enter an exit value (0 to 255): ");
      fwrite(buf, strlen(buf), 1, stdout);

      scanf(" %d", &retval);

      sprintf(buf, "<> <> CHILD: Goodbye!\n");
      fwrite(buf, strlen(buf), 1, stdout);

      exit(retval); /* child exits with user-provided return code */
    }
    else /* fork() returns new pid to the parent process */
    {
      sprintf(buf, "  #   PARENT: I am the parent process!\n");
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "  #   PARENT: Here's my PID: %d\n", (int) getpid());
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "  #   PARENT: The value of my copy of childpid is %d\n", childpid);
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "  #   PARENT: I will now wait for my child to exit.\n");
      fwrite(buf, strlen(buf), 1, stdout);

      wait(&status); /* wait for child to exit, and store its status */

      sprintf(buf, "  #   PARENT: Child's exit code is: %d\n", status/256);
      fwrite(buf, strlen(buf), 1, stdout);

      sprintf(buf, "  #   PARENT: Goodbye!\n");
      fwrite(buf, strlen(buf), 1, stdout);

      exit(0);  /* parent exits */
    }
  }
  else /* fork returns -1 on failure */
  {
    fprintf(stderr, "Error: unsuccsseful fork\n"); /* display error message */
    exit(0);
  }
}
