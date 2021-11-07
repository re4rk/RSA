#include"typedef.h"
#pragma once

MPZ * newMPZs(int bytes,int num);
MPZ * newMPZ(int bytes);
void delMPZs(MPZ *temp,int num);
void delMPZ(MPZ *temp);


void Gen_BigNum_File(SINT8 *filename ,SINT32 bytes,SINT32 num);
void Read_MPZ_FIle(SINT8 *filename ,MPZ *arr,SINT32 num);
void Write_MPZ_File(SINT8 *filename, MPZ *MPZs,SINT32 bytes, SINT32 num);

int MPZ_UADD(MPZ *first, MPZ *second, MPZ *result);
int MPZ_USUB(MPZ *first, MPZ *second, MPZ *result);

int MPZ_ADD(MPZ *first, MPZ *second, MPZ *result);
void MPZ_MUL_BLOCK(UINT32 first,UINT32 second,UINT32 *result);
void MPZ_MUL(MPZ *first, MPZ *second,MPZ *result);

int Compare_MPZ(MPZ *first, MPZ *second);
int MPZ_Swap(MPZ *first, MPZ *second);
int MPZ_Sort(MPZ *MPZs,int size);
void COPY_MPZ(MPZ *r,MPZ *a);
void MPZ_BIT_SHIFT(MPZ *r, MPZ *a, SINT32 shift);
void MPZ_UDIV(MPZ *first, MPZ *secon,MPZ *a, MPZ *b);

void MPZ_MUL_with_single_block(UINT32 first, MPZ *second,MPZ *result);

void BIG_PRINT(MPZ *);