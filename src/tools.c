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


void segferror (int sig, siginfo_t *info, void *ctx)
{
  printf("Unlucky le segfault owo ");
}

void fperror (int sig, siginfo_t *info, void *ctx)
{
  printf("Les cours de maths alors? uwu ");
}

// Test commit with new OS and VSCode


void choice ()
{
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK | O_NOCTTY ); // read non bloquant
    char key_press;
    size_t pread = read(STDIN_FILENO, &key_press, sizeof(char));
    struct sigaction pdt;
    switch(key_press)
    {
      case 1:
        // Segfaul
        pdt.sa_sigaction = segferror;
        pdt.sa_flags = SA_SIGINFO;

        char *tb[] = {"sfm", NULL};
        char *env[] = {"bin", NULL};

        pid_t child = 1;
        child = fork();

        if(child == 1)
        {
          ptrace(PTRACE_TRACEME); // The tracee is expected to be traced by its parent

          // In the manual, execve is the "usual" function used alongside PTRACE
          if (execve(tb[0], tb, env) == -1)
            perror("Exec of segfault programme failed");

          if (sigaction(SIGSEGV, &pdt, NULL))
          		perror("sigaction child");
        }
        else
        {
          ptrace(PTRACE_SEIZE, child, 0, PTRACE_O_TRACESYSGOOD); //

          memset(&pdt, 0, sizeof(struct sigaction));

          if(sigaction(SIGSEGV, &pdt, NULL) )
          {
            perror("sigaction parent");
          }

        }

        break;
      case 2:
        // catch SIGFPE
        pdt.sa_sigaction = fperror;
        pdt.sa_flags = SA_SIGINFO;
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
