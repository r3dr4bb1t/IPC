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

typedef struct {
	long long mtype;
	char data[MAXBUF];

}mybuf;

typedef struct {
	int number;
	int fd;
}id;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *snd(void *arg);
void *rcv(void *arg);

int main (int argc,char *argv[])
{
	pthread_t snd_thread, rcv_thread;
	int fd;
	void *thread_result;
	id num;

	num.fd = msgget((key_t)2222, IPC_CREAT|0666);


	if(argc!=2)
	{
		printf("press again\n");
		exit(1);
	}

	num.number = atoi (argv[1]);

	pthread_create(&snd_thread,NULL,snd,&num);
	pthread_create(&rcv_thread,NULL,rcv,&num);
	pthread_join(rcv_thread,&thread_result);
	pthread_join(snd_thread,&thread_result);
	return 0;
}

	void *snd(void *arg)
	{
		id* num;
		num= (id*)arg;
		pthread_t tid;
		char buf[MAXBUF];
		char buff[MAXBUF];
		mybuf datas;
		int c;

		while(1)
		{
			memset(buf,'\0',MAXBUF);
			memset(buff,'\0',MAXBUF);
			scanf("%d", &c);
			getchar();
			fgets(buf,MAXBUF,stdin);
			*(buf+(strlen(buf)-1))='\0';

			datas.mtype =c;
			sprintf(buff, "[%d send] : %s\n", (*num).number,buf);
			strcpy(datas.data,buff);

			pthread_mutex_lock(&mutex);
			msgsnd((*num).fd, &datas,sizeof(datas)-sizeof(long),0);
			pthread_mutex_unlock(&mutex);
}

}
		
	
void *rcv(void *arg)

{
	id* num;
	num = (id*) arg;
	char buf[MAXBUF];
	int i;
	mybuf datas;

	while(1)
	{
		if((msgrcv((*num).fd,&datas,sizeof(datas)-sizeof(long),(*num).number,0))>0)
		{
			printf("%s\n",datas.data);
		}
	}
}