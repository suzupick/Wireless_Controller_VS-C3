//===============================================
// File     : motorDrv.hpp
// Date     : 2020/10/07
// Design   : S.Ando
//===============================================
#ifndef __MOTOR_DRV_H
#define __MOTOR_DRV_H

/**************************************************
 * Include
 *************************************************/
#include <stdint.h>

/**************************************************
 * ENUM
 *************************************************/
typedef enum {
    ENUM_MOTOR_DIR_CCW = 0,
    ENUM_MOTOR_DIR_CW
} ENUM_MOTOR_DIR;

typedef enum {
    ENUM_MOTOR_SEL_LEFT = 0,
    ENUM_MOTOR_SEL_RIGHT
} ENUM_MOTOR_SEL;

/**************************************************
 * Const
 *************************************************/
/* None */

/**************************************************
 * Prototype
 *************************************************/
void MD_Init(void);
void MD_SetMotorState(ENUM_MOTOR_SEL sel, ENUM_MOTOR_DIR dir, uint8_t duty);
void MD_StopAll(void);

#endif
