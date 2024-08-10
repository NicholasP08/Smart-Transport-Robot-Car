//Nicholas_Pillay_Code_for_RFID_Control_Motor

//Inclcude Libraries
#include <SPI.h>                                                              //Allows to communicate to SPI (Serial Peripheral Interface) (The RFID Reader)
#include <MFRC522.h>                                                          //Allows to Read/Write a RFID Card
#include <Servo.h>                                                            //Allows to control servo motor

//Defines Pins
#define SS_PIN 10                                                             //Define RFID SDA Pin (Serial Input (SS) for SPI communication)
#define RST_PIN 9                                                             //Define RFID RST Pin (Reset pin (Used to reset or power down the module))
#define LED_G 5                                                               //Define Green LED Pin
#define LED_R 4                                                               //Define Red LED Pin
#define BUZZER 2                                                              //Define Buzzer pin

//Define Names
MFRC522 mfrc522(SS_PIN, RST_PIN);                                             //Create MFRC522 instance (Object to be used in code)
Servo myServo;                                                                //Define servo name
 
void setup() 
{
  Serial.begin(9600);                                                         //Starts the Serial Communication
  SPI.begin();                                                                //Initiates the SPI bus
  mfrc522.PCD_Init();                                                         //Initiates the MFRC522 (RFID Reader)
  myServo.attach(3);                                                          //Defines the Servo Pin
  myServo.write(0);                                                           //Adjusts the Servo to the start position
  pinMode(LED_G, OUTPUT);                                                     //Sets the Green LED as an Output
  pinMode(LED_R, OUTPUT);                                                     //Sets the Red LED as an Output
  pinMode(BUZZER, OUTPUT);                                                    //Sets the Buzzer as an Output
  noTone(BUZZER);                                                             //Stops any tone from the buzzer
  Serial.println("Please place your card on the reader");
  Serial.println();

}
void loop() 
{
  //Search for RFID Tags
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  //Read the RFID Tag
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Print the UID on the serial monitor
  Serial.print("UID tag : ");
  String content="";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)                                  //For each byte of the UID
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();                                                       //Get an upper-case version of the String
  if (content.substring(1) == "23 32 1A 0F")                                   //Enter the correct UID of the card/cards you want to give access to
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    Serial.println();
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}