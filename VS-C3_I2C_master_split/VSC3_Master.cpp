//===============================================
// File     : VS-C3_Master.cpp
// Date     : 2020/11/29
// Design   : R.Suzuki
//===============================================
#include <Wire.h>
#include "VSC3_Master.hpp"

uint8_t gamepad_state[20] = {0};
uint8_t gamepad_state_cmp[6] = {0};

/**
 * @fn VSC3_Init
 * @brief Initialize I2C on master side.
 * @return void.
 */
void VSC3_Init(void)
{
    // I2C Initialize
    Wire.begin();
    Wire.setClock(400000L);
}

/**
 * @fn VSC3_GetState
 * @brief Get gamepad state.
 * @return int : Gamepad state
 */
uint8_t VSC3_GetState(void)
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

    return gamepad_state[7];

    // // デバッグ用
    // for(int i=0;i<20;i++){
    //     Serial.print(gamepad_state[i]);

    //     if(i==19){
    //         Serial.println("");
    //     } else {
    //         Serial.print(",");
    //     }
    // }
}
