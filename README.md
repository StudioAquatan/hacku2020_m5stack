# hacku2020_m5stack

お祈りメールが来たときに励ましてくれるシステム（m5stack）.

## m5stack スペック

https://www.switch-science.com/catalog/3647/  
LCD：$320\times240$  
WiFi：802.11 b/g/n （802.11a 5GHz は使用不可）

## エンドポイント

### `http://m5stack.local/`

GET:  
return `Hello from m5stack`

### `http://m5stack.local/status`

POST: `{"status": "positive"}`  
Start positive audio and display AR marker
return `Positive audio start`

POST: `{"status": "negative"}`  
Start negative audio and display AR marker
return `Negative audio start`

POST: `{"status": "off"}`  
Stop audio and turn to waiting mode
return `audio end`
