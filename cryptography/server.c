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
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len=sizeof(struct sockaddr_in);
	int port_no=atoi(argv[1]);
    /**
        Create tcp socket using given parameters
    */
	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
        	perror("\n socket ");
	else 
	        printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
    /**
        Bind created socket to an interface
    */
	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	        perror("\n bind : ");
	else
	        printf("\n bind successful ");

    /**
        Listen for incoming connection
    */
	listen(sfd,10);

	int nsfd;
	/**
        Accept connection if any one requested over this port and ip address
	*/
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	        perror("\n accept ");
	else 
	        printf("\n accept successful");
        
        /*while(1)
        {
                char buf[256];
                bzero(buf,sizeof(buf));
                read(0,buf,256);
                write(nsfd,buf,sizeof(buf));
                //send(sfd,buf,sizeof(buf),0);
        }*/
        
        char buf[512];
        bzero(buf,sizeof(buf));
        
        int flag,i;
        mpz_t q1,q2,q3,p,g,t,p1,x,xa,ya,yb,k,K,c1,c2,m,limit;
        mpz_inits(q1,q2,q3,p,g,p1,t,limit,x,xa,ya,yb,k,K,c1,c2,m,NULL);
        mpz_set_ui(t,1);
        mpz_set_ui(limit,20);
        
        gmp_randstate_t(state);
        gmp_randinit_mt(state);
        
        do
        {
                mpz_set_ui(p,1);
                
                /*mpz_urandomb(q1,state,512);
                mpz_nextprime(q1,q1);*/
                mpz_set_ui(q1,2);
                mpz_urandomb(q2,state,512);
                mpz_nextprime(q2,q2);
                mpz_urandomb(q3,state,512);
                mpz_nextprime(q3,q3);
                
                mpz_mul(p,p,q1);
                mpz_mul(p,p,q2);
                mpz_mul(p,p,q3);
                
                mpz_add_ui(p1,p,0);
                mpz_add(p,p,t);
                mpz_nextprime(p1,p1);
                
                /*gmp_printf("q1 = %Zd\n",q1);
                gmp_printf("q2 = %Zd\n",q2);
                gmp_printf("q3 = %Zd\n",q3);
                gmp_printf("p = %Zd\n",p);*/
                
        }while(mpz_cmp(p1,p)!=0);
        
        gmp_printf("q1 = %Zd\n",q1);
        gmp_printf("q2 = %Zd\n",q2);
        gmp_printf("q3 = %Zd\n",q3);
        gmp_printf("p = %Zd\n",p);
        
        do
        {
                flag = 0;
                
                mpz_urandomm(g,state,limit);
                
                if(mpz_cmp(g,t)!=0)
                {
                        mpz_add_ui(p1,p,0);
                        mpz_sub(p1,p1,t);
                        mpz_div(p1,p1,q1);
                        mpz_powm(x,g,p1,p);
                        if(mpz_cmp(x,t)==0)
                        {
                                flag = 1;
                                continue;
                        }         
                        
                        mpz_add_ui(p1,p,0);
                        mpz_sub(p1,p1,t);
                        mpz_div(p1,p1,q2);
                        mpz_powm(x,g,p1,p);
                        if(mpz_cmp(x,t)==0)
                        {
                                flag = 1;
                                continue;
                        }
                        
                        mpz_add_ui(p1,p,0);
                        mpz_sub(p1,p1,t);
                        mpz_div(p1,p1,q3);
                        mpz_powm(x,g,p1,p);
                        if(mpz_cmp(x,t)==0)
                        {
                                flag = 1;
                                continue;
                        }
                }
                else
                {
                        flag = 1;
                }
                
        }while(flag == 1);
        
        gmp_printf("generator is %Zd\n",g);
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,p);
        write(nsfd,buf,sizeof(buf));
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,g);
        write(nsfd,buf,sizeof(buf));
        
        mpz_urandomm(xa,state,p-1);
        mpz_powm(ya,g,xa,p);
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,ya);
        write(nsfd,buf,sizeof(buf));
        gmp_printf("ya is %Zd\n",ya);
        
        bzero(buf,sizeof(buf));
        read(nsfd,buf,512);
        mpz_set_str(c1,buf,10);
        gmp_printf("\nc1 = %Zd\n",c1);
        
        bzero(buf,sizeof(buf));
        read(nsfd,buf,512);
        mpz_set_str(c2,buf,10);
        gmp_printf("\nc2 = %Zd\n",c2);
        
        mpz_powm(K,c1,xa,p);
        gmp_printf("\nK = %Zd\n",K);
        
        mpz_invert(m,K,p);
        mpz_mul(m,m,c2);
        mpz_mod(m,m,p);
        gmp_printf("\nM = %Zd\n",m); 
}
