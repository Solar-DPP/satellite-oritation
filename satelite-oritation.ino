#include <Wire.h>
#include <LightSensor.h>

using namespace IntroSatLib;

LightSensor light1(Wire, 0x51);
LightSensor light2(Wire, 0x53);
LightSensor light3(Wire, 0x50);
LightSensor light4(Wire, 0x52);

void setup() {
  Serial.begin(115200, SERIAL_8E1); // Включения Serial для вывода данных
  Wire.begin(); // Включение Wire(I2C)
  light1.Init();
  light2.Init();
  light3.Init();
  light4.Init();
}

void loop() {

  Serial.print(light1.GetLight());
  Serial.print("\t");
  Serial.print(light2.GetLight());
  Serial.print("\t");
  Serial.print(light3.GetLight());
  Serial.print("\t");
  Serial.print(light4.GetLight());
  Serial.println();

  delay(100);
}


// (вход, установка, п, и, д, период в секундах, мин.выход, макс. выход)
int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
  float err = setpoint - input;
  static float integral = 0, prevErr = 0;
  integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr) / dt;
  prevErr = err;
  return constrain(err * kp + integral + D * kd, minOut, maxOut);
}
