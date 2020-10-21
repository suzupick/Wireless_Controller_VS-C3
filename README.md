# セットアップ
## PS2X_libのインストール
PS2コントローラー通信用ライブラリPS2X_libをArduinoのライブラリフォルダにダウンロードする。
https://github.com/simondlevy/PS2X_lib

## 配線
動作チェック用サンプルプログラムでの配線は下記の通り。

![wiring](https://github.com/suzupick/Wireless_Controller_VS-C3/blob/master/wiring.png)

VS-C3のピンアサイン
| Pin | 役割 | 
| --- | ---- | 
| 1   | 3.3V | 
| 2   | NC   | 
| 3   | SEL  | 
| 4   | DAT  | 
| 5   | NC   | 
| 6   | GNC  | 
| 7   | NC   | 
| 8   | CLK  | 
| 9   | CMD  | 
| 10  | NC   | 

通信はSEL, DAT, CLK, CMDのみ使う。
PS2コントローラーのCLOCK, COMMAND, ATTENTION, DATAとの対応は

- SEL → ATTENTION
- DAT → DATA
- CLK → CLOCK
- CMD → COMMAND

# コントローラーの動作チェック
1. レシーバーとArduinoを配線
1. VS-C3_test.inoを書き込む
1. コントローラーとレシーバーをペアリングする(ペアリング方法は説明書参照)。ペアリングできるとシリアルモニタに表示される。
1. コントローラーのボタンを押し、シリアルモニタに表示されることを確認する。
1. L1押下中にアナログスティックの入力値が表示されることを確認する。

# 参考

参考にしたブログ：
https://nakkye.at.webry.info/201411/article_1.html

PS2Xライブラリ：
https://github.com/simondlevy/PS2X_lib

画像：
http://twinklesmile.blog42.fc2.com/blog-entry-3.html
