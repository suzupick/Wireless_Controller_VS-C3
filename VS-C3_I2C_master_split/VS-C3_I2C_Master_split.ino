// #include <Wire.h>
// //#include "motorDrv.hpp"
// #include "VSC3_Master.hpp"

// void setup() {
// //  Wire.begin();
//   Serial.begin(115200);
//   Serial.println("master:");

// //  MD_Init();
//   VSC3_Init();
// }

// void loop() {
//     int return_value = 0;
//     VSC3_GetState( return_value );
//     Serial.println( return_value );
    
// //    if(tmp == 1){
// //        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 255);
// //        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 255);  
// //    } else {
// //        MD_SetMotorState(ENUM_MOTOR_SEL_LEFT, ENUM_MOTOR_DIR_CW, 0);
// //        MD_SetMotorState(ENUM_MOTOR_SEL_RIGHT, ENUM_MOTOR_DIR_CW, 0);  
// //    }


// }

#include <Wire.h>
// #include "VSC3_Master.hpp"

// void VSC3_Init(void);
// void VSC3_GetState(int& return_value);

byte gamepad_state[20] = {0};
byte gamepad_state_cmp[6] = {0};

void setup() {
  Serial.begin(115200);
  Serial.println("master:");
  VSC3_Init();
}

void loop() {
//    int return_value = 0;
//    VSC3_GetState( return_value );

    Wire.requestFrom(8, 6); // アドレス8のスレーブに6バイトのデータをリクエスト
    
    while (Wire.available() < 6); // 6バイト受け取るまで待機
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
    
    Serial.println( gamepad_state[7] );
}

void VSC3_Init(void)
{
    // I2C Initialize
    Wire.begin();
    // Wire.setClock(400000L);
}

void VSC3_GetState(int& return_value)
{
    Wire.requestFrom(8, 6); // アドレス8のスレーブに6バイトのデータをリクエスト
    
    while (Wire.available() < 6); // 6バイト受け取るまで待機
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

    return_value = (int)gamepad_state[7];
}
