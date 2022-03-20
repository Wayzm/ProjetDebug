// .h
#ifndef TOOLS_H
#define TOOLS_H
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
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <execinfo.h>
#include <errno.h>

// Main function where we fork the child and have him run the executable 
void choice (char **argv);

// This function will give us the elf map of the executable ran by the child
void elf_mapping(char **argv);

//Tells us what signal it is
void c_c(int sig);

// This is to be used with sigaction, mainly to stop people users from using ctrl c
void segferror (int sig, siginfo_t *info, void *ctx);

// To verify that the set up is correct
void  prog_name(char **argv);

#endif
