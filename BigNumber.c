#include"typedef.h"
#include"BigNumber.h"
#include"Config.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

time_t zxc =0;
void Gen_BigNum_File(SINT8 *filename ,SINT32 bytes,SINT32 num){
  FILE* pFile = fopen(filename, "wb");
  char contents[MAX_DATA_SIZE+2];

#if CONFIG_DEBUG
  printf("Gen_BigNum_File function start!\n");
  printf("FileName : %s\n", filename);
  printf("bytes : %d\n", bytes);
  printf("num : %d\n", num);
#endif
  ////////
  srand(time(NULL));
  rand();
  ///////
  for(int i=0;i<num;i++){
    for(int j=0;j<bytes/8;j++)
      sprintf(&contents[j*8], "%08x", rand()<<1 ^ rand());
    sprintf(&contents[bytes], "\n");
    fwrite(contents, 1, bytes+1, pFile);
  }
  fclose(pFile);
}

void Read_MPZ_FIle(SINT8 *filename ,MPZ *MPZs,SINT32 num){
  FILE* pFIle = fopen(filename, "rb");
  char str_prime[MAX_DATA_SIZE+1];
  MPZ * ptr_MPZ;

#if CONFIG_DEBUG
  printf("Read_MPZ_File function start!\n");
  printf("FileName : %s\n", filename);
  printf("num : %d\n", num);
#endif
  for(int m=0;m<num;m++){
    ptr_MPZ = &MPZs[m];
    fgets(str_prime,ptr_MPZ->len*8+1,pFIle);
    fgetc(pFIle);
    for(int i=ptr_MPZ->len; 0<i ; i--){
      ptr_MPZ->data[ptr_MPZ->len-i] = (int)strtol(&str_prime[i*8-8],NULL, 16);
      str_prime[i*8-8] = '\0';
    }
#if CONFIG_DEBUG
    printf("[%0.4d] sign : %d , blocks : %d\n ",m,ptr_MPZ->sign,ptr_MPZ->len);
    for(int i=ptr_MPZ->len-1; 0<=i ; i--)
      printf("%0.8x",ptr_MPZ->data[i]);
    printf("\n");
#endif
  }
}

void Write_MPZ_File(SINT8 *filename, MPZ *MPZs,SINT32 bytes, SINT32 num){
  FILE* pFile = fopen(filename, "wb");
  char contents[MAX_DATA_SIZE+2];
  for(int i=0;i<num;i++){
    for(int j=0;j<bytes/8;j++)
      sprintf(&contents[j*8], "%08x", MPZs[i].data[bytes/8 - j -1]);
    sprintf(&contents[bytes], "\n");
    fwrite(contents, 1, bytes+1, pFile);
  }
  fclose(pFile);
  
}

int MPZ_UADD(MPZ *first, MPZ *second, MPZ *result){
  int carry = 0;
  for(int i=0;i<first->len;i++){
    result->data[i] = first->data[i] + second->data[i] + carry;
    if(result->data[i] < first->data[i] + carry)
      carry = 1;
    else
      carry = 0;
  }
#if CONFIG_DEBUG
    for(int i=first->len-1; 0<=i ; i--)
      printf("%0.8x",result->data[i]);
    printf("\n");
#endif
  return 0;
}

int MPZ_ADD(MPZ *first, MPZ *second, MPZ *result){
  if(first->sign && second->sign){
    MPZ_UADD(first,second,result);
    result->sign = 1;
  }else if(first->sign == 0 && second->sign == 0){
    MPZ_UADD(first,second,result);
    result->sign = 0;
  }else if(first->sign == 0 && second){
    MPZ_USUB(first,second,result);
  }else if(first->sign && second == 0){
    MPZ_UADD(first,second,result);
  }
  return 0;
}

// 0 + 0 + 0 = 0
// 0
// 0 + 9 + 0 = 9
// 0 + 9 + 1 = 0
// 9 + 0 + 0 = 9
// 9 + 0 + 1 = 0
// 9 + 0 + 1 =


