#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/msg.h> 
#include <sys/stat.h> 

struct msgbuf
{
    long mtype;
    char mbuf[1024];
    char mpid[3];
};



