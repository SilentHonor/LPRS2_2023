/*#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte address[10] = "ADDRESS01";
int i = 1;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  if(i == 0){
    const char txt[] = "Hello";
    Serial.print("Sending to receiver: ");
    //Serial.println(radio.write(txt, sizeof(txt)));
    radio.write(txt, sizeof(txt));
    radio.txStandBy(); // Add this line
    Serial.println(sizeof(txt));
    delay(1000);
  }
}*/


//########################################################

/*
// Code 3 : Bidirectional Communication (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte addresses[][10] = {"ADDRESS01","ADDRESS02"};
int i = 1;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]);    // ADDRESS01
  radio.openReadingPipe(1, addresses[1]); // ADDRESS02
  radio.setPALevel(RF24_PA_MAX);
};

void loop() {
  if(i == 0){
  delay(100);
  
  radio.stopListening();                  // Transmit
  const char txt_sent[] = "Sender 1";
  radio.write(&txt_sent, sizeof(txt_sent));  
  Serial.print("Sent to: ");Serial.println(txt_sent);
  
  delay(1000);

  radio.startListening();
  if (radio.available()) {                // Receive
    char txt_received[10] = "";
    radio.read(&txt_received, sizeof(txt_received)); 
    Serial.print("Received from: ");Serial.println(txt_received);
  };
  }
};*/


//###############################################################
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte addresses[][10] = {"ADDRESS01","ADDRESS02"};
char message[128];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]);    // ADDRESS01
  radio.openReadingPipe(1, addresses[1]); // ADDRESS02
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  delay(100);

  if (Serial.available()) {
    // Read message from Serial input
    size_t length = Serial.readBytesUntil('\n', message, sizeof(message));
    message[length] = '\0';  // Null-terminate the message
    
    // Trim leading whitespace
    char* trimmedMessage = message;
    while (*trimmedMessage == ' ' || *trimmedMessage == '\t') {
      trimmedMessage++;
    }
    
    // Transmit the message
    radio.stopListening();
    radio.write(trimmedMessage, strlen(trimmedMessage) + 1);
    Serial.print("Sent: ");
    Serial.println(trimmedMessage);
  }
  
  radio.startListening();
  if (radio.available()) {
    // Receive message
    radio.read(&message, sizeof(message));
    Serial.print("Received: ");
    Serial.println(message);
  }
}