int MPZ_USUB(MPZ *first, MPZ *second, MPZ *result){
  int carry = 0;
  int i = 0;
  int max = first->len > second->len ? first->len : second->len;
  int min = first->len > second->len ? second->len : first->len;

  for(i=0;i<min;i++){
    result->data[i] = first->data[i] - second->data[i] + carry;
    if(first->data[i] + carry < result->data[i])
      carry = -1;
    else
      carry = 0;
  }
  for(;i<max;i++){
    result->data[i] = first->data[i] - second->data[i] + carry;
    if(first->data[i]  + carry < result->data[i])
      carry = -1;
    else
      carry = 0;
  }
  
  for(i=max; 0<=i && result->data[i] == 0;i--);

  result->len = i+1;
#if CONFIG_DEBUG
    for(int i=first->len-1; 0<=i ; i--)
      printf("%0.8x",result->data[i]);
    printf("\n");
#endif
  return 0;
}

int MPZ_SUB(MPZ *first, MPZ *second, MPZ *result){
  if(first->sign && second->sign){
    MPZ_USUB(first,second,result);
  }else if(first->sign == 0 && second->sign == 0){
    MPZ_USUB(first,second,result);
  }else if(first->sign == 0 && second){
    MPZ_UADD(first,second,result);
    result->sign = 0;
  }else if(first->sign && second == 0){
    MPZ_UADD(first,second,result);
    result->sign = 1;
  }
  return 0;
}

int BigNum_Compare(MPZ *first, MPZ *second){
  for(int i=first->len-1 ; 0 <= i;i--){
    if(first->data[i] > second->data[i])
      return 1;
    else if(first->data[i] < second->data[i])
      return -1;
  }

  return 0;
}

int BigNum_Swap(MPZ *first, MPZ *second){
  first->sign ^= second->sign ^=first->sign ^= second->sign;
  first->len ^= second->len ^= first->len ^= second->len;

  UINT32 *temp;
  temp = first->data;
  first->data = second->data;
  second->data =temp;
  return 0;
}

int BigNum_Sort(MPZ *MPZs,int size){
  for(int i=0;i<size-1;i++)
    for(int j=i+1;j<size;j++)
      if(BigNum_Compare(&MPZs[i],&MPZs[j]) == -1)
        BigNum_Swap(&MPZs[i],&MPZs[j]);
#if CONFIG_DEBUG
  for(int i=0;i<size;i++){
    for(int j=MPZs[i].len-1; 0<=j ; j--)
      printf("%0.8x",MPZs[i].data[j]);
    printf("\n");
  }
#endif
  return 0;
}

inline void BigNum_Block_Mul(UINT32 first,UINT32 second,UINT32 *result){
  UINT64 temp = (UINT64)first * (UINT64)second;
  if((result[0]+=(UINT32)temp) < (UINT32)temp)
    result[1]+=1;

  if((result[1]+=(temp >> 32)) < (temp >> 32)){
    result[2] +=1;
    for(int i = 2; i<MAX_DATA_SIZE;i++){
      if(result[i] == 0) result[i+1]++;
        else return;
    }
  }
}

void BigNum_Mul(MPZ *first, MPZ *second,MPZ *result){
  for(UINT32 i=0;i<result->len;i++)
    result->data[i] = 0;

  for(UINT32 i=0;i<first->len;i++)
    for(UINT32 j=0;j<second->len;j++)
      BigNum_Block_Mul(first->data[i],second->data[j],&result->data[i+j]);
  return;
}

void BigNum_Mul2(MPZ *first, MPZ *second,MPZ *result){
  for(UINT32 i=0;i<first->len*2;i++)
    for(UINT32 j=0;j<=i;j++)
      BigNum_Block_Mul(first->data[i-j],second->data[j],&result->data[i]);
  return;
}