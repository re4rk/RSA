#include"typedef.h"
#pragma once

void Gen_BigNum_File(SINT8 *filename ,SINT32 bytes,SINT32 num);
void Read_MPZ_FIle(SINT8 *filename ,MPZ *arr,SINT32 num);
void Write_MPZ_File(SINT8 *filename, MPZ *MPZs,SINT32 bytes, SINT32 num);

int BigNum_Add(MPZ *first, MPZ *second, MPZ *result);
int BigNum_Sub(MPZ *first, MPZ *second, MPZ *result);
void BigNum_Block_Mul(UINT32 first,UINT32 second,UINT32 *result);
void BigNum_Mul(MPZ *first, MPZ *second,MPZ *result);
void BigNum_Mul2(MPZ *first, MPZ *second,MPZ *result);


int BigNum_Compare(MPZ *first, MPZ *second);
int BigNum_Swap(MPZ *first, MPZ *second);
int BigNum_Sort(MPZ *MPZs,int size);