#include <stdio.h>
#include <gmp.h>

void prime_factors(mpz_t num){
    mpz_t i,rem;
    mpz_inits(i,rem,NULL);

    int cnt=0,flag=0;
	
	for(mpz_set_ui(i,2); mpz_cmp_ui(num,1) != 0;mpz_add_ui(i,i,1)){
		
		mpz_mmod(rem,num,i);
         cnt=0,flag=0;
		while(mpz_cmp_ui(rem,0) == 0){
			//gmp_printf("%Zd ,",i);
		    cnt++;flag=1;
			mpz_div(num,num,i);
		    mpz_mmod(rem,num,i);
		}
        if(flag==1)
		gmp_printf("%Zd ^ %d   , ",i,cnt);
		
	}
}


int main(){
	mpz_t num;
	mpz_init(num);
	gmp_printf("Enter num\n");
	gmp_scanf("%Zd",num);
	//gmp_printf("%Zd",num);
	prime_factors(num);
	return 0;
}