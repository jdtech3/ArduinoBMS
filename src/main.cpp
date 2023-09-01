#include "BQ76952.h"

#define ALERT_PIN 10

BQ76952 bms;

void setup() {
  Serial.begin(115200);

  Serial.println("ArduinoBMS up!");

  bms.begin();
  bms.check_connection();


  // Wire.begin();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3E);
  // Wire.write(0x9A);
  // Wire.endTransmission();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3F);
  // Wire.write(0x00);
  // Wire.endTransmission();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x64);
  // Wire.endTransmission();

  // byte buf[2];
  // Wire.requestFrom(0x08, 2);
  // Wire.readBytes(buf, 2);

  // char out_buf[16];
  // sprintf(out_buf, "%02x %02x\n", buf[1], buf[0]);
  // Serial.println(out_buf);

  // ###

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3E);
  // Wire.write(0x96);
  // Wire.endTransmission();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3F);
  // Wire.write(0x00);
  // Wire.endTransmission();

  // ###

  // for (int i = 0; i < 10; i++) {
  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3E);
  //   Wire.endTransmission();

  //   Wire.requestFrom(0x08, 1);
  //   Wire.readBytes(buf, 1);

  //   sprintf(out_buf, "%02x\n", buf[0]);
  //   Serial.println(out_buf);

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3F);
  //   Wire.endTransmission();

  //   Wire.requestFrom(0x08, 1);
  //   Wire.readBytes(buf, 1);

  //   sprintf(out_buf, "%02x\n", buf[0]);
  //   Serial.println(out_buf);

  //   delay(1);
  // }

  // Wire.beginTransmission(0x08);
  // Wire.write(0x64);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 2);
  // Wire.readBytes(buf, 2);

  // sprintf(out_buf, "%02x %02x\n", buf[1], buf[0]);
  // Serial.println(out_buf);

  // delay(1);

  // Wire.beginTransmission(0x08);
  // Wire.write(0x7F);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 1);


  // while (1) {

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3E);
  //   Wire.write(0x96);
  //   Wire.endTransmission();

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3F);
  //   Wire.write(0x00);
  //   Wire.endTransmission();

  //   Serial.println("FET ON");

  //   delay(5000);

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3E);
  //   Wire.write(0x95);
  //   Wire.endTransmission();

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3F);
  //   Wire.write(0x00);
  //   Wire.endTransmission();

  //   Serial.println("FET OFF");

  //   delay(5000);

  // }

  // delayMicroseconds(300);

  // Wire.beginTransmission(0x08);
  // Wire.write(0x12);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 2);
  // int a = Wire.read();
  // int b = Wire.read();


  // Wire.beginTransmission(0x08);
  // Wire.write(0x3E);
  // Wire.write(0x9A);
  // Wire.endTransmission();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3F);
  // Wire.write(0x00);
  // Wire.endTransmission();


  // Wire.beginTransmission(0x08);
  // Wire.write(0x12);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 2);
  // int c = Wire.read();
  // int d = Wire.read();

  // Serial.println(b, HEX);
  // Serial.println(a, HEX);

  // Serial.println(d, HEX);
  // Serial.println(c, HEX);

  // int a, b;
  // a = Wire.read();
  // b = Wire.read();

  // Serial.println(a, HEX);

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3E);
  // Wire.write(0x08);
  // Wire.endTransmission();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x3F);
  // Wire.write(0x93);
  // Wire.endTransmission();

  // delay(1);

  // Wire.beginTransmission(0x08);
  // Wire.write(0x40);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 1);
  // int a, b;
  // a = Wire.read();

  // Wire.beginTransmission(0x08);
  // Wire.write(0x41);
  // Wire.endTransmission();

  // Wire.requestFrom(0x08, 1);
  // b = Wire.read();

  // Serial.println(a, HEX);
  // Serial.println(b, HEX);

  // for (int i = 0; i < 5; i++) {

  //   Wire.beginTransmission(0x08);
  //   Wire.write(0x3E);
  //   Wire.endTransmission();

  //   Wire.requestFrom(0x08, 2);
  //   int a, b;
  //   a = Wire.read();
  //   b = Wire.read();

  //   delay(1);

  // }

  // bms.setDebug(true);
  // Serial.begin(115200);
  // bms.begin();
  // bms.reset();
  // bq76952_protection_t status = bms.getProtectionStatus();
  // Serial.println("after prot");
  // bq76952_temperature_t tStat = bms.getTemperatureStatus();
  // Serial.println("after temp");
  // Serial.println(status.bits.SC_DCHG);
  // Serial.println(tStat.bits.OVERTEMP_FET);
  // float temp = bms.getInternalTemp();
  // Serial.println(temp);

  // bms.setCellOvervoltageProtection(4150, 1000);
  // bms.setCellUndervoltageProtection(2880, 1000);
  // bms.setChargingOvercurrentProtection(50, 10);
  // bms.setDischargingOvercurrentProtection(70, 15);
  // bms.setDischargingShortcircuitProtection(SCD_40, 100);
  // Serial.println(bms.isConnected());

  // Serial.println(bms.isCharging());
  // Serial.println(bms.isDischarging());
}

void loop() {

  // put your main code here, to run repeatedly:
  // Serial.println("FET on!");
  // bms.setFET(ALL, ON);
  // delay(3000);
  // Serial.println("FET off!");
  // bms.setFET(ALL, OFF);
  // delay(3000);

  // float temp = bms.getInternalTemp();
  // Serial.println(temp);
}
