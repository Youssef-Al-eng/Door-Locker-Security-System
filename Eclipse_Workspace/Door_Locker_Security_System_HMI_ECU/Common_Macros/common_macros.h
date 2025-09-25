/***************************************************************************************************************
 * common_macros.h
 * Author: Youssef Alaa
 * Description: Common macros used for bit manipulation and register operations
 ***************************************************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* -------------------------- Bit Manipulation Macros -------------------------- */

/* Set a specific bit */
#define SET_BIT(REG, BIT)       ((REG) |= (1U << (BIT)))

/* Clear a specific bit */
#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(1U << (BIT)))

/* Toggle a specific bit */
#define TOGGLE_BIT(REG, BIT)    ((REG) ^= (1U << (BIT)))

/* Check if a specific bit is set (returns non-zero if true) */
#define BIT_IS_SET(REG, BIT)    ((REG) & (1U << (BIT)))

/* Check if a specific bit is clear (returns non-zero if true) */
#define BIT_IS_CLEAR(REG, BIT)  (!((REG) & (1U << (BIT))))

/* Get the value (0 or 1) of a specific bit */
#define GET_BIT(REG, BIT)       (((REG) >> (BIT)) & 0x01)

/* -------------------------- Bit Rotation Macros -------------------------- */

/* Rotate right an 8-bit register by a given number of positions */
#define ROR(REG, NUM)           ((REG) = ((REG) >> (NUM)) | ((REG) << (8 - (NUM))))

/* Rotate left an 8-bit register by a given number of positions */
#define ROL(REG, NUM)           ((REG) = ((REG) << (NUM)) | ((REG) >> (8 - (NUM))))

#endif /* COMMON_MACROS_H_ */
