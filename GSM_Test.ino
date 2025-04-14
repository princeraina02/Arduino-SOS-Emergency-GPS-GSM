#include <SoftwareSerial.h>

SoftwareSerial gsm(9, 8); // RX, TX (Nano RX ← GSM TX, Nano TX → GSM RX)

String incomingData = "";
String targetWord = "hello";
String targetNumber = "+------------"; //  Replace with your number

void setup() {
  Serial.begin(9600);
  gsm.begin(38400);

  Serial.println("GSM Initialized. Type 'hello' to send SMS.");
  delay(1000);
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    incomingData += ch;

    // check if 'enter' was pressed (end of input)
    if (ch == '\n') {
      incomingData.trim(); // remove extra spaces/newlines

      if (incomingData.equalsIgnoreCase(targetWord)) {
        sendSMS(targetNumber, "Hello World");
        Serial.println("SMS Sent: Hello World");
      } else {
        Serial.println("Type 'hello' to trigger SMS.");
      }

      incomingData = ""; // reset for next input
    }
  }
}

void sendSMS(String number, String text) {
  gsm.println("AT+CMGF=1");  // Text mode
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(number);
  gsm.println("\"");
  delay(1000);

  gsm.print(text);
  gsm.write(26); // Ctrl+Z to send
  delay(3000);
}
