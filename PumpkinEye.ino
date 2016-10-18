#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

long randNumber;

int const defaultPupilX = 3;
int const defaultPupilY = 3;
int const pupilX = 3;
int const pupilY = 3;


void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address

  randomSeed(analogRead(0));
}

static const uint8_t PROGMEM
  baseEyeball[] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
  },
  eyeball[] = {
    B00111100,
    B01111110,
    B11111111,
    B11100111,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blank[] {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  eyeDownRight1[] {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11110011,
    B11110011,
    B01111110,
    B00111100
  },
  eyeDownRight2[] {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111001,
    B01111000,
    B00111100
  }
  ;


void loop() {

  drawDefaultEye();

  int wait = random(10,10000);
  delay(wait);

//   Serial.println(getWeightedRandomNumber());

   blink();
  
//  lookDown();



  //lookDownRight();

  //pulsateEye();

  // matrix.setBrightness(1);
  // blink();
  // delay(2500);

  //snooze();  
  //delay(2500);
}

int getWeightedRandomNumber() {
  
    int weightedChoices[] = { 75, 50, 25 };
    int sumOfWeight = 150;
    int choiceCount = 3;
        
    for(int i = 0; i < choiceCount; i++) {
       sumOfWeight += weightedChoices[i];
    }
    
    int rnd = random(sumOfWeight);
    
    for(int i = 0; i < choiceCount; i++) {
      if(rnd < weightedChoices[i])
        return i;
      rnd -= weightedChoices[i];
    }
}

void lookDown() {
    matrix.clear();
    drawDefaultEye();
    matrix.writeDisplay();

    delay(200);

    for(int i = 4; i < 7; i++){
        drawBaseEyeBall();
        matrix.fillRect(i, 3, 2, 2, LED_OFF);
        matrix.writeDisplay();
        delay(20);
    }
    delay(2000);

}

void lookDownRight() {

  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);

  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(750);
  
  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);  
}

void snooze() {
  matrix.clear();
  matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
  matrix.writeDisplay();

  matrix.setTextSize(1);
  matrix.setTextWrap(false); 
  matrix.setTextColor(LED_ON);

  delay(2500);    

  for (int8_t x=0; x>=-60; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("ZZZZZZZZZZZZZZZZ");
    matrix.writeDisplay();
    delay(100);
  }

  matrix.clear();
  matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);    

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void blink() {
    int blinkSpeed = getRandomBlinkSpeed();
    closeEyeLid(blinkSpeed);
    openEyeLid(blinkSpeed);
}

int getRandomBlinkSpeed() {
    return random(10, 45);
}

void closeEyeLid(int blinkSpeed) {
    for(int lidHeight = 0; lidHeight < 9; lidHeight++) {
        drawEyeWithLid(lidHeight);
        delay(blinkSpeed);
    }
}

void openEyeLid(int blinkSpeed) {
    for(int lidHeight = 9; lidHeight >= 0; lidHeight--) {
        drawEyeWithLid(lidHeight);
        delay(blinkSpeed);
    }
}

void drawEyeWithLid(int lidHeight) {
    drawBaseEyeBall();
    drawCenteredPupil();
    matrix.fillRect(-1,-1, lidHeight, 9, LED_OFF);
    matrix.writeDisplay();
}

void drawDefaultEye() {
  drawBaseEyeBall();
  drawCenteredPupil();
  matrix.writeDisplay();
}

void drawBaseEyeBall() {
    matrix.clear();
    matrix.drawBitmap(0,0, baseEyeball, 8, 8, LED_ON);
}

void drawCenteredPupil() {
    matrix.fillRect(defaultPupilX, defaultPupilY, 2, 2, LED_OFF);
}

void pulsateEye() {    
    for(int i = 0; i < 100; i++) {
        dimEye();
        brightenEye();
    }    
}

void dimEye() {
    for(int brightness = 16; brightness > 0; brightness--) {
        setBrightnessAndDrawEye(brightness);
        delay(1);
    }
}

void brightenEye() {
    for(int brightness = 0; brightness < 16; brightness++) {
        setBrightnessAndDrawEye(brightness);
        delay(1);        
    }
}

void setBrightnessAndDrawEye(int brightness) {
    matrix.setBrightness(brightness);
    drawBaseEyeBall();
    drawCenteredPupil();
    matrix.writeDisplay();
}








