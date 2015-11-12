
#include <stdio.h>
#include <gmp.h>
#include <sys/time.h>

int main()
{
	mpz_t p , Xa , Xb , Ya , Yb , k1 , k2 , random, bits_512 ;

	mpz_inits(p  ,  Xa , Xb , Ya , Yb , k1 , k2 , random , bits_512, NULL);

    mpz_ui_pow_ui(bits_512 , 2 , 5);

    gmp_randstate_t state;
    gmp_randinit_default(state);


    int seed ;

    gmp_randseed_ui(state , seed);

    

    mpz_t num,g,q0,q1,q2,q3,N,g_max,sub_res,div_res,powres,prod;
    mpz_inits(num,q0,q1,q2,q3,N,g_max,sub_res,div_res,powres,g,p,prod,NULL);
    mpz_set_ui(N,50);
    mpz_set_ui(prod,1);
    mpz_set_ui(g_max,20);
    mpz_set_ui(q0,2);


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
       gmp_printf("generator : %Zd",g);




   mpz_urandomm(Xa , state , p);
   mpz_urandomm(Xb , state , p);



   mpz_powm(Ya , g , Xa , p);
   mpz_powm(Yb , g , Xb , p);


   gmp_printf("\np is \n%Zd\n g is \n%Zd\n" , p , g);
   gmp_printf("\nXa is \n%Zd\n Xb is \n%Zd\n" , Xa , Xb);
   gmp_printf("\nYa is \n%Zd\n Yb is \n%Zd\n" , Ya , Yb);

   mpz_powm(k1 , Yb , Xa , p);
   mpz_powm(k2 , Ya , Xb , p);

   gmp_printf("\nK1 is - \n%Zd\n K2 is \n%Zd\n",k1,k2);
}