//===============================================
// File     : motorDrv.cpp
// Date     : 2020/10/07
// Design   : S.Ando
//===============================================
#include "motorDrv.hpp"
#include <Arduino.h>

/* Define */
#define DEF_MD1_A_BIT       (5)
#define DEF_MD1_A_DDR       (DDRD)
#define DEF_MD1_A_PORT      (PORTD)
#define DEF_MD1_B_BIT       (7)
#define DEF_MD1_B_DDR       (DDRD)
#define DEF_MD1_B_PORT      (PORTD)
#define DEF_MD2_A_BIT       (6)
#define DEF_MD2_A_DDR       (DDRD)
#define DEF_MD2_A_PORT      (PORTD)
#define DEF_MD2_B_BIT       (0)
#define DEF_MD2_B_DDR       (DDRB)
#define DEF_MD2_B_PORT      (PORTB)

/**
 * @fn MD_Init
 * @brief Initialize Motor Driver
 * @return void.
 */
void MD_Init(void)
{
    /* GPIO Initialize */
    DEF_MD1_A_PORT &= ~(1 << DEF_MD1_A_BIT);
    DEF_MD1_B_PORT &= ~(1 << DEF_MD1_B_BIT);
    DEF_MD2_A_PORT &= ~(1 << DEF_MD2_A_BIT);
    DEF_MD2_B_PORT &= ~(1 << DEF_MD2_B_BIT);
    DEF_MD1_A_DDR |= (1 << DEF_MD1_A_BIT);
    DEF_MD1_B_DDR |= (1 << DEF_MD1_B_BIT);
    DEF_MD2_A_DDR |= (1 << DEF_MD2_A_BIT);
    DEF_MD2_B_DDR |= (1 << DEF_MD2_B_BIT);

    /* PWM Timer Setting (Timer0, OUTPUT:OC0B, OC0A)*/
    TCCR0A = 0b10100011;    // 8bit High Speed PWM mode.
    TCCR0B = 0b00000011;    // 8bit High Speed PWM mode, clk/64.
    OCR0A = 0;              // OC0A Duty = 0(1clk pulse)
    OCR0B = 0;              // OC0B Duty = 0(1clk pulse)
}

/**
 * @fn MD_SetMotorState
 * @brief Set Motor rotation and power.
 * @param [in] ENUM_MOTOR_SEL sel : Motor select.
 * @param [in] ENUM_MOTOR_DIR dir : Motor direction of rotation.
 * @param [in] uint8_t duty : PWM Duty 0 - 255(max power).
 * @return void.
 */
void MD_SetMotorState(ENUM_MOTOR_SEL sel, ENUM_MOTOR_DIR dir, uint8_t duty)
{
    uint8_t tDuty = duty;

    if (sel == ENUM_MOTOR_SEL_LEFT)
    {
        if (dir == ENUM_MOTOR_DIR_CW) {
            DEF_MD1_B_PORT |= (1 << DEF_MD1_B_BIT);
            tDuty = 255 - duty;
        } else {
            DEF_MD1_B_PORT &= ~(1 << DEF_MD1_B_BIT);
        }
        OCR0B = tDuty;
    }
    else
    {
        if (dir == ENUM_MOTOR_DIR_CW) {
            DEF_MD2_B_PORT |= (1 << DEF_MD2_B_BIT);
            tDuty = 255 - duty;
        } else {
            DEF_MD2_B_PORT &= ~(1 << DEF_MD2_B_BIT);
        }
        OCR0A = tDuty;
    }
}

/**
 * @fn MD_StopAll
 * @brief Stop All Motor.
 * @return void.
 */
void MD_StopAll(void)
{
    DEF_MD1_B_PORT &= ~(1 << DEF_MD1_B_BIT);
    DEF_MD2_B_PORT &= ~(1 << DEF_MD2_B_BIT);
    OCR0B = 0;
    OCR0A = 0;
}
