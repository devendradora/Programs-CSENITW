#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/sem.h>
#define MAXM 9
int NCLNT=0;
char *sfifo,*cfifo;
int *pid,S1,S2;
int *clientNo,*groupNo;
int group[10];

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

void newClient()
{
	++NCLNT;
	printf("client %d connecting... \n",NCLNT);

	if(NCLNT<=MAXM)
	{
		cfifo[5] = '0'+NCLNT;
		mkfifo(cfifo,IPC_CREAT|0666);
		*clientNo = NCLNT;
		group[*clientNo] = *groupNo;
		
		printf("connected client %d in group %d \n",*clientNo,group[*clientNo]);
		kill(*pid,SIGUSR2);
		*pid = getpid();
	}
	else
	{
		printf("Maximum limit of client reached!!\n");
		unlock(S1);
	}
}


int main()
{
	int shmid = shmget(ftok(".",'A'),sizeof(char)*5,IPC_CREAT|0666);
	sfifo = (char*)shmat(shmid,NULL,0);
	strcpy(sfifo,"sfifo");
	
	cfifo = (char*)shmat((shmget(ftok(".",'B'),sizeof(char)*6,IPC_CREAT|0666)),NULL,0);
	strcpy(cfifo,"cfifo0");
	
	pid = (int*)shmat((shmget(ftok(".",'C'),sizeof(int),IPC_CREAT|0666)),NULL,0);
	*pid = getpid();
	
	clientNo = (int*)shmat((shmget(ftok(".",'D'),sizeof(int),IPC_CREAT|0666)),NULL,0);
	groupNo = (int*)shmat((shmget(ftok(".",'G'),sizeof(int),IPC_CREAT|0666)),NULL,0);
	
	S1 = semget(ftok(".",'E'),1,IPC_CREAT|0666);
	semctl(S1,0,SETVAL,1);
	S2 = semget(ftok(".",'F'),1,IPC_CREAT|0666);
	semctl(S2,0,SETVAL,1);
	
	signal(SIGUSR1,newClient);
	mkfifo(sfifo,IPC_CREAT|0666);
	//int c = fork();
	char client[10];strcpy(client,"cfifo0");int i;
	
	
	while(1)
	{
		struct buff buf;
		int fd = open(sfifo,O_RDONLY);
		read(fd,&buf,1024);
		close(fd);
		//printf("in server %d : %s\n",buf.id,buf.msg);
		for(i=1;i<=NCLNT;i++)
		{
			//printf("%d %d %d\n",buf.id,buf.grp,group[i]);
			if(buf.id==i||buf.grp!=group[i])continue;
			//printf("%d\n",buf.id);
			client[5] = '0'+i;
			fd = open(client,O_WRONLY);
			write(fd,&buf,1024);
			close(fd);
		}
	}
}

