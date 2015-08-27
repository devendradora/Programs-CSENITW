#include<stdio.h>
#include<gmp.h>


int main(int argc, char const *argv[])
{

	mpz_t n1,n2,s;
	mpz_init(n1);
	mpz_init(n2);
    mpz_init(s);

	mpz_add(s,n1,n2);
	gmp_printf("sum : %Zd",s);
	
	return 0;
}