#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte addresses[][10] = {"ADDRESS01","ADDRESS02", "ADDRESS03"};
char message[32];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[2]);    // ADDRESS03
  radio.openReadingPipe(1, addresses[0]); // ADDRESS01
  radio.openReadingPipe(2, addresses[1]); // ADDRESS02
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
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
    size_t length = Serial.readBytesUntil('\n', message, sizeof(message));
    message[length] = '\0';  // Null-terminate the message
    
    // Trim leading whitespace
    char* trimmedMessage = message;
    while (*trimmedMessage == ' ' || *trimmedMessage == '\t') {
      trimmedMessage++;
    }
    
    // Transmit the message to other Arduinos
    radio.stopListening();
    for (int i = 0; i < 1; i++) {
      radio.openWritingPipe(addresses[i]);  // Switch writing pipe
      radio.write(trimmedMessage, strlen(trimmedMessage) + 1);
    }
    Serial.print("Sent: ");
    Serial.println(trimmedMessage);
  }
}

