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
        temp[i].dat = (UINT32*)calloc(MAX_DATA_SIZE,sizeof(UINT32));
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
      ptr_MPZ->dat[ptr_MPZ->len-i] = (int)strtol(&str_prime[i*8-8],NULL, 16);
      str_prime[i*8-8] = '\0';
    }
  }
}

void Write_MPZ_File(SINT8 *filename, MPZ *MPZs,SINT32 bytes, SINT32 num){
  FILE* pFile = fopen(filename, "wb");
  char contents[MAX_DATA_SIZE+2];
  for(int i=0;i<num;i++){
    for(int j=0;j<bytes/8;j++)
      sprintf(&contents[j*8], "%08x", MPZs[i].dat[bytes/8 - j -1]);
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
    result->dat[i] = first->dat[i] + second->dat[i] + overflow;

    if(result->dat[i] < first->dat[i] + overflow) overflow = 1;
    else overflow = 0;
  }

  for(int i=min;i<max;i++){
    result->dat[i] = longer_MPZ->dat[i] + overflow;

    if(overflow == 1 && result->dat[i] == 0) overflow = 1;
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
  UINT32 temp;
  int max = first->len > second->len ? first->len : second->len;
  int min = first->len > second->len ? second->len : first->len;

  for(i=0;i<min;i++){
    temp = first->dat[i];
    result->dat[i] = first->dat[i] - second->dat[i] + underflow;
    if(temp + underflow < result->dat[i])
      underflow = -1;
    else
      underflow = 0;
  }
  
  if(max == first->len){
    for(i=min;i<max;i++){
      result->dat[i] = first->dat[i] + underflow;

      if(underflow == -1 && result->dat[i] == 0) underflow = -1;
      else underflow = 0;
    }
  }else{
    for(i=min;i<max;i++){
      result->dat[i] = -second->dat[i] + underflow;

      if(underflow == -1 && result->dat[i] == 0) underflow = -1;
      else underflow = 0;
    }
  }

  if(underflow){
    for(i=0;i<max;i++)
      result->dat[i] ^= 0xffffffff;

    result->dat[0]++;
    for(i=0;i<max;i++){
      if(result->dat[i] == 0)
        result->dat[i+1]++;
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
  if(first->sign == 0 && second->sign == 1) return 1;
  else if(first->sign == 1 && second->sign == 0) return 0;
  else if(first->sign == 0 && second->sign == 0){
    if(first->len < second->len) return 1;
    else if(second->len < first->len)return 0;

    for(int i=first->len-1 ; 0 <= i;i--){
      if(first->dat[i] > second->dat[i]) return 1;
      else if(first->dat[i] < second->dat[i]) return 0;
    }
  }
  else if(first->sign == 1 && second->sign == 0){
    if(first->len < second->len) return 0;
    else if(second->len < first->len) return 1;

    for(int i=first->len-1 ; 0 <= i;i--){
      if(first->dat[i] > second->dat[i]) return 0;
      else if(first->dat[i] < second->dat[i]) return 1;
    }
  }
  return 1;
}

int BigNum_Swap(MPZ *first, MPZ *second){
  first->sign ^= second->sign ^=first->sign ^= second->sign;
  first->len ^= second->len ^= first->len ^= second->len;

  UINT32 *temp;
  temp = first->dat;
  first->dat = second->dat;
  second->dat =temp;
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
    result->dat[i] = 0;

  for(UINT32 i=0;i<first->len;i++)
    for(UINT32 j=0;j<second->len;j++)
      BigNum_Block_Mul(first->dat[i],second->dat[j],&result->dat[i+j]);
  return;
}

void BigNum_Mul_with_single_block(UINT32 first, MPZ *second,MPZ *result){
  for(UINT32 i=0;i<result->len;i++)
    result->dat[i] = 0;

  for(UINT32 i=0;i<second->len;i++)
    BigNum_Block_Mul(first,second->dat[i],&result->dat[i]);
    
  for(UINT32 i=second->len ; 0<=i; i--)
    if(result->dat[i] != 0){
      result->len = i+1;
      break;
    }
  return;
}

void COPY_MPZ(MPZ *r,MPZ *a){
  for(int i=0;i<a->len;i++)
    r->dat[i] = a->dat[i];
  r->len = a->len;
  r->sign = a->sign;
}

void MPZ_BIT_SHIFT(MPZ *r, MPZ *a, SINT32 shift){
  if(shift == 0){
    COPY_MPZ(r,a);
  }else if(0 < shift){
    r->sign = a->sign;
    if(a->dat[(a->len-1) >> (32 - shift)])
      r->len = a->len+1;
    else
      r->len = a->len;

    r->dat = realloc(r->dat,r->len);
    r->dat[a->len] = a->dat[(a->len-1) >> (32 - shift)];

    for(int i=a->len-1 ; 0<i ; i--)
      r->dat[i] = (a->dat[i]<<shift) || (a->dat[i-1]>>(32-shift));
    r->dat[0] = (a->dat[0]<<shift);
  }else if(shift < 0){
    int abs_shift = -shift;

    r->sign = a->sign;
    if((a->dat[a->len-1]>>(32-abs_shift)))
      r->len = a->len;
    else
      r->len = a->len-1;
    
    r->dat = realloc(r->dat,r->len);
    r->dat[a->len] = a->dat[(a->len-1) >> (32 - shift)];

    r->dat[a->len-1] = (a->dat[a->len-1]>>(32-abs_shift));
    for(int i=a->len-2 ; 0<=i ; i--)
      r->dat[i] = (a->dat[i]>>abs_shift) || (a->dat[i-1]>>(32-abs_shift));

    if(r->len == 0)
      r->sign = 0;
  }
}

void MPZ_WORD_SHIFT(MPZ* r, MPZ* a, SINT32 shift) //if shift>=0, left shift. Else, right shift
{
  r->len = a->len + shift;
  if(r->len == 0){
    r->sign = 0;
  }else{
    r->sign = a->sign;
    int i = shift >= 0 ? 0 : -shift;
    for(int j=0;j<i;j++)
      r->dat[j] = 0;
    for (; i < a->len; i++)
      r->dat[i + shift] = a->dat[i];
  }
}

// normalization
void MPZ_UDIV(MPZ *q, MPZ *r,MPZ *a, MPZ *b){
	SINT32 i, normbits;
	UINT32 x0, x1, x2;
	UINT64 x_, y_;
  MPZ *x = initMPZs(DATA_SIZE,COUNT); 
  MPZ *y = initMPZs(DATA_SIZE,COUNT);
  MPZ *tmp = initMPZs(DATA_SIZE,COUNT);

	if (Compare_MPZ(a, b) == 0){
		q->len = 0;
		q->sign = 0;
		COPY_MPZ(r, a);
	}else{
		//biginning of normalization
		for (i = 31; i >= 0; i--)
			if ((b->dat[b->len - 1] & (1 << i)) == 1)
				break;
		normbits = 31 - i;

		MPZ_BIT_SHIFT(x, a, normbits);
		MPZ_BIT_SHIFT(y, b, normbits);
    /// init q
		q->len = x->len - y->len + 1;
		for (i = 0; i < q->len; i++)
			q->dat[i] = 0;

    /// round 2
    MPZ_WORD_SHIFT(tmp, y, x->len - y->len);
		if (Compare_MPZ(x, tmp) == 1){
			q->dat[x->len - y->len]++;
			MPZ_USUB(x, x, tmp);
		}
		/// round 3
		for (i = x->len - 1; y->len <= i; i--){
      /// round 3.1
			if (x->dat[i] == y->dat[y->len - 1])
				q->dat[i - y->len] = 0xFFFFFFFF;
			else
				q->dat[i - y->len] = (((UINT64)x->dat[i] << 32) | x->dat[i - 1]) / y->dat[y->len - 1];

      /// round 3.2
			x_=(UINT64)q->dat[i - y->len] * y->dat[y->len - 2];
			x0=x_ & 0xffffffff;
			y_ = (UINT64)q->dat[i - y->len] * y->dat[y->len - 1];
			y_ += x_ >> 32;
			x1=y_ & 0xffffffff;
			x2 = y_ >> 32;
			if (x2 > x->dat[i])
				q->dat[i - y->len]--;
			else if (x2 == x->dat[i])
			{
				if(x1>x->dat[i-1])
					q->dat[i - y->len]--;
				else if(x1 == x->dat[i-1])
					if(x0>x->dat[i-2])
						q->dat[i - y->len]--;
			}
      /// round 3.3
      BigNum_Mul_with_single_block(q->dat[i - y->len], y,tmp);
      MPZ_USUB(x, x, tmp);
      /// round 3.4
      if(x->sign == 1){
        MPZ_UADD(x, x, y);
        q->dat[i - y->len]--;
      }
		}
	}
  COPY_MPZ(r, x);
}

