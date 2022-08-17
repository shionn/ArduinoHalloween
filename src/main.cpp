#include <Arduino.h>
#include <SoftwareSerial.h>
#include <RedMP3.h>

#define MP3_RX 7 //RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8 //TX to D8, note that D8 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO

#define ECHO_PIN 3
#define TRIGGER_PIN 2
#define MEASURE_TIMEOUT 25000UL

MP3 mp3(MP3_RX, MP3_TX);
long previous = 0;
void setup()
{
  delay(500); //Requires 500ms to wait for the MP3 module to initialize

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

uint8_t track = 1;

void loop()
{

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  if (measure < (previous - 2000))
  {
    Serial.println(track);
    mp3.playWithVolume(track, 0x1a);
    delay(7000);
    track++;
    if (track == 8)
    {
      track = 1;
    }
  }
  else
  {
    Serial.print(measure);
    Serial.print(" ");
    Serial.print(previous - 2000);
    Serial.println();
  }
  previous = measure;

  // put your main code here, to run repeatedly:
}