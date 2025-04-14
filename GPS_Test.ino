#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 2; // GPS TX connected here
static const int TXPin = 3; // Not used, but required for SoftwareSerial
static const uint32_t GPSBaud = 9600; // GPS default baud rate

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin); // RX, TX

unsigned long lastPrintTime = 0;
const unsigned long interval = 5000; // 5 seconds

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  Serial.println("GPS Logger Initialized...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - lastPrintTime >= interval) {
    lastPrintTime = millis();

    if (gps.location.isValid()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    } else {
      Serial.println("Waiting for GPS signal...");
    }
  }
}
