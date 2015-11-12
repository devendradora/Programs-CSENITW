#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(){

	mpz_t p , q , N ,phi_N,e,d,M,C,res;
	mpz_inits(p,q,N,phi_N,e,d,M,C,res,NULL);

	gmp_randstate_t state ;
	gmp_randinit_mt(state);

 //Manual input of p and q
     //int repeats=5,primecheck=0;   
	// printf("Enter p \n");
	// gmp_scanf("%Zd",&p);
	// //mpz_inp_str(p,stdin,10);
	// primecheck = mpz_probab_prime_p(p,repeats);
	// if(primecheck != 2)
	// {printf(" p is not prime . Error code : %d \n",primecheck);exit(1);
 //    }
	// printf("Enter q \n");
	// gmp_scanf("%Zd",&q);
	// //mpz_inp_str(q,stdin,10);
	// primecheck = mpz_probab_prime_p(q,repeats);
	// if(primecheck!= 2)
	// {printf(" q is not prime . Error code : %d \n",primecheck);exit(1);
 //    }
    

    // Randomly generating p and q
	//b - bits uradomb ( 0- 2^n -1 ) urandom  (0 - n-1)
	mpz_urandomb(p,state,512);  
	mpz_nextprime(p,p);
	gmp_printf("p : %Zd \n",p );

	mpz_urandomb(q,state,512);
	mpz_nextprime(q,q);
	gmp_printf("q : %Zd \n",q );

	printf("Enter M \n");
	gmp_scanf("%Zd",&M);
	

	mpz_mul(N,p,q);
	gmp_printf("N : %Zd \n",N );

    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
	mpz_mul(phi_N,p,q);
	gmp_printf("phi_N : %Zd \n",phi_N );


	// mpz_urandomm(e,state,phi_N);
	// mpz_nextprime(e,e);
	
	
	mpz_set_ui(e,2);
     mpz_gcd(res,e,phi_N);
	 while( mpz_cmp_ui(res,1) != 0 ){
	 	  mpz_add_ui(e,e,1);
	 	  mpz_gcd(res,e,phi_N);
                   
	 }


	gmp_printf("e : %Zd \n",e);

	gmp_printf("\n\nPublic key : { %Zd , %Zd \n }",e,N);

	mpz_invert(d,e,phi_N);

	gmp_printf("\n\nd : %Zd \n",d);
	gmp_printf("\n\nPrivate key : { %Zd , %Zd \n }",d,N);

	mpz_powm (C , M , e , N );

	gmp_printf("\n\nC : %Zd \n",C );

	mpz_powm (M , C , d, N );

	gmp_printf("\n\nM : %Zd \n",M );




}
