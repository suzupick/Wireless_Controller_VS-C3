#include <Wire.h>
#include "motorDrv.hpp"

byte gamepad_state[20] = {0};
byte gamepad_state_cmp[6] = {0};

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("master:");

  MD_Init();
}

void loop() {
    Wire.requestFrom(8, 6);// request 6 bytes from Slave ID 8
    
    while (Wire.available() < 6);
    for(int i=0;i<6;i++){
        gamepad_state_cmp[i] = Wire.read();
    }

    // 解凍
    for (int i=0; i<8; i++){
        gamepad_state[i] = (gamepad_state_cmp[0] & 0x01); // 1ビット目を取り出す
        gamepad_state_cmp[0] >>= 1; // 1ビット右シフト
        
        gamepad_state[i + 8] = (gamepad_state_cmp[1] & 0x01); // 1ビット目を取り出す
        gamepad_state_cmp[1] >>= 1; // 1ビット右シフト
    }

    for (int i = 16; i<20; i++){
        gamepad_state[i] = gamepad_state_cmp[i - 14]; // ジョイスティックの情報を取り出す
    }

    // デバッグ用
    for(int i=0;i<20;i++){
        Serial.print(gamepad_state[i]);

        if(i==19){
            Serial.println("");
        } else {
            Serial.print(",");
        }
    }

    if(gamepad_state[7] == 1){
        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 255);
        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 255);  
    } else {
        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 0);
        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 0);  
    }
}
