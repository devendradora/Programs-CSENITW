//gcc gcd.cpp -lgmp


#include <stdio.h>
#include <gmp.h>

void find_gcd(mpz_t gcd , mpz_t a , mpz_t b)
{
	while(mpz_cmp(a , b) != 0)
	{
        if(mpz_cmp(a , b) > 0)
        {
        	mpz_sub(a , a , b);
        }

        else
        {
        	mpz_sub(b , b , a);
        }
	}
	
    mpz_set(gcd , a);
}

int main()
{
	mpz_t a , b , gcd;
	mpz_inits(a , b , gcd , NULL);
    
	printf("Enter first number : ");
	mpz_inp_str (a , stdin , 10 );

	printf("\nEnter second number : ");
	mpz_inp_str (b , stdin , 10 );

    find_gcd(gcd , a , b);

    printf("\nGCD of the given two numbers is : ");
    mpz_out_str (stdout , 10 , gcd);

    printf("\n");
}