#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"BigNumber.h"
#include"typedef.h"

MPZ * initMPZs(int bytes,int num){
    MPZ * temp = (MPZ*)malloc(sizeof(MPZ)*num);
    for(int i=0;i<num;i++){
        temp[i].sign = 0;
        //temp[i].data = (UINT32*)malloc(bytes+1);
        temp[i].data = (UINT32*)calloc(bytes+1,sizeof(UINT32));
        temp[i].len = bytes/8;
    }
    return temp;
}

int main(void){
    int bytes = DATA_SIZE;
    int num = COUNT;
    MPZ* MPZs1 = initMPZs(bytes,num);
    MPZ* MPZs2 = initMPZs(bytes,num);
    // MPZ* large = initMPZs(bytes*2,num);
    // MPZ* large2 = initMPZs(bytes*2,num);
    MPZ* result = initMPZs(bytes,num);
    Gen_BigNum_File("rand_MPZs1.txt",bytes,num);
    Gen_BigNum_File("rand_MPZs2.txt",bytes,num);
    Read_MPZ_FIle("rand_MPZs1.txt",MPZs1, num);
    Read_MPZ_FIle("rand_MPZs2.txt",MPZs2, num);
    // BigNum_Sort(MPZs1,num);
    // BigNum_Sort(MPZs2,num);
    // Write_MPZ_File("rand_MPZs1w.txt",MPZs1,bytes,num);
    // Write_MPZ_File("rand_MPZs2w.txt",MPZs2,bytes,num);

    srand(time(NULL));
    clock_t start = clock();
    for(int i=0;i<num;i++)
        MPZ_UADD(&MPZs1[i],&MPZs2[i],&result[i]);
    Write_MPZ_File("rand_large.txt",result,bytes,num);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);


    // clock_t start = clock();
    // for(int i=0;i<num;i++)
    //     BigNum_Mul(&MPZs1[i],&MPZs2[i],&large[i]);
    // Write_MPZ_File("rand_large.txt",large,bytes*2,num);
    // clock_t end = clock();
    // printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    // start = clock();
    // for(int i=0;i<num;i++)
    //     BigNum_Mul2(&MPZs1[i],&MPZs2[i],&large2[i]);
    // Write_MPZ_File("rand_large2.txt",large,bytes*2,num);
    // end = clock();
    // printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    return 0;
}