#include<SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

String incomingByte = "";   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
    
}

void loop() {
        
        // send data only when you receive data:
        
        
        if (Serial.available() > 0) {       
                incomingByte = Serial.readString();
               
        }
 
        Serial.println(incomingByte);
        
        incomingByte = "";
}
