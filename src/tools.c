#include <stdio.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>
#include <fcntl.h>

// PTRACE_GETSIGINFO
// sigaction
// PTRACE_SETOPTIONS

char *buff[]; // buffer for the backtrace to get the function name 

struct sigaction sgt;

// This functions will get the executable file name for the debugger
void prog_name(char* binairename, char* cwd)
{
  if(getcwd(cwd,sizeof(cwd)) != NULL)
  {
    printf("Double check that your file is in the right directory, which is where the makefile is. \n");

    if(read(0, binairename, 128) < 0)
    {
      printf("An error occurred in the read.\n");
    }

    else // Now we check if the fileis is in the cwd
      {
        if(access( strcat(cwd,binairename), X_OK ) == 0 ) 
        {
          //file is here
          printf("File name is good and file was found and can be executed ! \n");
        } 
        
      else 
        {
          // file doesn't exist
          printf("File name is good but file was not found or does not have executable permission! \n");
        }
      }
  }
}


// Sighandler that will find the errors, will stop at the first error found.
void c_c(int sig)
{
	switch(sig)
	{
		case SIGILL:
			printf("sigill found %d\n", sig);
			break;
		case SIGSEGV:
			printf("sigsegv found %d\n", sig);
			break;
    case SIGFPE:
			printf("sigfpe found %d\n", sig);
			break;
		default:
			printf("No errors ?\n");
	}
}

void sigerror (int sig, siginfo_t *info, void *ctx)
{
  printf("Error found ! ");
}

// Test commit with new OS and VSCode


void choice (char* binairename)
{
    char key_press;
    size_t pread = read(STDIN_FILENO, &key_press, sizeof(char));
    char *tb[] = {"sfm fpe", NULL};
    char *env[] = {"bin", NULL};
    sgt.sa_sigaction = sigerror;
    sgt.sa_flags = SA_SIGINFO;

    switch(key_press)
    {
      case 1:
        pid_t child = fork();

        if(child == 0)
        {
          ptrace(PTRACE_TRACEME,child, NULL, NULL); // The tracee is expected to be traced by its parent

          // In the manual, execve is the "usual" function used alongside PTRACE
          if (execvp(tb[0], tb) == -1)
            perror("Exec failed");

          if (sigaction(SIGSEGV, &sgt, NULL))
          		perror("Wrong use of memory! \n");
          
          if (sigaction(SIGFPE, &sgt, NULL))
          		perror("Math error found! \n");
                    
          if (sigaction(SIGILL, &sgt, NULL))
          		perror("Illegal instruction found! \n");
        }
        else
        {
          ptrace(PTRACE_SEIZE, child, 0, PTRACE_O_TRACESYSGOOD); //

          memset(&sgt, 0, sizeof(struct sigaction));

          c_c(SIGCHLD); // SIGCHLD allows us to know when the child ends

        }

        break;
      case 2:

        break;
      case 'r':
        
        break;
      case 'q':
        break;
      default:
        printf("How to use : \n \n Press 1 to catch a SIGSEGV. \n Press 2 to catch SIGFPE. \n Press q to exit.");
      break;
    }
}
