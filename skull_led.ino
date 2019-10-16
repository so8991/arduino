#include <Arduino.h>
#include <SD.h> //Include the library.
#include <TMRpcm.h> //Include the library.

#define LED_PIN 5
#define PIR_PIN 2
TMRpcm tmrpcm; //Creating a player object.
const int buttonPin = 2;
char filename[4][50] = {"jack0.wav", "jack1.wav", "jack2.wav", "oogie.wav"};
long rand_number;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

  tmrpcm.speakerPin = 9; //The speaker is connected to 11 Pin. You can use any PWM Pin.
  if(!SD.begin(10)) //If the card is available.
  {
    Serial.println("SD fail"); //Write in the serial port "SD fail".
    return; //Return.
  }
  else Serial.println("success");
  tmrpcm.volume(15);
}
void analogLedTurnOn(int delay_time)
{
  int value;
  for(value = 0; value <=80; value+=delay_time)
  {
    analogWrite(LED_PIN, value);
    delay(30);
  }
  
}
void analogLedTurnOff(int delay_time)
{
  int value;
  for(value = 80; value >=0; value-=delay_time)
  {
    analogWrite(LED_PIN, value);
    delay(30);
  }
  
}
int pir_value;
int current_music_index = 0;
void loop() {
  // put your main code here, to run repeatedly:
 pir_value = digitalRead(PIR_PIN);
 if(pir_value == 1 && !tmrpcm.isPlaying())
 {
  Serial.println("high");
  tmrpcm.play(filename[random(4)]);
 }
 else if(tmrpcm.isPlaying())
 {
   analogLedTurnOn(20);
   analogLedTurnOff(20);
 }
 else
 {
  Serial.println("low");
  tmrpcm.disable();
  analogLedTurnOn(1);
  analogLedTurnOff(1); 
 }
}
