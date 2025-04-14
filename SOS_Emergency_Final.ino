#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// GSM setup: Nano RX (9) ← GSM TX, Nano TX (8) → GSM RX
SoftwareSerial gsm(9, 8); // RX, TX for GSM

// GPS setup: GPS TX → Nano RX (2), GPS RX not used
static const int GPS_RXPin = 2;
static const int GPS_TXPin = 3; // Not used, but required for SoftwareSerial
static const uint32_t GPSBaud = 9600;

// Button setup
const int buttonPin = 4; // Button connected to D4
int lastButtonState = HIGH; // For debouncing (pull-up assumed)

// Target number for SMS
String targetNumber = "+------------"; // Replace with your number

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RXPin, GPS_TXPin); // RX, TX for GPS

void setup() {
  Serial.begin(9600);
  gsm.begin(38400); // GSM baud rate
  gpsSerial.begin(GPSBaud); // GPS baud rate

  pinMode(buttonPin, INPUT_PULLUP); // Button with internal pull-up resistor

  Serial.println("GSM and GPS Initialized. Press button on D4 to send SOS.");
  delay(1000);
}

void loop() {
  // Read GPS data continuously
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Read button state
  int buttonState = digitalRead(buttonPin);

  // Check for button press (LOW when pressed due to pull-up)
  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button pressed! Preparing SOS...");

    if (gps.location.isValid()) {
      // Fetch latitude and longitude
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      // Format the SOS message with Google Maps link
      String message = "SOS EMERGENCY!\nHelp needed at:\nLat: " + String(latitude, 6) + 
                      ", Lon: " + String(longitude, 6) + 
                      "\nMap: https://www.google.com/maps?q=" + 
                      String(latitude, 6) + "," + String(longitude, 6);

      Serial.println("Sending: " + message);

      // Send SMS
      sendSMS(targetNumber, message);
      Serial.println("SOS SMS Sent!");
    } else {
      // Send fallback message if no GPS signal
      String message = "SOS EMERGENCY!\nNo GPS signal. Please help!";
      Serial.println("No GPS signal. Sending fallback: " + message);
      sendSMS(targetNumber, message);
      Serial.println("Fallback SOS SMS Sent!");
    }

    delay(200); // Simple debounce delay
  }

  lastButtonState = buttonState; // Update button state for next loop
}

void sendSMS(String number, String text) {
  gsm.println("AT+CMGF=1"); // Set SMS to text mode
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(number);
  gsm.println("\"");
  delay(1000);

  gsm.print(text);
  gsm.write(26); // Ctrl+Z to send SMS
  delay(3000);
}
