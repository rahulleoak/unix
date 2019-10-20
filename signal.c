#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sighup();
void sigint();
void sigquit();

void main()
{
  int pid;

  pid=fork();
  if (pid == 0)
  {
    printf("child\n");
    signal(SIGHUP,sighup);
    signal(SIGINT,sigint);
    signal(SIGQUIT, sigquit);
    for(;;);
  }
  else
  {
    sleep(3);
    printf("\nPARENT: sending SIGHUP\n\n");
    kill(pid,SIGHUP);
    sleep(3);

    printf("\nPARENT: sending SIGINT\n\n");
    kill(pid,SIGINT);
    sleep(3);
    printf("\nPARENT: sending SIGQUIT\n\n");
    kill(pid,SIGQUIT);
    sleep(3);
  }
}

void sighup()
{
  signal(SIGHUP,sighup);
  printf("CHILD: I have received a SIGHUP\n");
}

void sigint()
{
  signal(SIGINT,sigint);
  printf("CHILD: I have received a SIGINT\n");
}

void sigquit()
{
  printf("My DADDY has Killed me!!!\n");
  exit(0);
}