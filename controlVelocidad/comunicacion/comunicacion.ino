#include <SoftwareSerial.h>
SoftwareSerial xbee_serial(11, 12);

void setup() {
  // put your setup code here, to run once:
  xbee_serial.begin(9600);
  Serial.begin(9600);
}

void loop() {
 xbee_serial.write(01);

}
