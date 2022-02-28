// .h
#ifndef TOOLS_H
#define TOOLS_H

void choice ();


//Catch and count signals
void c_c ();

void tracer(pid_t Child);

void code (char **argc);

void segferror (int sig, siginfo_t *info, void *ctx);

void fperror (int sig, siginfo_t *info, void *ctx);
#endif
