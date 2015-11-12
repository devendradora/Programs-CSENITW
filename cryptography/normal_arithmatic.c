#include <stdio.h>
#include <gmp.h>


int main()
{
	mpz_t a , b , sum , difference , product , division;
	mpz_inits( a , b , sum , difference , product , division , NULL);
	
	printf("Enter first number : ");
	mpz_inp_str (a , stdin , 10 );

	printf("\nEnter second number : ");
	mpz_inp_str (b , stdin , 10 );

	mpz_add(sum , a , b);
	mpz_sub(difference , a , b);
	mpz_mul(product , a , b);
	mpz_div(division , a , b);

    printf("\nSum of the given two numbers is : ");
    mpz_out_str (stdout , 10 , sum );

    printf("\nDifference of the given two numbers is : ");
    mpz_out_str (stdout , 10 , difference );

    printf("\nProduct of the given two numbers is : ");
    mpz_out_str (stdout , 10 , product );

    printf("\nDivision of the given two numbers is : ");
    mpz_out_str (stdout , 10 , division );

    printf("\n");
}