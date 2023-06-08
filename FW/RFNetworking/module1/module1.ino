#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002", "00003"};
char message[32];
bool shouldEcho = true; // Flag to control echoing of received messages

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]);    // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.openReadingPipe(2, addresses[2]); // 00003
  radio.setPALevel(RF24_PA_MAX);
}

/*void loop() {
  delay(100);

  radio.startListening();
  if (radio.available()) {
    // Receive message
    radio.read(&message, sizeof(message));
    Serial.print("Received: ");
    Serial.println(message);
  }
  
  if (Serial.available()) {
    // Read message from Serial input
    size_t length = Serial.readBytesUntil('\n', message, sizeof(message) - 1);
    message[length] = '\0';  // Null-terminate the message

    // Trim leading whitespace
    char* trimmedMessage = message;
    while (*trimmedMessage == ' ' || *trimmedMessage == '\t') {
      trimmedMessage++;
    }

    // Delay before transmitting the message
    delay(100);

    // Transmit the message to other Arduinos
    radio.stopListening();
    for (int i = 0; i < 3; i++) {
      radio.openWritingPipe(addresses[i]);  // Switch writing pipe
      radio.write(trimmedMessage, strlen(trimmedMessage) + 1);
    }
    Serial.print("Sent: ");
    Serial.println(trimmedMessage);
  }
}*/


void loop() {
  delay(100);

  radio.startListening();
  if (radio.available()) {
    // Receive message
    radio.read(&message, sizeof(message));
    Serial.print("Received: ");
    Serial.println(message);

    // Echo the message to other modules if shouldEcho is true
    if (shouldEcho) {
      radio.stopListening();
      for (int i = 0; i < 3; i++) {
        radio.openWritingPipe(addresses[i]);  // Switch writing pipe
        radio.write(message, strlen(message) + 1);
      }
      shouldEcho = false; // Disable echoing to prevent looping
    }
  }

  if (Serial.available()) {
    // Read message from Serial input
    size_t length = Serial.readBytesUntil('\n', message, sizeof(message) - 1);
    message[length] = '\0';  // Null-terminate the message

    // Trim leading whitespace
    char* trimmedMessage = message;
    while (*trimmedMessage == ' ' || *trimmedMessage == '\t') {
      trimmedMessage++;
    }

    // Enable echoing for the next message
    shouldEcho = true;

    delay(100);

    // Transmit the message to other Arduinos
    radio.stopListening();
    for (int i = 0; i < 3; i++) {
      radio.openWritingPipe(addresses[i]);  // Switch writing pipe
      radio.write(trimmedMessage, strlen(trimmedMessage) + 1);
    }
    Serial.print("Sent: ");
    Serial.println(trimmedMessage);
  }
}
