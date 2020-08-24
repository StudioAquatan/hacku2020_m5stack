# hacku2020_m5stack

お祈りメールが来たときに励ましてくれるシステム（m5stack）.

## m5stack スペック

https://www.switch-science.com/catalog/3647/  
LCD：$320\times240$  
WiFi：802.11 b/g/n （802.11a 5GHz は使用不可）

## Requirements

参考:[Mac で M5stack をはじめる - Qiita](https://qiita.com/hmmrjn/items/2b2da09eecffcbdbad85)

- Arduino IDE

### Arduino IDE Library

- M5Stack by M5Stack (Ver. 0.3.0)
- ESP8266Audio by Earle F. Philhower, III (Ver. 1.5.1)

動作確認済みのバージョンを記載

## 設定

1. WiFi の設定として`ssid`,`password`を設定する
2. 音声データと AR マーカ用の画像データを入れた SD カードを M5Stack に挿す
3. 音声データと AR マーカ用画像のファイルパスを`file~`という変数に設定する

## エンドポイント

### `http://m5stack.local/`

GET:  
return `Hello from m5stack`

### `http://m5stack.local/status`

POST: `status=positive`  
Start positive audio and display AR marker
return `Positive audio start`

POST: `status=negative`  
Start cheering audio and display AR marker
return `Cheering audio start`

POST: `status=off`  
Stop audio and turn to waiting mode
return `audio end`
