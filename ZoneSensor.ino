#include <Wire.h>

#define MAX 100               // max range as 100cm

void setup() {
  // put your setup code here, to run once:
 pinMode(13, OUTPUT);         // define pin #13 as output
 Wire.begin();                // join i2c bus (address optional for master)
 Serial.begin(9600);          // start serial communication at 9600bps
}

int reading = 0;

void loop() {
  // put your main code here, to run repeatedly:
  reading = readUS42V2();
  writeBuzzer(reading);
}

int readUS42V2(){
  Wire.beginTransmission(112);// start transmitting to device in address 112
  Wire.write(byte(81));       // command the sensor to take one range reading
  Wire.endTransmission();     // end transmission

  delay(70);                  // delay 70ms
  Wire.requestFrom(112, 2);   // request 2 bytes from the sensor
  if (2<=Wire.available()){   // if 2 bytes were received
    int reading = Wire.read();// receive high byte
    reading = reading << 8;   // shift high byte 8 bits left
    reading |= Wire.read();   // receive low byteas lower 8 bits
    Serial.print(reading);    // print distance value
    Serial.print("cm ");

    return reading;
  }
  
}

void writeBuzzer(int reading){
      if (reading < MAX){
        digitalWrite(13, HIGH);// turn on buzzer
      }
      else{
        digitalWrite(13, LOW);// turn off buzzer
      }
}
