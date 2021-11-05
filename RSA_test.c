#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"BigNumber.h"
#include"typedef.h"


void test_MUL(){
        int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = initMPZs(bytes,num);
    MPZ* MPZs2 = initMPZs(bytes,num);
    MPZ* large = initMPZs(bytes*2,num);
    MPZ* large2 = initMPZs(bytes*2,num);
    Gen_BigNum_File("rand_MPZs1w.txt",bytes,num);
    sleep(1);
    Gen_BigNum_File("rand_MPZs2w.txt",bytes,num);
    Read_MPZ_FIle("rand_MPZs1w.txt",MPZs1, num);
    Read_MPZ_FIle("rand_MPZs2w.txt",MPZs2, num);

    clock_t start = clock();
    for(int i=0;i<num;i++)
        BigNum_Mul(&MPZs1[i],&MPZs2[i],&large[i]);
    Write_MPZ_File("rand_large.txt",large,bytes*2,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);


}
void test_ADD(){
            int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = initMPZs(bytes,num);
    MPZ* MPZs2 = initMPZs(bytes,num);

    MPZ* result = initMPZs(bytes,num);
    Gen_BigNum_File("rand_MPZs1.txt",bytes,num);
    sleep(1);
    Gen_BigNum_File("rand_MPZs2.txt",bytes,num);
    Read_MPZ_FIle("rand_MPZs1.txt",MPZs1, num);
    Read_MPZ_FIle("rand_MPZs2.txt",MPZs2, num);

    srand(time(NULL));
    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_UADD(&MPZs1[i],&MPZs2[i],&result[i]);
    Write_MPZ_File("rand_large.txt",result,bytes,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

}

void test_SUB(){
            int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = initMPZs(bytes,num);
    MPZ* MPZs2 = initMPZs(bytes,num);

    MPZ* result = initMPZs(bytes,num);
    Gen_BigNum_File("rand_MPZs1.txt",bytes,num);
    sleep(1);
    Gen_BigNum_File("rand_MPZs2.txt",bytes,num);
    Read_MPZ_FIle("rand_MPZs1.txt",MPZs1, num);
    Read_MPZ_FIle("rand_MPZs2.txt",MPZs2, num);

    srand(time(NULL));
    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_USUB(&MPZs1[i],&MPZs2[i],&result[i]);
    Write_MPZ_File("rand_large.txt",result,bytes,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

}