#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>

SoftwareSerial gpsSerial(3,4);
TinyGPSPlus gps;
File LogFile;

long latitude,longitude,alt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(gpsSerial.available()){
    if(gps.encode(gpsSerial.read())){
      latitude = gps.location.lat(); //get latitude
      longitude = gps.location.lng();
      alt = gps.altitude.meters();
    }

    LogFile = SD.open("test.txt", FILE_WRITE);

    if(LogFile){
      Serial.println("Latitude    Longitude   Altitude");
      Serial.print(latitude);
      Serial.print("    ");
      Serial.print(longitude);
      Serial.print("    ");
      Serial.println(alt);
      LogFile.close();
    }else{
      Serial.println("error opening file");
    }
  }
}
