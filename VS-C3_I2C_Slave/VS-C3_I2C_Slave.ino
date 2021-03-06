/*
 * 無線コントローラーVS-C3のArduino用I2Cマスター
 * 2020.11.05
 * 
 * 参考にしたブログ
 * https://qiita.com/hikoalpha/items/7bf563ee286a59bfd2f4
 */

#include <Wire.h>
#include <PS2X_lib.h>

void requestEvent(); // プロトタイプ宣言

PS2X ps2x; // PS2Xクラスのインスタンスを生成
int error = 0; // エラー値の変数
byte vibrate = 0; // 振動機能のON/OFF?　あんまり調べていない
byte gamepad_state[20] = {0}; // コントローラのボタン押下状態　ゼロで初期化
byte gamepad_state_cmp[6] = {0}; // コントローラのボタン押下状態(圧縮版)　ゼロで初期化

void setup() {
    Serial.begin(57600);
    Serial.println("slave:");
    
    // ピンのセットアップ、PressuresとRumble(?)の設定。返り値でエラー判定
    error = ps2x.config_gamepad(7, 2, 8, 4, false, false);
    
    if (error == 0) {
        Serial.println("Controller found, configured successful.");
    } else if (error == 1) {
        Serial.println("error1: No controller found, check wiring.");
    } else if (error == 2) {
        Serial.println("error2: Controller found but not accepting commands.");
    } else if (error == 3) {
        Serial.println("error3: Controller refusing to enter Pressures mode, may not support it.");
    }
    
    // Serial.print(ps2x.Analog(1), HEX);
    // Serial.println("Controller found! OK!");
    Wire.begin(8);// Slave ID #8
    Wire.onRequest(requestEvent);
}

void loop() {
}

void requestEvent() {
    ps2x.read_gamepad(false, vibrate); //ゲームパッド・ボタンの読み込み

    // gamepad_stateにボタン押下状態を格納   
    gamepad_state[0] = ps2x.Button(PSB_START);
    gamepad_state[1] = ps2x.Button(PSB_SELECT);
    gamepad_state[2] = ps2x.Button(PSB_PAD_UP);
    gamepad_state[3] = ps2x.Button(PSB_PAD_RIGHT);
    gamepad_state[4] = ps2x.Button(PSB_PAD_LEFT);
    gamepad_state[5] = ps2x.Button(PSB_PAD_DOWN);
    gamepad_state[6] = ps2x.Button(PSB_GREEN);
    gamepad_state[7] = ps2x.Button(PSB_RED);
    gamepad_state[8] = ps2x.Button(PSB_PINK);
    gamepad_state[9] = ps2x.Button(PSB_BLUE);
    gamepad_state[10] = ps2x.Button(PSB_L3);
    gamepad_state[11] = ps2x.Button(PSB_R3);
    gamepad_state[12] = ps2x.Button(PSB_L2);
    gamepad_state[13] = ps2x.Button(PSB_R2);
    gamepad_state[14] = ps2x.Button(PSB_L1);
    gamepad_state[15] = ps2x.Button(PSB_R1);
    gamepad_state[16] = ps2x.Analog(PSS_LX);
    gamepad_state[17] = ps2x.Analog(PSS_LY);
    gamepad_state[18] = ps2x.Analog(PSS_RX);
    gamepad_state[19] = ps2x.Analog(PSS_RY);

    // 20バイト→6バイトに圧縮
    gamepad_state_cmp[0] = 0;
    gamepad_state_cmp[1] = 0;
    for (int i=0; i<8; i++){
        gamepad_state_cmp[0] += (gamepad_state[i] << i); // 1バイト目のiビット目に格納
        gamepad_state_cmp[1] += (gamepad_state[8 + i] << i); // 2バイト目のiビット目に格納
    }

    for (int i=0; i<4; i++){
        gamepad_state_cmp[i + 2] = gamepad_state[16 + i]; // ジョイスティックの情報をi+2 バイト目に格納
    }

//    Wire.write(gamepad_state, 20); 
    Wire.write(gamepad_state_cmp, 6);
    
//    // デバッグ用
//    if (ps2x.Button(PSB_START)) Serial.println("Start");
//    if (ps2x.Button(PSB_SELECT)) Serial.println("Select");
//    if (ps2x.Button(PSB_PAD_UP)) Serial.println("U");
//    if (ps2x.Button(PSB_PAD_RIGHT)) Serial.println("R");
//    if (ps2x.Button(PSB_PAD_LEFT)) Serial.println("L");
//    if (ps2x.Button(PSB_PAD_DOWN)) Serial.println("D");
//    if (ps2x.Button(PSB_GREEN)) Serial.println("GREEN");
//    if (ps2x.Button(PSB_RED)) Serial.println("RED");
//    if (ps2x.Button(PSB_PINK)) Serial.println("PINK");
//    if (ps2x.Button(PSB_BLUE)) Serial.println("BLUE");
//    if (ps2x.Button(PSB_L3)) Serial.println("L3");
//    if (ps2x.Button(PSB_R3)) Serial.println("R3");
//    if (ps2x.Button(PSB_L2)) Serial.println("L2");
//    if (ps2x.Button(PSB_R2)) Serial.println("R2");
//    if (ps2x.Button(PSB_R1)) Serial.println("R1");
//    if (ps2x.Button(PSB_L1)) {
//        // L1を押している間、アナログスティックの入力を表示
//        Serial.print(ps2x.Analog(PSS_LY), DEC);
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_LX), DEC);
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_RY), DEC);
//        Serial.print(",");
//        Serial.println(ps2x.Analog(PSS_RX), DEC);
//    }
}
