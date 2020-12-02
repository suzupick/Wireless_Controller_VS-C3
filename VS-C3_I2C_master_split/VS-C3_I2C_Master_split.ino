#include <Wire.h>
#include "motorDrv.hpp"
#include "VSC3_Master.hpp"

// uint8_t gamepad_state[20] = {0};

void setup() {
   Serial.begin(115200);
   Serial.println("master:");

   MD_Init();
   VSC3_Init();
}

void loop() {
    int tmp = VSC3_GetState();
    Serial.println( tmp );
    
//    if(return_value == 1){
//        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 255);
//        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 255);  
//    } else {
//        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 0);
//        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 0);  
//    };
}
