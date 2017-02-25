/**
 *  @brief simple and fast sqrt alghortim (based on Jack Crenshaw method) 
 */
#ifndef __FIX_SQRT_H
#define __FIX_SQRT_H

#include <stdint.h>

/**
 * @brief calculate fixed point square root using successive approximation method
 */
static inline uint16_t fix_sqrt(uint32_t val)
{
    uint32_t rem = 0;
    uint32_t root = 0;
    int i;
    for(i = 0; i < 16; i++) {
        root <<= 1;
        rem = ((rem << 2) + (val >> 30));
        val <<= 2;
        root++;
        if(root <= rem) {
            rem-=root;
            root++;
        } else {
            root--;
        }
    }
    return((uint16_t) (root >> 1));
}
     
#endif