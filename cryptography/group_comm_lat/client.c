#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
char *sfifo,*cfifo,clRead[10];
int *clientNo,*pid,S1,S2,clientId;
int *groupNo,gno;

struct buff
{
	int grp;
	int id;
	char msg[1024];
};

void lock(int semid)
{
	struct sembuf sb;
	sb.sem_flg = 0;
	sb.sem_num = 0;
	sb.sem_op = -1;
	if(semop(semid,&sb,1)<0)
	{
		perror("lock");
		exit(0);
	}
}

void unlock(int semid)
{
	struct  sembuf sb;
	sb.sem_flg = 0;
	sb.sem_num = 0;
	sb.sem_op = 1;
	if(semop(semid,&sb,1)<0)
	{
		perror("unlock");
		exit(0);
	}
}

void start()
{
	int i;
	int c = fork();
	if(c>0)
	{
		while(1)
		{
			struct buff buf;
			int fd = open(clRead,O_RDONLY);
			read(fd,&buf,1024);
			close(fd);
			printf("From %d: %s\n",buf.id,buf.msg);
			close(fd);
		}
	}
	else
	{
		while(1)
		{
			struct buff buf;
			gets(buf.msg);
			
			buf.id = clientId;
			buf.grp = gno;
			lock(S2);
			
			int fd = open(sfifo,O_WRONLY);
			write(fd,&buf,1024);
			close(fd);
			unlock(S2);
		}
	}
		
}

void connect()
{
	strcpy(clRead,cfifo);
	unlock(S1);
	clientId = *clientNo;
	printf("Connected to server client Id: %d\n",clientId);
	start();
}
	
int main(int argc,char* argv[])
{
	//int shmid = shmget(ftok(".",'A'),sizeof(char)*5,0666);
	//char *ch = shmat(shmid,NULL,0);
	sfifo = (char*)shmat((shmget(ftok(".",'A'),sizeof(char)*5,0666)),NULL,0);
	cfifo = (char*)shmat((shmget(ftok(".",'B'),sizeof(char)*6,0666)),NULL,0);
	
	//strcpy(ch,"sfifo");
	//printf("%s",ch);
	pid = (int*)shmat((shmget(ftok(".",'C'),sizeof(int),0666)),NULL,0);
	clientNo = (int*)shmat((shmget(ftok(".",'D'),sizeof(int),0666)),NULL,0);
	groupNo = (int*)shmat((shmget(ftok(".",'G'),sizeof(int),0666)),NULL,0);
	*groupNo = argv[1][0]-'0';
	gno = argv[1][0]-'0';

	S1 = semget(ftok(".",'E'),1,IPC_CREAT|0666);
	semctl(S1,0,SETVAL,1);
	S2 = semget(ftok(".",'F'),1,IPC_CREAT|0666);
	semctl(S2,0,SETVAL,1);

	signal(SIGUSR2,connect);
	lock(S1);
	kill(*pid,SIGUSR1);
	*pid = getpid();
	while(1);
}

