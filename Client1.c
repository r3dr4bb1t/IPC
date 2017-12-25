#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/msg.h> 
#include <sys/stat.h> 
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 1024

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct 
{
    long mtype;
    char mbuf[MAXBUF];
    int mpid;
   	int privacy;
}msgbuff;

typedef struct 
{
	key_t key_id;
}id;

void *send(void *arg);
void *rcv(void *arg);

int main ()
{

    pthread_t sendt;
	pthread_t rcvt;
	void *result;
	id identifier;
	int shmid; 
	int shared_memory;

	shmid = shmget((key_t)1111, sizeof(int), 0666|IPC_CREAT);
	//shared_memory = shmat(shmid,(void*)0, 0);

    identifier.key_id = msgget((key_t)2222, IPC_CREAT|0666);


    pthread_create(&sendt,NULL,send,&identifier);
    pthread_create(&rcvt,NULL,rcv,&identifier);
    pthread_join(rcvt,&result);
    pthread_join(sendt,&result);


    return 0;
 
}	

void *send(void *arg)
{
	id* identifier;
	identifier = (id*)arg;

	pthread_t tid;

	msgbuff c1;
    c1.mpid = getpid(); // get msg input from client

    while(1)
    {	
    	
   		memset(c1.mbuf, 0x00, 1024); 

    	scanf("%d", &c1.privacy );
    	scanf("%s", c1.mbuf );

    	pthread_mutex_lock(&mutex);
  		if (msgsnd( identifier->key_id, (void *)&c1, sizeof(msgbuff), IPC_NOWAIT) == -1)
    	    {
        	    perror("msgsnd error ");
            	exit(0);
        	}
        pthread_mutex_unlock(&mutex);

  }
}
  
 void *rcv(void* arg)
 {
  	id* identifier;
  	identifier = (id*)arg;

  	msgbuff c1;

  	while(1)
  	{ 
  	 	if (msgrcv( identifier->key_id, (void *)&c1, sizeof(msgbuff), c1.mtype, 0) == -1)
        {
            perror("msgrcv error ");
            exit(0);    
        }

  }
}