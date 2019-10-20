#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    int *shmPtr;
    key_t shmKey;
    shmKey = ftok(".",'x');
    int shmID,pid,status;

    // Logic of the problem
    if( (pid = fork()) == 0){

        sleep(5);

        shmID = shmget(shmKey,12*sizeof(int),IPC_CREAT | 0666);
        if(shmID < 0){
            cout << "child : shmget() error" << endl;
            exit(1);
        }

        // Attach the shared memory
        shmPtr = (int*)shmat(shmID,NULL,0);
        if( *shmPtr == -1){
            cout << "child : shmat() error" << endl;
            exit(1);
        }

        cout << "The child started reading : " << endl ;
        int i;
        for(i = 0; i < 10 ; i++){
            cout << "The value of shmPtr[" << i << "] : " << shmPtr[i] << endl ;
        }
        cout << "The child has finished reading ";
        shmPtr[10] = 1;

    }
    else{
        // Create the shared memory
	cout << "Parent : Create the shared memory" << endl;
        shmID = shmget(shmKey,12*sizeof(int),IPC_CREAT | 0666);
        if(shmID < 0){
            cout << "shmget() error" << endl;
            exit(1);
        }

        // Attach the shared memory
	cout << "Parent : Attached the shared memory" << endl;
        shmPtr = (int*)shmat(shmID,NULL,0);
        if( *shmPtr == -1){
            cout << "shmat() error" << endl;
            exit(1);
        }

        int i;
        for(i = 0; i < 10 ; i++){
            shmPtr[i] = i+1;
        }

        wait(&status);
        cout << "The value is : " << shmPtr[10] << endl ;
    }

    // Detach the shared memory
    shmdt(shmPtr);

    // Clear the shared memory
    shmctl(shmID,IPC_RMID,NULL);
}