/*
 * 無線コントローラーVS-C3のArduino用I2Cマスター
 * 2020.11.05
 * 
 * 参考にしたブログ
 * https://qiita.com/hikoalpha/items/7bf563ee286a59bfd2f4
 */

#include <Wire.h>

byte gamepad_state[20] = {};

void setup() {
  Wire.begin();
  Serial.begin(57600);
  Serial.println("master:");
}

void loop() {
    Wire.requestFrom(8, 20);// request 20 bytes from Slave ID #8
    
    while (Wire.available() < 20);
    for(int i=0;i<20;i++){
        gamepad_state[i] = Wire.read();
    }

    for(int i=0;i<20;i++){
        Serial.print(gamepad_state[i]);
        if(i==19){
            Serial.println("");
        } else {
            Serial.print(",");
        }
    }
}
