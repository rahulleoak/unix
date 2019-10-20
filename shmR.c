#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
  char c;
  char *str, *s;
  key_t key = ftok("shmfile",65);

  // shmget returns an identifier in shmid
  int shmid = shmget(key,1024,0666|IPC_CREAT);

  // shmat to attach to shared memory
  str = (char*) shmat(shmid,NULL,0);

  s=str;
  for(c='a';c<='z';c++)
  {
    *s++=c;
    *s='\0';
  }

  while(*str!='*')
    sleep(1);

  //detach from shared memory
  shmdt(str);
}