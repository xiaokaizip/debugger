//
// Created by 86136 on 2023/1/15.
//

#include "system.h"

/**
 * 将浮点数转化为16位无符号的数
 * @param data0
 * @return
 */
unsigned short FloatToInt16(float data0) {
    if (data0 == 0)
        return 0;
    unsigned short fInt16;
    unsigned int *pfp32 = ((unsigned int *) &data0);
    fInt16 = ((*pfp32 >> 16) & 0x8000) |
             ((((*pfp32 >> 23) - 0x7f + 0x0f) & 0x1f) << 10) |
             ((*pfp32 >> 13) & 0x3ff);
    return fInt16;
}

/**
 * 将无符号的16位数转化为小数
 * @param data0
 * @return
 */
float Int16ToFloat(unsigned short data0) {
    if (data0 == 0)
        return 0;
    float *fp32;
    unsigned int fInt32 = ((data0 & 0x8000) << 16) |
                          (((((data0 >> 10) & 0x1f) - 0x0f + 0x7f) & 0xff) << 23)
                          | ((data0 & 0x03FF) << 13);
    fp32 = (float *) &fInt32;
    return *fp32;
}
