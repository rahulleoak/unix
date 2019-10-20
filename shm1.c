#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdlib.h>

#define MIN 1
#define MAX 2


int Cscore=0, Dscore=0;

void printscores(){

	printf("-----------------Current Scores-----------------\n");
	printf("C Score:%d\n",Cscore);
	printf("D Score:%d\n",Dscore);
}

int main(){

	int shmid1,shmid2;
	int *shmptr1,*shmptr2;
	int c,d;
	int flag;

	shmid1 = shmget(IPC_PRIVATE,10,0777|IPC_CREAT);

	shmid2 = shmget(IPC_PRIVATE,32,0777|IPC_CREAT);

	c = fork();

	if(c == 0){

			shmptr1 =(int*) shmat(shmid1,0,0);

			//srand(time(0));
			shmptr1[0] = rand()%100+1;

			shmdt(shmptr1);
			}

	else{

		d = fork();
		if(d == 0){

		   shmptr2 =(int*) shmat(shmid2,0,0);

		   srand(time(0));
           shmptr2[0] = rand()%100+1;

           shmdt(shmptr2);
           }
           else{

			shmptr1 =(int *) shmat(shmid1,0,0);

			shmptr2 =(int *) shmat(shmid2,0,0);


			printf("---------------------------------------------------------------------------------------------------\n");

			srand(time(0));

			if((rand()%100+1) %2 ==0)
			{
				flag = MIN;
				printf("Flag set is :%s\n","MIN");
			}
			else{
				flag = MAX;
				printf("Flag set is :%s\n","MAX");
			}

			printf("\nNumber choosen by C:%d\n",shmptr1[0]);
			printf("Number choosen by D:%d\n",shmptr2[0]);

			if(flag == MIN){

				if(shmptr1[0] < shmptr2[0]){

					printf("C Won the round\n");
					Cscore++;
					printscores();
				}
				else if(shmptr1[0] > shmptr2[0])
				{

					printf("D Won the Round\n");
					Dscore++;
					printscores();
				}
				else{

					printf("Both have choosen same number\n");
				}

			}
			else{
				 if(shmptr1[0] > shmptr2[0]){

				  	printf("C Won the round\n");
				   	Cscore++;
				   	printscores();
				   	}
				  else if(shmptr1[0] < shmptr2[0]){

				  	printf("D Won the round\n");
				  	Dscore++;
				  	printscores();
				  	}
				 else{
				 		printf("Both have choosen same number\n");
				 	}
				}

			shmdt(shmptr1);
			shmdt(shmptr2);

			shmctl(shmid1,IPC_RMID,0);
			shmctl(shmid2,IPC_RMID,0);
		}

	}
}