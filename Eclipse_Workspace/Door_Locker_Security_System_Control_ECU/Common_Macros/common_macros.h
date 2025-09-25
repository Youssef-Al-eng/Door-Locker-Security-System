/***************************************************************************************************************
 * File: common_macros.h
 * Description: Common macros for bit manipulation (set, clear, toggle, rotate, check).
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a specific bit in any register */
#define SET_BIT(REG, BIT)        ((REG) |= (1 << (BIT)))

/* Clear a specific bit in any register */
#define CLEAR_BIT(REG, BIT)      ((REG) &= ~(1 << (BIT)))

/* Toggle a specific bit in any register */
#define TOGGLE_BIT(REG, BIT)     ((REG) ^= (1 << (BIT)))

/* Rotate right: circular shift of register by NUM bits */
#define ROR(REG, NUM)            ((REG) = ((REG) >> (NUM)) | ((REG) << (8 - (NUM))))

/* Rotate left: circular shift of register by NUM bits */
#define ROL(REG, NUM)            ((REG) = ((REG) << (NUM)) | ((REG) >> (8 - (NUM))))

/* Check if a specific bit is set (returns non-zero if set) */
#define BIT_IS_SET(REG, BIT)     ((REG) & (1 << (BIT)))

/* Check if a specific bit is clear (returns non-zero if clear) */
#define BIT_IS_CLEAR(REG, BIT)   (!((REG) & (1 << (BIT))))

/* Get the value of a specific bit (returns 0 or 1) */
#define GET_BIT(REG, BIT)        (((REG) & (1 << (BIT))) >> (BIT))

#endif /* COMMON_MACROS_H_ */
