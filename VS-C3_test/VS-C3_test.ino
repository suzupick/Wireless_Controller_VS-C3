/* 
 *  無線コントローラーVS-C3の動作チェック用スケッチ
 *  2020.10.21
 *  鈴木遼
 *  
 *  <動作チェック手順>
 *  レシーバーとArduinoを配線し、コントローラーとレシーバーをペアリングする。配線はREADMEを参照。
 *  シリアルモニタ(ボーレート57600)で接続できたか確認。
 *  押したボタンがシリアルモニタに表示される。
 *  アナログスティックについては、L1入力中のみ座標を表示する仕様。
 *  
 *  参考にしたブログ：
 *  https://nakkye.at.webry.info/201411/article_1.html
 *  
 *  PS2Xライブラリ：
 *  https://github.com/simondlevy/PS2X_lib
 */

#include <PS2X_lib.h>

// インスタンスを生成
PS2X ps2x;

int error = 0; // エラー値の変数
byte vibrate = 0; // 振動機能のON/OFF?　あんまり調べていない

void setup() {
    Serial.begin(57600);
    
    // ピンのセットアップ、PrressuresとRumble(?)の設定。返り値でエラー判定
    error = ps2x.config_gamepad(13, 11, 10, 12, true, true);
    
    if (error == 0) {
        Serial.println("Found Controller, configured successful");
    } else if (error == 1) {
        Serial.println("error1: No controller found, check wiring, see readme.txt to enable debug. ");
    } else if (error == 2) {
        Serial.println("error2: Controller found but not accepting commands. see readme.txt to enable debug. ");
    } else if (error == 3) {
        Serial.println("error3: Controller refusing to enter Pressures mode, may not support it. ");
    }
    
    // Serial.print(ps2x.Analog(1), HEX);
    Serial.println("PS-C2 Controller Found OK! "); //ＰＳ－２Ｃコントローラー
}


void loop() {
    ps2x.read_gamepad(false, vibrate); //ゲームパッド・ボタンの読み込み
    
    if (ps2x.Button(PSB_START)) //スタートボタン
        Serial.println("Start");
    if (ps2x.Button(PSB_SELECT)) //セレクトボタン
        Serial.println("Select");
    
    if (ps2x.Button(PSB_PAD_UP)) //上ボタン
        Serial.println("U");
    if (ps2x.Button(PSB_PAD_RIGHT)) //右ボタン
        Serial.println("R");
    if (ps2x.Button(PSB_PAD_LEFT)) //左ボタン
        Serial.println("L");
    if (ps2x.Button(PSB_PAD_DOWN)) //下ボタン
        Serial.println("D");
    
    if (ps2x.Button(PSB_GREEN)) //△ボタン
        Serial.println("GREEN");
    if (ps2x.Button(PSB_RED)) //〇ボタン
        Serial.println("RED");
    if (ps2x.Button(PSB_PINK)) //□ボタン
        Serial.println("PINK");
    if (ps2x.Button(PSB_BLUE)) //×ボタン
        Serial.println("BLUE");
    
    if (ps2x.Button(PSB_L3))
        Serial.println("L3");
    if (ps2x.Button(PSB_R3))
        Serial.println("R3");
    if (ps2x.Button(PSB_L2))
        Serial.println("L2");
    if (ps2x.Button(PSB_R2))
        Serial.println("R2");
    if (ps2x.Button(PSB_R1))
        Serial.println("R1");

    // L1を押している間、アナログスティックの入力を表示
    if (ps2x.Button(PSB_L1)) {
        Serial.print(ps2x.Analog(PSS_LY), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC);
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
    
    delay(50);
}
