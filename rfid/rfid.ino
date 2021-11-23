#include <SPI.h>
#include <MFRC522.h>
#define SDA_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SDA_PIN, RST_PIN);
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();   // آماده کردن MFRC522 
  Serial.println("کارت خود را نزدیک ماژول کنید...");
  pinMode(2,OUTPUT);
}
void loop()
{
  //بررسی کارت جدید
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // انتخاب و خواندن کارت
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //نمایش شناسه UID کارت
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C6 3E 7D 2B") //شناسه UID کارت خود را اینجا جایگزین کنید
  {
    Serial.println("کارت مورد تایید است.");
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
  }
  else
  {
    Serial.println(" کارت غیر مجاز");
    delay(1000);
  }
}
