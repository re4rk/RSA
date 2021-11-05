#include"typedef.h"
#include"BigNumber.h"
#include"Config.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>


time_t zxc =0;

MPZ * initMPZs(int bytes,int num){
    MPZ * temp = (MPZ*)malloc(sizeof(MPZ)*num);
    for(int i=0;i<num;i++){
        temp[i].sign = 0;
        temp[i].data = (UINT32*)calloc(bytes+1,sizeof(UINT32));
        temp[i].len = bytes/8;
    }
    return temp;
}

void Gen_BigNum_File(SINT8 *filename ,SINT32 bytes,SINT32 num){
  FILE* pFile = fopen(filename, "wb");
  char contents[MAX_DATA_SIZE+2];

  srand(time(NULL));
  rand();

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

  for(int m=0;m<num;m++){
    ptr_MPZ = &MPZs[m];
    fgets(str_prime,ptr_MPZ->len*8+1,pFIle);
    fgetc(pFIle);
    for(int i=ptr_MPZ->len; 0<i ; i--){
      ptr_MPZ->data[ptr_MPZ->len-i] = (int)strtol(&str_prime[i*8-8],NULL, 16);
      str_prime[i*8-8] = '\0';
    }
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
  int overflow = 0;
  MPZ * longer_MPZ = first->len > second->len ? first : second;
  int max = first->len > second->len ? first->len : second->len;
  int min = first->len > second->len ? second->len : first->len;

  for(int i=0;i<min;i++){
    result->data[i] = first->data[i] + second->data[i] + overflow;

    if(result->data[i] < first->data[i] + overflow) overflow = 1;
    else overflow = 0;
  }

  for(int i=min;i<max;i++){
    result->data[i] = longer_MPZ->data[i] + overflow;

    if(overflow == 1 && result->data[i] == 0) overflow = 1;
    else overflow = 0;
  }

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

int MPZ_USUB(MPZ *first, MPZ *second, MPZ *result){
  int underflow = 0;
  int i = 0;

  int max = first->len > second->len ? first->len : second->len;
  int min = first->len > second->len ? second->len : first->len;

  for(i=0;i<min;i++){
    result->data[i] = first->data[i] - second->data[i] + underflow;
    if(first->data[i] + underflow < result->data[i])
      underflow = -1;
    else
      underflow = 0;
  }
  
  if(max == first->len){
    for(i=min;i<max;i++){
      result->data[i] = first->data[i] + underflow;

      if(underflow == -1 && result->data[i] == 0) underflow = -1;
      else underflow = 0;
    }
  }else{
    for(i=min;i<max;i++){
      result->data[i] = -second->data[i] + underflow;

      if(underflow == -1 && result->data[i] == 0) underflow = -1;
      else underflow = 0;
    }
  }

  if(underflow){
    for(i=0;i<max;i++)
      result->data[i] ^= 0xffffffff;

    result->data[0]++;
    for(i=0;i<max;i++){
      if(result->data[i] == 0)
        result->data[i+1]++;
      else break;
    }
    result->sign = 1;
  }

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

int Compare_MPZ(MPZ *first, MPZ *second){
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
      if(Compare_MPZ(&MPZs[i],&MPZs[j]) == -1)
        BigNum_Swap(&MPZs[i],&MPZs[j]);
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

void COPY_MPZ(MPZ *r,MPZ *a){
  SINT32 i;

  if (r->data)
    free(r->data);
  r->data = (UINT32 *)malloc(sizeof(int) * a->len);

  for(i=0;i<a->len;i++)
    r->data[i] = a->data[i];
  r->len = a->len;
  r->sign = a->sign;
}

void MPZ_BIT_SHIFT(MPZ *r, MPZ *a, SINT32 shift){
  if(shift == 0){
    COPY_MPZ(r,a);
  }else if(0 < shift){
    r->sign = a->sign;
    if(a->data[(a->len-1) >> (32 - shift)])
      r->len = a->len+1;
    else
      r->len = a->len;

    r->data = realloc(r->data,r->len);
    r->data[a->len] = a->data[(a->len-1) >> (32 - shift)];

    for(int i=a->len-1 ; 0<i ; i--)
      r->data[i] = (a->data[i]<<shift) || (a->data[i-1]>>(32-shift));
    r->data[0] = (a->data[0]<<shift);
  }else if(shift < 0){
    int abs_shift = -shift;

    r->sign = a->sign;
    if((a->data[a->len-1]>>(32-abs_shift)))
      r->len = a->len;
    else
      r->len = a->len-1;
    
    r->data = realloc(r->data,r->len);
    r->data[a->len] = a->data[(a->len-1) >> (32 - shift)];

    r->data[a->len-1] = (a->data[a->len-1]>>(32-abs_shift));
    for(int i=a->len-2 ; 0<=i ; i--)
      r->data[i] = (a->data[i]>>abs_shift) || (a->data[i-1]>>(32-abs_shift));

    if(r->len == 0)
      r->sign = 0;
  }
}

void MPZ_WORD_SHIFT(MPZ *r, MPZ *a, SINT32 shift){
  if(shift == 0){
    COPY_MPZ(r,a);
  }else if(0<shift){
    for(int i=0;i<a->len;i++)
      r->data[i+shift] =a->data[i];
    r->sign = a->sign;
    r->len = a->len + shift;
  }else{
    for(int i =-shift;i< a->len;i++)
      r->data[i+shift]=a->data[i];
    r->sign = a->sign;
    r->len = a->len + shift;
    if(r->len <=0)
      r->len = 0;
  }
}


// normalization
void MPZ_UDIV(MPZ *q, MPZ *r,MPZ *a, MPZ *b){
  int i;
  int normbits;
  MPZ *x = initMPZs(DATA_SIZE,COUNT); 
  MPZ *y = initMPZs(DATA_SIZE,COUNT);
  MPZ *tmp = initMPZs(DATA_SIZE,COUNT);
  if(Compare_MPZ(a,b)){
    q->len = 0;
    q->sign = 0;
    COPY_MPZ(r,a);
  }else{
    for(i=31; 0<=i; i--)
      if( b->data[b->len-1] & (1<<i) )
        break;
    normbits = 31 - i;

    MPZ_BIT_SHIFT(x, a, normbits);
    MPZ_BIT_SHIFT(y, b, normbits);
    for(i=0;i<=x->len -y->len;i++){
      q->data[i]=0;
    }
    q->len = x->len - y->len +1;
    MPZ_WORD_SHIFT(tmp,y,x->len-y->len);
    if(Compare_MPZ(x,tmp)==1){
      q->data[x->len-y->len]++;
      MPZ_USUB(x,y,x);
    }

    for(i = x->len-1; y->len<=i ;i--){
      if(x->data[i] == y->data[y->len-1])
        q->data[i- y->len]= 0xffffffff;
      else
        q->data[i-y->len] = (((UINT64)x->data[i]<<32) | x->data[i-1]) / y->data[y->len -1];

      UINT32 x0,x1,x2;
      UINT64 x_,y_;

      x_ = (UINT64)q->data[i- y->len] * y->data[y->len-2];
      x0 = x_ & 0xffffffff;
      y_ = (UINT64)q->data[i- y->len] * y->data[y->len-1];
      y_ += x_ >> 32;
      x1 = y_ & 0xffffffff;
      x2 = y_ >> 32;
      if(x2 > x->data[i])
        q->data[i-y->len]--;
      // else if (x2 == x->data[i]){
      //   if(x>x->data[i-1])
      //     q->data[i-y->len]--;
      //   else if(x1 == -x->data[i-1]);
      //     if(x>x->data[i-2]){
      //       q->data[1-y->len]--;
      //     }
      // }
    }
  }
}
