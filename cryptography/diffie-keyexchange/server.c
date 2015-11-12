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
        
       


mpz_t num,q0,q1,q2,q3,N,g_max,sub_res,div_res,powres,g,prod,p;
mpz_inits(num,q0,q1,q2,q3,N,g_max,sub_res,div_res,powres,g,p,prod,NULL);
mpz_set_ui(N,50);
mpz_set_ui(prod,1);
mpz_set_ui(g_max,20);
mpz_set_ui(q0,2);

gmp_randstate_t state ;
gmp_randinit_mt(state);


int primecheck;

//mpz_urandomb(num,state,5);
mpz_urandomm(num,state,N);
mpz_nextprime(q1,num);
mpz_mul(prod,q0,q1);
gmp_printf("\n\n\nq0 : %Zd\n",q0);
gmp_printf("\n\n\nq1: %Zd\n",q1);

do {
//mpz_urandomb(q1,state,5);

mpz_nextprime(q2,q1);
mpz_nextprime(q3,q2);

gmp_printf("\n\n\nq2 : %Zd\n",q2);
gmp_printf("\n\n\nq3: %Zd\n",q3);

mpz_mul(prod,prod,q2);
mpz_mul(prod,prod,q3);

mpz_add_ui(prod,prod,1);
gmp_printf("q1: %Zd\n",prod);
primecheck = mpz_probab_prime_p(prod,5);
} while(primecheck == 0);



mpz_set(p,prod);
gmp_printf("\n\n\np : %Zd\n",p);
int gen_cnt = 0;

do{
mpz_urandomm(g,state,g_max);
gen_cnt=0;

mpz_sub_ui(sub_res,p,1);
mpz_div(div_res,sub_res,q0);
mpz_powm(powres,g,div_res,p);

if (mpz_cmp_ui(powres,1) != 0)
    gen_cnt ++;
else
    continue;

mpz_sub_ui(sub_res,p,1);
mpz_div(div_res,sub_res,q1);
mpz_powm(powres,g,div_res,p);
if (mpz_cmp_ui(powres,1) != 0)
    gen_cnt ++;
else
    continue;

mpz_sub_ui(sub_res,p,1);
mpz_div(div_res,sub_res,q2);
mpz_powm(powres,g,div_res,p);
if (mpz_cmp_ui(powres,1) != 0)
    gen_cnt ++;
else
    continue;


mpz_sub_ui(sub_res,p,1);
mpz_div(div_res,sub_res,q3);
mpz_powm(powres,g,div_res,p);
if (mpz_cmp_ui(powres,1) != 0)
    gen_cnt ++;
else
    continue;

printf("g ^ (p-1)/qi  mod p checking......\n");

}while(gen_cnt != 4);


if(gen_cnt == 4)
    gmp_printf("generator : %Zd\n\n",g);

 
        
 char buf[2056];
 bzero(buf,sizeof(buf));
mpz_t xa,ya,yb,k;
mpz_inits(xa,ya,yb,k,NULL);
       
        bcopy(&p, buf,sizeof(p));
        mpz_get_str(buf,10,p);
       // gmp_printf("\nbuf= %s\n",buf);
        write(nsfd,buf,sizeof(buf));
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,g);
        write(nsfd,buf,sizeof(buf));
        
        mpz_urandomm(xa,state,p);
        mpz_powm(ya,g,xa,p);
         
        gmp_printf("\nxa = %Zd\n",xa);
        gmp_printf("\nya = %Zd\n",ya);
        
        bzero(buf,sizeof(buf));
        mpz_get_str(buf,10,ya);
        write(nsfd,buf,sizeof(buf));
        
        bzero(buf,sizeof(buf));
        read(nsfd,buf,2056);
        mpz_set_str(yb,buf,10);
        gmp_printf("\nyb = %Zd\n",yb);
        
        mpz_powm(k,yb,xa,p);
        
        gmp_printf("\n\n\nkey is %Zd\n",k);

}
