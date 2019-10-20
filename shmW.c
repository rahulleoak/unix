#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
  char *str, *s;

  key_t key = ftok("shmfile",65);

  // shmget returns an identifier in shmid
  int shmid = shmget(key,1024,0666|IPC_CREAT);

  // shmat to attach to shared memory
  str = (char*) shmat(shmid,NULL,0);

  for (s = str; *s != '\0'; s++)
    putchar(*s);
  
  putchar('\n');
  *str = '*';

  //detach from shared memory
  shmdt(str);

  // destroy the shared memory
  shmctl(shmid,IPC_RMID,NULL);

  return 0;
}