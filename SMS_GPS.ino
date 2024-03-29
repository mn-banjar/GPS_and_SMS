#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5; //reversed should be Rx to 5
static const uint32_t GPSBaud = 9600;
float Latitude;
float Longitude;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial mySerial(9, 10);


void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println("started!");

  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Latitude = gps.location.lat();
      Longitude = gps.location.lng();
      Serial.print("Latitude= "); 
      Serial.print(Latitude, 8);
      Serial.print(" Longitude= "); 
      Serial.println(Longitude, 8);

      delay(300);
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+9665xxxxxxxx\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.print("https://www.google.com/maps/?q=");
      mySerial.print(Latitude, 8);
      mySerial.print(",");
      mySerial.println(Longitude, 8);// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
  }
  
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
}
