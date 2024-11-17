#include <Wire.h>
#include "Adafruit_TCS34725.h"

uint16_t r, g, b, c, colorTemp, lux = 0;
uint16_t rL, gL, bL = 0;
uint16_t rR, gR, bR = 0;
uint16_t rM, gM, bM = 0;
int sensorLeft = 7;
int sensorRight = 8;
int sensorMid = 9;
int CS_DELAY = 250;
void setup(void) {
  Serial.begin(9600);
  init_sensor_pins();
}
void init_sensor_pins(void) {
  pinMode(sensorLeft, OUTPUT);
  pinMode(sensorRight, OUTPUT);
  pinMode(sensorMid, OUTPUT);
}
void loop(void) {
  read_3_colour_sensors();
}
void read_3_colour_sensors(void) {
  for(int i = 0; i < 3; i++){
    sensorON(sensorRight);
    delay(2*CS_DELAY);
  }
  // Save last reading
  rR = r;
  gR = g;
  bR = b;
  digitalWrite(sensorRight, LOW);
  delay(CS_DELAY);
  for(int j = 0; j < 3; j++){
    sensorON(sensorLeft);
    delay(2*CS_DELAY);
  }
  // Save last reading
  rL = r;
  gL = g;
  bL = b;
  digitalWrite(sensorLeft, LOW);
  delay(CS_DELAY);
  for(int k = 0; k < 3; k++){
    sensorON(sensorMid);
    delay(2*CS_DELAY);
  }
  // Save last reading
  rM = r;
  gM = g;
  bM = b;
  digitalWrite(sensorMid, LOW);
  delay(CS_DELAY);
}

void sensorON(int pin){  
  // Must reinit so that when power is turned back on it is OK
  digitalWrite(pin, HIGH);
  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X); 
  delay(3*CS_DELAY);
  
  tcs.getRawData(&r, &g, &b, &c);
  Serial.println("TEST2");
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  // display data
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
}
