#pragma once

typedef unsigned long long UINT64;
typedef long long SINT64;

typedef unsigned int UINT32;
typedef int SINT32;

typedef unsigned short UINT16;
typedef short SINT16;

typedef unsigned char UINT8;
typedef char SINT8;

#define COUNT 10000
#define DATA_SIZE 2048
#define MAX_DATA_SIZE 4097
typedef struct {
    SINT8 sign;
    UINT32 len;
    UINT32 *data;
}MPZ;
