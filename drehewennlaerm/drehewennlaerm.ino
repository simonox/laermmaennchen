int currentValue;
#include <Adafruit_NeoPixel.h>
#define PIN 4

int maxValue;
int minValue;
unsigned long timer;
int sampleSpan = 10; // Amount in milliseconds to sample data
int volume; // this roughly goes from 0 to 700
const int motorPin1 = 8; // 8;  // Blue   - In 1
const int motorPin2 = 7; // 9;  // Pink   - In 2
const int motorPin3 = 6; // 10; // Yellow - In 3
const int motorPin4 = 5; // 11; // Orange - In 4
const int TRESHHOLD = 260;                          // Red    - pin 5 (VCC)
const int TRESHHOLD2 = 400;                          // Red    - pin 5 (VCC)

unsigned int lowSpeed  = 10000; // Notabene: nicht über 16000
unsigned int highSpeed =  1000;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  resetValues();
  Serial.begin(9600); 

}

void loop() {
    currentValue = analogRead(A0);


    if (currentValue < minValue) {
        minValue = currentValue;
    } 
    if (currentValue > maxValue) {
        maxValue = currentValue;
    }

    if (millis() - timer >= sampleSpan) {
        volume = maxValue - minValue;

        Serial.println(volume);
        if (volume > TRESHHOLD) {
            // g r b
            strip.setPixelColor(0,  Wheel((volume - 250) * 3));
            strip.setPixelColor(1,  Wheel((volume - 240) * 3));
            strip.show();  
        }
        if (volume > TRESHHOLD2) {
            strip.setPixelColor(0, 0, 255, 0);
            strip.setPixelColor(1, 0, 255, 0);

            strip.show();

            for (int i = 0; i < 100; i++) {
              rechtsrum(highSpeed); 
              delay(15);  
            }
            for (int i = 0; i < 100; i++) {
              linksrum(highSpeed); 
              delay(15);  
            }
            
        }

        //strip.setPixelColor(0, 0, 0, 0);
        //strip.setPixelColor(1, 0, 0, 0);
        //strip.show();
        resetValues();
    }
    
}

void resetValues()
{
    maxValue = 0;
    minValue = 40;
    timer = millis(); 
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


void rechtsrum(unsigned int motorSpeed)
{ // 1
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delayMicroseconds(motorSpeed);

  // 2
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delayMicroseconds(motorSpeed);

  // 3
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delayMicroseconds(motorSpeed);

  // 4
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delayMicroseconds(motorSpeed);

  // 5
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delayMicroseconds(motorSpeed);

  // 6
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delayMicroseconds(motorSpeed);

  // 7
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delayMicroseconds(motorSpeed);

  // 8
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delayMicroseconds(motorSpeed);
}

void linksrum(unsigned int motorSpeed)
{ // 1
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delayMicroseconds(motorSpeed);

  // 2
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delayMicroseconds(motorSpeed);

  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delayMicroseconds(motorSpeed);

  // 4
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delayMicroseconds(motorSpeed);

  // 5
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delayMicroseconds(motorSpeed);

  // 6
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delayMicroseconds(motorSpeed);

  // 7
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delayMicroseconds(motorSpeed);

  // 8
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delayMicroseconds(motorSpeed);
}

void stop()
{ digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
}

