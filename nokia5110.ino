#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 myDisplay = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

unsigned long stateMachine_currMillis;
unsigned long stateMachine_prevMillis_1s;

void setup()   {  
  delay(200);
  myDisplay.begin();  
  myDisplay.setContrast(60);  
  myDisplay.clearDisplay();   
  myDisplay.setRotation(2);    
  //self test
  myDisplay.fillRect(0, 0, 84, 64, BLACK);   
  myDisplay.display();
  delay(1000);
  myDisplay.clearDisplay();
}


void loop() {  
  stateMachine_currMillis = millis();
  if((stateMachine_currMillis-stateMachine_prevMillis_1s) > 1000){
    stateMachine_1s();
    stateMachine_prevMillis_1s = stateMachine_currMillis;
  } 
}

void stateMachine_1s(){   
  renderAcc();
}

void renderAcc(){
  uint8_t displayAccWidthMax = 19;
  uint8_t displayAccHeightMax = 7;
  
  myDisplay.fillRect(0, 0, 84, displayAccHeightMax, WHITE); //clear 
  
  uint16_t accVoltage_10bit = random(614, 859); // 3.0__4.2V
  float accVoltage = map(accVoltage_10bit, 0, 1023, 0, 500) / 100.0;
  uint16_t displayAccWidthCurr = map(accVoltage_10bit, 736, 859, 0, displayAccWidthMax);  // 3.6__4.2 V
  //int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color
  myDisplay.drawRect(0, 0, displayAccWidthMax, displayAccHeightMax, BLACK); 
  myDisplay.fillRect(0, 0, displayAccWidthCurr, displayAccHeightMax, BLACK); 
  
  myDisplay.setTextSize(1);
  myDisplay.setTextColor(BLACK);
  myDisplay.setCursor(displayAccWidthMax+2, 0);
  myDisplay.print(accVoltage, 2);  

  myDisplay.display();
}





