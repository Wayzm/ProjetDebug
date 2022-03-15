// .h
#ifndef TOOLS_H
#define TOOLS_H

void choice ();


//Catch signals
void c_c(int sig);

void tracer(pid_t Child);

void code (char **argc);

void segferror (int sig, siginfo_t *info, void *ctx);

void fperror (int sig, siginfo_t *info, void *ctx);

void  prog_name(char* binairename,char* cwd);
#endif
