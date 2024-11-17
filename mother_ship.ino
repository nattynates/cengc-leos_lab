#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "SoftwareWire.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

uint16_t R;
uint16_t G;
uint16_t B;
int colour_int;

SoftwareWire colourSensorBus2(2, 3);

int DIRECTION_PIN_A = 12;
int PWM_PIN_A = 3;
int DIRECTION_PIN_B = 13;
int PWM_PIN_B = 11;

int PWM_Value = 70;

//boolean to switch direction
bool directionState;

void setup() {
  
//define pins
pinMode(DIRECTION_PIN_A, OUTPUT);
pinMode(PWM_PIN_A, OUTPUT);
pinMode(DIRECTION_PIN_B, OUTPUT);
pinMode(PWM_PIN_B, OUTPUT);

Serial.begin(9600);

if (tcs.begin()) {
  Serial.println("Found sensor");
} else {
  Serial.println("No TCS34725 found ... check your connections");
  while (1);
}
  // Now we're ready to get readings!
}

void loop() {

get_colour_sensor(&R, &G, &B);
colour_int = determine_colour(R, G, B);

if (colour_int == 2) {
  Forward(500);
}
else if (colour_int == 0) {
  Backward(500);
}


}

void get_colour_sensor(uint16_t *R, uint16_t *G, uint16_t *B) {
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC);
  Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  *R = r;
  *G = g;
  *B = b;
}

int determine_colour(uint16_t R, uint16_t G, uint16_t B) {
  // white --> 0
  // Black --> 100
  // red --> 1
  // yellow --> 2
  // blue --> 3
  // green --> 4
  
  // Black
  if (R < 3000 && G < 3000 && B < 3000) {
    return 100;
  }
  // White
  else if (R > 48000 && G > 48000 && B > 48000) {
    return 0;
  }
  // yellow
  else if (R > 35000 && G > 29000 && B > 17000 ) {
    return 2;
  }
  // red
  else if (R > 18000 && G > 6000 && B > 6000 ) {
    return 1;
  }
  // blue
  else if (R > 2000 && G > 3000 && B > 5000 ) {
    return 3;
  }
  // green
  else if (R > 2000 && G > 3000 && B > 5000 ) {
    return 3;
  }
  // otherwise return white
  return 0;
}

void Forward(long duration) {
  digitalWrite(DIRECTION_PIN_A, HIGH);
  digitalWrite(DIRECTION_PIN_B, LOW);

  //set work duty for the motor
  analogWrite(PWM_PIN_A, PWM_Value);
  analogWrite(PWM_PIN_B, PWM_Value);

  delay(duration);

  //set work duty for the motor to 0 (off)
  analogWrite(PWM_PIN_A, 0);
  analogWrite(PWM_PIN_B, 0);

  delay(duration);
}
void Backward(long duration) {

  digitalWrite(DIRECTION_PIN_A, LOW);
  digitalWrite(DIRECTION_PIN_B, HIGH);

  //set work duty for the motor
  analogWrite(PWM_PIN_A, PWM_Value);
  analogWrite(PWM_PIN_B, PWM_Value);

  delay(duration);

  //set work duty for the motor to 0 (off)
  analogWrite(PWM_PIN_A, 0);
  analogWrite(PWM_PIN_B, 0);

  delay(duration);
}
void TurnRight(long duration) {
  digitalWrite(DIRECTION_PIN_A, HIGH);
  digitalWrite(DIRECTION_PIN_B, HIGH);

  //set work duty for the motor
  analogWrite(PWM_PIN_A, PWM_Value);
  analogWrite(PWM_PIN_B, PWM_Value);

  delay(duration);

  //set work duty for the motor to 0 (off)
  analogWrite(PWM_PIN_A, 0);
  analogWrite(PWM_PIN_B, 0);
}

void TurnLeft(long duration) {
  digitalWrite(DIRECTION_PIN_A, LOW);
  digitalWrite(DIRECTION_PIN_B, LOW);

  //set work duty for the motor
  analogWrite(PWM_PIN_A, PWM_Value);
  analogWrite(PWM_PIN_B, PWM_Value);

  delay(duration);

  //set work duty for the motor to 0 (off)
  analogWrite(PWM_PIN_A, 0);
  analogWrite(PWM_PIN_B, 0);
}