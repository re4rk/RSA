#include"typedef.h"
#pragma once

MPZ * initMPZs(int bytes,int num);

void Gen_BigNum_File(SINT8 *filename ,SINT32 bytes,SINT32 num);
void Read_MPZ_FIle(SINT8 *filename ,MPZ *arr,SINT32 num);
void Write_MPZ_File(SINT8 *filename, MPZ *MPZs,SINT32 bytes, SINT32 num);

int MPZ_UADD(MPZ *first, MPZ *second, MPZ *result);
int MPZ_USUB(MPZ *first, MPZ *second, MPZ *result);

int MPZ_ADD(MPZ *first, MPZ *second, MPZ *result);
void BigNum_Block_Mul(UINT32 first,UINT32 second,UINT32 *result);
void BigNum_Mul(MPZ *first, MPZ *second,MPZ *result);
void BigNum_Mul2(MPZ *first, MPZ *second,MPZ *result);

int Compare_MPZ(MPZ *first, MPZ *second);
int BigNum_Swap(MPZ *first, MPZ *second);
int BigNum_Sort(MPZ *MPZs,int size);
void COPY_MPZ(MPZ *r,MPZ *a);
void MPZ_BIT_SHIFT(MPZ *r, MPZ *a, SINT32 shift);
void MPZ_UDIV(MPZ *first, MPZ *secon,MPZ *a, MPZ *b);