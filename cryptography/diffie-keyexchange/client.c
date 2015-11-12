#include<time.h>
#include<stdio.h>
#include<math.h>
#include<gmp.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>

int main(int argc,char *argv[ ])
{
	if(argc!=2)
        	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	bzero(&serv_addr,sizeof(serv_addr));
    /**
        Create tcp socket using given parameters
    */
	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
        	perror("\n socket");
	else 
	        printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
    /**
        Connect tcp socket using given parameters
    */
	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
        	perror("\n connect : ");
	else    
	        printf("\nconnect succesful");
	        
        mpz_t q1,q2,q3,p,g,t,p1,x,xb,ya,yb,k,limit;
        mpz_inits(q1,q2,q3,p,g,p1,t,limit,x,xb,ya,yb,k,NULL);
        
        gmp_randstate_t(state);
        gmp_randinit_mt(state);
        
        char buf[2056];
        bzero(buf,sizeof(buf));
        
        read(sfd,buf,2056);
        mpz_set_str(p,buf,10);
        gmp_printf("\nprime is %Zd\n",p);
        
        read(sfd,buf,2056);
        mpz_set_str(g,buf,10);
        gmp_printf("\ngenerator is %Zd\n",g);
        
        mpz_urandomm(xb,state,p);
        mpz_powm(yb,g,xb,p);
        
        bzero(buf,sizeof(buf));
        read(sfd,buf,2056);
        mpz_set_str(ya,buf,10);
        gmp_printf("\nya = %Zd\n",ya);
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,yb);
        write(sfd,buf,sizeof(buf));
        
        mpz_powm(k,ya,xb,p);
        
        gmp_printf("\n\n\n\nkey is %Zd\n",k);
}
