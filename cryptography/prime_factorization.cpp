#include <stdio.h>
#include <gmp.h>

void prime_factors(mpz_t num){
    mpz_t i,rem;
    mpz_inits(i,rem,NULL);
    
	
	for(mpz_set_ui(i,2); mpz_cmp_ui(num,1) != 0;mpz_add_ui(i,i,1)){
		
		mpz_mmod(rem,num,i);

		while(mpz_cmp_ui(rem,0) == 0){
			gmp_printf("%Zd ,",i);
			mpz_div(num,num,i);
		    mpz_mmod(rem,num,i);
		}
		
	}
}


int main(){
	mpz_t num;
	mpz_init(num);
	gmp_scanf("%Zd",num);
	//gmp_printf("%Zd",num);
	prime_factors(num);
	return 0;
}