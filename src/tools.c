#define UNW_LOCAL_ONLY

#include "tools.h"


struct sigaction sgt;

void print_trace ()
{
  void *array[2046];
  char **strings;
  int size, i;

  size = backtrace (array, 2046);
  strings = backtrace_symbols (array, size);
  if (strings != NULL)
  {

    printf ("Obtained %d stack frames.\n", size);
    for (i = 0; i < size; i++)
      printf ("%s\n", strings[i]);
  }
}

void elf_mapping(char **argv)
{
  void* start = NULL;
	int i, fd;
	struct stat stat;
	char *strtab;
	int n;

  printf("Let's look at what the elf file tells us ! \n");
  sleep(1);

	// Mapped bin
	fd = open(argv[1], O_RDONLY, 660);
	if(fd < 0)
		perror("Didnt open");

	fstat(fd, &stat); // its size

	start = mmap(0, stat.st_size, PROT_READ , MAP_FILE | MAP_SHARED, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("No mapping done");
		exit(0);
	}

	Elf64_Ehdr* hdr = (Elf64_Ehdr *) start;
	Elf64_Sym* sym;

  // Making sure it's an elf file
	printf("First four bytes: %x '%c' '%c' '%c'\n", *(char*)start,*((char*)start+1), *((char*)start+2), *((char*)start+3));


  // Offset found on the header
	Elf64_Shdr* headeroff = (Elf64_Shdr *)((char *)start + hdr->e_shoff);


	for (i = 0; i < hdr->e_shnum; i++)
	{
		// For symbol tab
		if (headeroff[i].sh_type == SHT_SYMTAB) 
    {

			sym = (Elf64_Sym *)((char *)start + headeroff[i].sh_offset);
			n = headeroff[i].sh_size / headeroff[i].sh_entsize;
			strtab = (char*)((char*)start + headeroff[headeroff[i].sh_link].sh_offset);
		}
	}

	for (i = 0; i < n; ++i) 
  {
		printf("%d: %s\n", i, strtab + sym[i].st_name);
	}
}



void prog_name(char **argv)
{
  printf("Double checking that your file is in the right directory, which is where the makefile is. \n");

  if(argv[1] == NULL)
  {
    printf("Please input your executable like this : ./exemple, after typing ./debug \n");
    exit(0);
  }

  else // Now we check if the file is is in the cwd and executable with X_OK
  {
    sleep(2);
    if(access(argv[1], X_OK ) == 0 && access(argv[1],F_OK) == 0)
    {
      //file is here
      printf("File name is good and file was found and can be executed ! \n");
    }
        
    else 
    {
      // file doesn't exist
      printf("File name is good but file was not found or does not have executable permission! \n");
      exit(0);
    }
  }
}


// Sighandler that will tell us what the erros is 
void c_c(int sig)
{
  switch(sig)
  {
    case 8:
      printf("Error found was of floating point nature. \n");
      break;
    case 11:
      printf("Error found was due to invalid memory access ! \n");
      break;
    case 4:
      printf("Eroor was due to an illicit use of instructions ! \n");
      break;
    case 5:
      printf("Error was due to a trap due to the tracing ! \n");
      break;
    case 6:
      printf("CHILD WAS ABORTED ! \n");
      break;
    case 3: 
      printf("Child quit ! \n");
      break;
    default:
      printf("This error was not documented,but you can look it up with kill -l ! \n");
      break;
  }
}

void sigerror (int sig, siginfo_t *info, void *ctx)
{
  printf("Nope ! \n ");
}

// Test commit with new OS and VSCode


void choice (char  **argv)
{
  pid_t s;

  char *const filename[] = {argv[1], NULL};
  int status;
  size_t pread;
  sgt.sa_sigaction = sigerror;
  sgt.sa_flags = SA_SIGINFO;

  pid_t child = fork();

  if(child == 0)
  {
    ptrace(PTRACE_TRACEME,child, NULL, NULL); // The tracee is expected to be traced by its parent
    int pid_child = getpid();
    printf("Child PID is %d\n", pid_child);

    // In the manual, execve is the "usual" function used alongside PTRACE
    if (execve(filename[0], filename, NULL) == -1)
      perror("Exec failed");
    
    print_trace();
  }
  else
  {
      // TRACESYSGOODto avoid sigtrap
      ptrace( PTRACE_SEIZE , child , 0 , PTRACE_O_TRACESYSGOOD );
      s = waitpid( child , &status , WUNTRACED | WCONTINUED );
      
      if( s == -1 )
      {
        printf("Waitpid failed ! \n");
        exit(0);
      } 

      if (WIFEXITED(status)) 
      {
        printf("Child finished, status=%d\n", WEXITSTATUS(status));
        c_c(WTERMSIG(status));
      } 

      else if (WIFSIGNALED(status)) 
      {
        printf("Child killed by signal %d\n", WTERMSIG(status));

        c_c(WTERMSIG(status));
      }

      else if (WIFSTOPPED(status)) 
      {
        printf("Child stopped by signal %d\n", WSTOPSIG(status));
        c_c(WSTOPSIG(status)); 
      }
      else if (WIFCONTINUED(status)) 
      {
        printf("Child is processing... \n");
        sleep(5);
        kill(child,9);
        printf("Child has been killed. \n");
      }
      
      sleep(1);
      
    }
  elf_mapping(argv);

  kill(child,9);
  
  char key_press;
  while(1)
  {
    if (sigaction(SIGINT, &sgt, NULL))
      perror("Cant catch those sigints :'( \n");
    
    printf("Press q to quit ! \n");
    read(STDIN_FILENO,&key_press,sizeof(char));
    
    if(key_press == 'q')
    {
      exit(0);
    }
    else 
    {
      printf("Press q please :'(");
    }
  }
}
