#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void miller_rabin(mpz_t n)
{
	if(mpz_cmp_ui(n , 2) == 0)
    {
    	gmp_printf("\n%Zd is a prime number\n" , n);
    	exit(2);
    } 

    mpz_t rem;
    mpz_init(rem);

    mpz_mmod_ui(rem , n , 2);
   
    if(mpz_cmp_ui(rem , 0) == 0)
    {
    	gmp_printf("\n%Zd is not a prime number\n" , n);
    	exit(2);
    }


    mpz_t n_minus_1;
    mpz_init(n_minus_1);
    mpz_sub_ui(n_minus_1 , n , 1);


	mpz_t r , s ;
	mpz_inits(r , s , NULL);

	mpz_set(s , n_minus_1);
	

    mpz_mmod_ui(rem , s , 2);
	while(mpz_cmp_ui(rem , 0) == 0)
	{
         mpz_add_ui(r , r , 1);
         mpz_div_ui(s , s , 2);
         mpz_mmod_ui(rem , s , 2);
	}

    mpz_t a;
    mpz_init(a);

    gmp_randstate_t state;
    gmp_randinit_default(state);
    
    int seed;
    //struct timeval* t;
    //gettimeofday(t , NULL);
    //seed = t->tv_usec;
    //seed = 4546;
    //printf("\nEnter seed - ");
    //scanf("%d" , &seed);

    gmp_randseed_ui (state , seed );

    mpz_urandomm (a , state , n_minus_1);
    mpz_add_ui(a , a , 1);
    gmp_printf("\na is - %Zd\n" , a);

    mpz_t a_pow_s;
    mpz_init(a_pow_s);

    
 
    mpz_powm(rem , a , s , n);

    
    if(mpz_cmp_ui(rem , 1) == 0)
    {
    	gmp_printf("\nThe given number %Zd is a prime number \n" , n);
    	exit(0);
    }

    mpz_t two_pow_j;
    mpz_init(two_pow_j);
    mpz_set_ui(two_pow_j , 1);

    mpz_t j;;
    mpz_init(j);

    mpz_set_ui(j , 0);

    mpz_t product;
    mpz_init(product);

    while(mpz_cmp(j , r) != 0)
    {
    	
        mpz_mul(product , two_pow_j , s);    
    
        mpz_powm(rem , a , product , n);

        if(mpz_cmp(rem , n_minus_1) == 0)
        {
        	gmp_printf("\nThe given number %Zd is a prime number \n" , n);
        	exit(1);
        }

        mpz_mul_ui(two_pow_j , two_pow_j , 2);
    	mpz_add_ui(j , j , 1);
    }

    gmp_printf("\nThe given number %Zd is   NOT   a prime number \n" , n);
}



int main()
{
	mpz_t n;
	mpz_init(n);
	printf("Enter a number - ");
	mpz_inp_str(n , NULL , 10);

    miller_rabin(n);
}