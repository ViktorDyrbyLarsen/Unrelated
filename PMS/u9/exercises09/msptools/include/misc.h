#ifndef MSPTOOLS_MISC_H
#define MSPTOOLS_MISC_H

enum storage_order
{
    RowMajor,
    ColMajor
};

enum cstype
{
    CSC,
    CSR
};

#define MSP_SUCCESS 0
#define MSP_FAILURE 1
#define MSP_MEM_ERR 2
#define MSP_FILE_ERR 3
#define MSP_ILLEGAL_INPUT 4
#define MSP_STRIDE_ERR 5
#define MSP_DIM_ERR 6

#define MEM_ERR fprintf(stderr, "%s: failed to allocate memory\n", __func__)
#define FILE_ERR(x) fprintf(stderr, "%s: failed to open file %s\n", __func__, x)
#define INPUT_ERR fprintf(stderr, "%s: received NULL pointer as input\n", __func__)

#endif