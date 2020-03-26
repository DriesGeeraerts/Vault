#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"


#include <Servo.h>
#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 21
#define ROTARY_ENCODER_BUTTON_PIN 25
#define ROTARY_ENCODER_VCC_PIN 27
int code1 = 7;
int code2 = 1;
int code3 = 13;

bool open1 = false;
bool open2 = false;
bool open3 = false;
int count1 = 0;
int count2 = 0;
int count3 = 0;

Servo myservo;
int posOpen = 180;
int posToe = 0;
int pos = 0;

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);

int test_limits = 2;

void rotary_onButtonClick() {
  rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
  test_limits *= 2;
}

void rotary_loop() {

  if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {

    rotary_onButtonClick();
  }

  int16_t encoderDelta = rotaryEncoder.encoderChanged();
  
  if (encoderDelta>0) Serial.print("+");
  if (encoderDelta<0) Serial.print("-");

  
    int16_t encoderValue = rotaryEncoder.readEncoder();
     if (encoderValue == code1){
            delay(100);
     int16_t encoderValue = rotaryEncoder.readEncoder();
    count1 = count1 + 1;
    Serial.println(encoderValue);
    Serial.println(count1);
     }
    if (count1 > 10){

      open1 = true;
      Serial.println(open1);
      count1 = 0;
    }
    if (encoderValue == code2){
            delay(100);
     int16_t encoderValue = rotaryEncoder.readEncoder();
    count2 = count2 + 1;
    Serial.println(encoderValue);
    Serial.println(count2);
     }
    if (count2 > 10){

      open2 = true;
      Serial.println(open1);
      count2 = 0;
    }
    if (encoderValue == code3){
            delay(100);
     int16_t encoderValue = rotaryEncoder.readEncoder();
    count3 = count3 + 1;
    Serial.println(encoderValue);
    Serial.println(count1);
     }
    if (count3 > 10){

      open3 = true;
      Serial.println(open3);
      count3 = 0;
    }
    Serial.print("Value: ");
    Serial.println(encoderValue);
    Serial.println(open1);
    Serial.println(open2);
    Serial.println(open3);
    delay(100);

}

void setup() {

  Serial.begin(115200);
  myservo.attach(13);
  
  
  rotaryEncoder.begin();
  rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
  rotaryEncoder.setBoundaries(0, 20, true);
  myservo.write(posToe);
}

void loop() {
  rotary_loop();
  
  delay(50);                               
  if (millis()>20000) rotaryEncoder.enable ();

  if (open1 + open2 + open3 == 3){
    Serial.println("Kluis open");
    myservo.write(posOpen);
  }

}
