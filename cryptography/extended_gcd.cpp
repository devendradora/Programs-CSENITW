#include <gmp.h>
#include <stdio.h>
#include <math.h>

void extended_gcd(mpz_t a, mpz_t b){

if(mpz_cmp_ui(a,0)  == 0 )
	gmp_printf("GCd : %Zd",b);
else if(mpz_cmp_ui(b,0) == 0)
	gmp_printf("GCd : %Zd",a);
else{
mpz_t r,r_1,r_2,x_1,y_1,x_2,y_2,x,y,q,temp1,temp2,ans;

mpz_inits(q,r,r_1,r_2,x,y,x_1,x_2,y_1,y_2,temp1,temp2,ans,NULL);

mpz_set(r_2,a);
mpz_set(r_1,b);

mpz_set_ui(x_2,1);
mpz_set_ui(y_2,0);

mpz_set_ui(x_1,0);
mpz_set_ui(y_1,1);



int flag=0;

mpz_mmod(r,r_2,r_1);


while(mpz_cmp_ui(r,0) != 0){
flag=1;
mpz_mmod(r,r_2,r_1);
mpz_div(q,r_2,r_1);


mpz_mul(temp1,q,x_1);
mpz_sub(x,x_2,temp1);

mpz_mul(temp2,q,y_1);
mpz_sub(y,y_2,temp2);

mpz_set(r_2,r_1);
mpz_set(r_1,r);

mpz_set(x_2,x_1);
mpz_set(x_1,x);

mpz_set(y_2,y_1);
mpz_set(y_1,y);


}

if(flag ==1){
	gmp_printf("%Zd  %Zd",x_2,y_2);
	mpz_mul(temp1,a,x_2);
	mpz_mul(temp2,b,y_2);
	mpz_add(ans,temp1,temp2);

}
else
{

	gmp_printf("%Zd  %Zd",x_1,y_1);
	mpz_mul(temp1,a,x_1);
	mpz_mul(temp2,b,y_1);
	mpz_add(ans,temp1,temp2);

}

gmp_printf("\nGCD is %Zd ",ans);

}


}

int main(){
	mpz_t a, b;
	mpz_inits(a, b, NULL);

	mpz_inp_str(a, stdin, 10);
	mpz_inp_str(b, stdin, 10);

	extended_gcd(a, b);

	return 0;
}