#include <SPI.h>

#include <MFRC522.h>

 

#define SS_PIN 10

#define RST_PIN 9

#define RED 7

#define Green 6

#define Blue 5

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 

void setup(){

  pinMode(RED,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);
  digitalWrite(Blue, HIGH);
  Serial.begin(9600);   // Initiate a serial communication

  SPI.begin();      // Initiate  SPI bus

  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Approximate your card to the reader...");

  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);

   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

   digitalWrite(Green, LOW);

   digitalWrite(RED, LOW);



}

void loop(){

  // Look for new cards

  if ( ! mfrc522.PICC_IsNewCardPresent()){

    return;

  }

  // Select one of the cards

  if ( ! mfrc522.PICC_ReadCardSerial()){

    return;

  }

  //Show UID on serial monitor

  Serial.print("UID tag :");

  String content= "";

  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++){

     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

     Serial.print(mfrc522.uid.uidByte[i], HEX);

     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));

     content.concat(String(mfrc522.uid.uidByte[i], HEX));

  }

  Serial.println();

  Serial.print("Message : ");

  content.toUpperCase();

    


  //change here the UID of the card/cards that you want to give access

  if(content.substring(1) == "3A 3D F2 60"){

    Serial.println("Authorized access");

    Serial.println();

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(Blue, LOW);
    digitalWrite(Green, HIGH);

    delay(1000);

    digitalWrite(Green, LOW);
    digitalWrite(Blue, HIGH);
  }

 

 else{

  

    Serial.println(" Access denied");

     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(Blue, LOW);
    digitalWrite(RED, HIGH);

    delay(1000);

    digitalWrite(RED, LOW);
    digitalWrite(Blue, HIGH);
  

  }

} 
