#include <M5Stack.h>

/* Draws 200x200 JPG file */
void drawARMarker(char *filename) {
  uint16_t x = 60;
  uint16_t y = 20;

  M5.Lcd.drawJpgFile(SD, filename, x, y);
}

// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin();

  /*
    Power chip connected to gpio21, gpio22, I2C device
    Set battery charging voltage and current
    If used battery, please call this function in your project
  */
  M5.Power.begin();
    
  // LCD display
  M5.Lcd.print("Hello World");
}

// the loop routine runs over and over again forever
void loop() {
  
  M5.update();
  if (M5.BtnA.wasPressed()){
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Button A");
  }
  if (M5.BtnB.wasPressed()){
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Button B");
  }
  if (M5.BtnC.wasPressed()){
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Button C");
  }

}
