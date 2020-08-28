#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// wifi settings
const char* ssid = "********";
const char* password = "********";
const char* domain = "m5stack";
WebServer server(80);

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

// data files path in SD card
char* filePositiveARMarker = "/filePositiveARMarker.jpg";
char* filePositiveMP3 = "/filePositiveMP3.mp3";
char* fileNegativeARMarker = "/fileNegativeARMarker.jpg";
char* fileNegativeMP3 = "/fileNegativeMP3.mp3";
char* fileDefault = "/fileDefault.jpg";

/* Plays MP3 */
void playMP3(char *filename){
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(1.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
}

/* Draws 320x240 JPG file */
void drawARMarker(char *filename) {
  uint16_t x = 40;
  uint16_t y = 0;

  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.drawJpgFile(SD, filename, x, y);
}

/* ENDPOINT:Root */
void handleRoot() {
  server.send(200, "text/plain", "hello from m5stack!");
  M5.Lcd.println("Hello");
}

/* ENDPOINT:status */
void handleStatus() {
  if (server.method() == HTTP_POST){
    String postdata = "";
    for (uint8_t i = 0; i < server.args(); i++){
      if (server.argName(i) == "status"){
        postdata = server.arg(i);
        Serial.println(postdata);
        break;
      }
    }

    if (postdata == "positive"){
      drawARMarker(filePositiveARMarker);
      mp3->stop();
      playMP3(filePositiveMP3);
      server.send(200, "text/plain", "Positive audio start");
    } else if (postdata == "negative"){
      drawARMarker(fileNegativeARMarker);
      mp3->stop();
      delay(10000);
      playMP3(fileNegativeMP3);
      server.send(200, "text/plain", "Cheering audio start");
    } else if (postdata == "off"){
      M5.Lcd.fillScreen(TFT_BLACK);
      mp3->stop();
      server.send(200, "text/plain", "audio end");
    }
    
    server.send(400, "text/plain", "Bad Request");
  } else {
    server.send(400, "text/plain", "Require POST Method");
  }
}

/* ENDPOINT:URI Not Found */
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  M5.Lcd.println("Not Found");
}

void setup(){
  M5.begin();
  M5.Power.begin();

  // WiFi preparation
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if(MDNS.begin(domain)) {
    Serial.println("MDNS responder started");
  }

  // Server start
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
  // LCD display
  M5.Lcd.setTextSize(3);
  drawARMarker(fileDefault);
  Serial.println("Waiting");
  
  playMP3(filePositiveMP3);
  mp3->stop();
}

void loop() {
  if(mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  }
  server.handleClient();
}
