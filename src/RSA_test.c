#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"include/BigNumber.h"
#include"include/typedef.h"


void test_MUL(){
    int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = newMPZs(bytes,num);
    MPZ* MPZs2 = newMPZs(bytes,num);
    MPZ* large = newMPZs(bytes*2,num);;

    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/mul_a.txt",bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/mul_b.txt",bytes,num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/mul_a.txt",MPZs1, num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/mul_b.txt",MPZs2, num);

    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_MUL(&MPZs1[i],&MPZs2[i],&large[i]);
    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/mul_result.txt",large,bytes*2,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    delMPZs(MPZs1, num);
    delMPZs(MPZs2, num);
    delMPZs(large, num);
}
void test_ADD(){
    int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = newMPZs(bytes,num);
    MPZ* MPZs2 = newMPZs(bytes,num);
    MPZ* result = newMPZs(bytes,num);

    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/add_a.txt",bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/add_b.txt",bytes,num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/add_a.txt",MPZs1, num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/add_b.txt",MPZs2, num);

    srand(time(NULL));
    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_UADD(&MPZs1[i],&MPZs2[i],&result[i]);
    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/add_result.txt",result,bytes,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    delMPZs(MPZs1, num);
    delMPZs(MPZs2, num);
    delMPZs(result, num);

}

void test_SUB(){
    int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = newMPZs(bytes,num);
    MPZ* MPZs2 = newMPZs(bytes,num);
    MPZ* result = newMPZs(bytes,num);

    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/sub_a.txt",bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/sub_b.txt",bytes,num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/sub_a.txt",MPZs1, num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/sub_b.txt",MPZs2, num);

    srand(time(NULL));
    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_USUB(&MPZs1[i],&MPZs2[i],&result[i]);

    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/sub_result.txt",result,bytes,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    delMPZs(MPZs1, num);
    delMPZs(MPZs2, num);
    delMPZs(result, num);

}

void test_DIV(){
        int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* diva = newMPZs(bytes,num);
    MPZ* divb = newMPZs(bytes,num);
    MPZ* divc = newMPZs(bytes,num);
    MPZ* result = newMPZs(bytes*2,num);
    MPZ* q = newMPZs(bytes,num);
    MPZ* r = newMPZs(bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_a.txt",bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_b.txt",bytes,num);
    Gen_BigNum_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_m.txt",bytes,num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_a.txt",diva, num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_b.txt",divb, num);
    Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_m.txt",divc, num);
    
    for(int i=0;i<num;i++)
        MPZ_MUL(&diva[i],&divb[i],&result[i]);

    clock_t start = clock();
    
    for(int i=0;i<num;i++)
        MPZ_UDIV(&q[i],&r[i],&result[i],&divc[i]);

    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_q_before.txt",result,bytes*2,num);
    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_q.txt",q,bytes,num);
    Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/div_r.txt",r,bytes,num);

    delMPZs(diva, num);
    delMPZs(divb, num);
    delMPZs(divc, num);
    delMPZs(result, num);
    delMPZs(q, num);
    delMPZs(r, num);
}