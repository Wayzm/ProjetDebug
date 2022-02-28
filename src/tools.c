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

int cnt_int = 0;
int cnt_segv = 0;
int cnt_fpe = 0;
int cnt_ill = 0;

struct sigaction sgt;

void sig_int ()
{
  
}

void c_c()
{
  int sig;
	switch(sig)
	{
		case SIGINT:
			printf("sigint found %d\n", sig);
			cnt_int++;
			break;
		case SIGSEGV:
			printf("sigsegv found %d\n", sig);
			cnt_segv++;
			break;
		default:
			printf("No errors ?\n");
	}
}

void segferror (int sig, siginfo_t *info, void *ctx)
{
  printf("Error found ! ");
}

void fperror (int sig, siginfo_t *info, void *ctx)
{
  printf("Les cours de maths alors? uwu ");
}

// Test commit with new OS and VSCode


void choice ()
{
    char key_press;
    size_t pread = read(STDIN_FILENO, &key_press, sizeof(char));
    switch(key_press)
    {
      case 1:
        // Segfault
        sgt.sa_sigaction = segferror;
        sgt.sa_flags = SA_SIGINFO;

        char *tb[] = {"sfm", NULL};
        char *env[] = {"bin", NULL};

        pid_t child = 1;
        child = fork();

        if(child == 1)
        {
          ptrace(PTRACE_TRACEME); // The tracee is expected to be traced by its parent

          // In the manual, execve is the "usual" function used alongside PTRACE
          if (execve(tb[0], tb, env) == -1)
            perror("Exec failed");

          if (sigaction(SIGSEGV, &sgt, NULL))
          		perror("sigaction child");
        }
        else
        {
          ptrace(PTRACE_SEIZE, child, 0, PTRACE_O_TRACESYSGOOD); //

          memset(&sgt, 0, sizeof(struct sigaction));

          if(sigaction(SIGSEGV, &sgt, NULL) )
          {
            perror("sigaction parent");
          }

        }

        break;
      case 2:
        // catch SIGFPE
        sgt.sa_sigaction = fperror;
        sgt.sa_flags = SA_SIGINFO;
        break;
      case 3:
        break;
      case 'q':
        break;
      default:
        printf("How to use : \n \n Press 1 to catch a SIGSEGV. \n Press 2 to catch SIGFPE. \n Press q to exit.");
      break;
    }
}
