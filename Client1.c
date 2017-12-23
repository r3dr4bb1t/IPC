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

int main ()
{

	key_t key;
	struct msgbuf c1;

	// msg queue get

    key_id = msgget((key_t)1234, IPC_CREAT|0666);

    if (key_id == -1)
    {
        perror("msgget error : ");
        exit(0);
    }
    //msg + pid write
 
    memset(c1.mtext, 0x00, 1024); 
    memset(c1.myname, 0x00, 4); 

    // get msg input from client
    
    scanf("%s",c1.mtext );
    memcpy(c1.myname, "PID1", 4);
    
}