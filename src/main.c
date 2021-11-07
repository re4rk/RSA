#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"include/BigNumber.h"
#include"include/typedef.h"
#include"include/RSA_test.h"

int main(void){
    // int bytes = DATA_SIZE;
    // int num = 1;
    // MPZ* diva = initMPZs(bytes,num);
    // MPZ* divb = initMPZs(bytes,num);
    // MPZ* divc = initMPZs(bytes,num);
    // MPZ* result = initMPZs(bytes*2,num);
    // MPZ* q = initMPZs(bytes,num);
    // MPZ* r = initMPZs(bytes,num);
    // Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_a.txt",diva, num);
    // Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_b.txt",divb, num);
    // Read_MPZ_FIle("/Users/Re4rk/Documents/crypto/RSA/tmp/div_c.txt",divc, num);
    // for(int i=0;i<num;i++){
    //     BigNum_Mul(&diva[i],&divb[i],&result[i]);
    //     MPZ_UDIV(&q[i],&r[i],&result[i],&divc[i]);
    //     BIG_PRINT(&q[i]);
    // }
    // Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/rand_large.txt",result,bytes*2,num);
    // Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/q.txt",q,bytes,num);
    // Write_MPZ_File("/Users/Re4rk/Documents/crypto/RSA/tmp/r.txt",r,bytes,num);
   test_DIV();
    return 0;
}