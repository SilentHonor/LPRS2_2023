
// Code 1 : Sending Text (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

/*#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte address[10] = "ADDRESS01";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  //radio.setPALevel(RF24_PA_MIN);
  //radio.setPALevel(RF24_PA_HIGH);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
};

void loop() {
  //Serial.println("Receiving from transmitter: ");
  if (radio.available()) {
    char txt[12] = "";
    //Serial.print("Receiving from transmitter: ");
    radio.read(&txt, sizeof(txt));
    Serial.println(txt);
    delay(1000);
  };
};*/


//###############################################################

// Code 3 : Bidirectional Communication (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)
/*
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte addresses[][10] = {"ADDRESS01","ADDRESS02"};
int i = 1;

void setup() {
  Serial.begin(9600);  
  radio.begin();  
  radio.openWritingPipe(addresses[1]);    // ADDRESS02
  radio.openReadingPipe(1, addresses[0]); // ADDRESS01
  radio.setPALevel(RF24_PA_MAX);
};

void loop() {  
  if(i == 0){
  delay(100);

  radio.startListening();
  if (radio.available()) {                // Receive
    //char txt_received[10] = "";
    //char txt_received[20] = "";
    char txt_received[9] = "";
    radio.read(&txt_received, sizeof(txt_received)); 
    Serial.print("Received from: ");Serial.println(txt_received);
  };
  
  delay(1000);
  
  radio.stopListening();                  // Transmit
  const char txt_sent[] = "Sender 2";
  radio.write(&txt_sent, sizeof(txt_sent));  
  Serial.print("Sent to: ");Serial.println(txt_sent);
  }
};*/

//###############################################################
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte addresses[][10] = {"ADDRESS01","ADDRESS02"};
char message[128];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]);    // ADDRESS02
  radio.openReadingPipe(1, addresses[0]); // ADDRESS01
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
    
    // Transmit the message
    radio.stopListening();
    radio.write(trimmedMessage, strlen(trimmedMessage) + 1);
    Serial.print("Sent: ");
    Serial.println(trimmedMessage);
  }
}



