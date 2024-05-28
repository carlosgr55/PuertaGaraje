/*
  Codigo para abrir la puerta 

*/
#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>  // incluye libreria especifica para MFRC522
#include <Servo.h>


#define RST_PIN 9  // constante para referenciar pin de reset
#define SS_PIN 10  // constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN);  // crea objeto mfrc522 enviando pines de slave select y reset

Servo motor;

byte LecturaUID[4];                            // crea array para almacenar el UID leido
byte tarjeta[4] = { 0xC3, 0x23, 0x50, 0x40 };  // UID de tarjeta leido en programa 1
byte llavero[4] = { 0xA9, 0x57, 0x51, 0xC2 };

void setup() {
  // put your setup code here, to run once:
  motor.attach(3);
  Serial.begin(9600);  // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();         // inicializa bus SPI
  mfrc522.PCD_Init();  // inicializa modulo lector
  Serial.println("Listo");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mfrc522.PICC_IsNewCardPresent())  // si no hay una tarjeta presente
    return;                              // retorna al loop esperando por una tarjeta

  if (!mfrc522.PICC_ReadCardSerial())  // si no puede obtener datos de la tarjeta
    return;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    LecturaUID[i] = mfrc522.uid.uidByte[i];
  }

  if (acceso(LecturaUID, tarjeta) || acceso(LecturaUID, llavero)) {
    Serial.println("Abriendo puerta\n");
    AbrirPuerta();
    delay(2000);
    Serial.println("Cerrando puerta");
    CerrarPuerta();
  }
}


boolean acceso(byte lectura[], byte usuario[]) {

  for (byte i = 0; i < mfrc522.uid.size; i++) {  // bucle recorre de a un byte por vez el UID
    if (lectura[i] != usuario[i])                // si byte de UID leido es distinto a usuario
      return (false);                            // retorna falso
  }
  return (true);
}


void AbrirPuerta() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  motor.write(130);
  delay(500);
  motor.write(120);
  delay(500);
  motor.write(110);
  delay(500);
  motor.write(100);
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(80);
  delay(500);
  motor.write(70);
  delay(500);
  motor.write(60);
  delay(500);
  motor.write(50);
  delay(500);
  motor.write(40);
  delay(500);
  motor.write(30);
  delay(500);
  motor.write(20);
  delay(500);
  motor.write(10);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}



void CerrarPuerta() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  motor.write(9);
  delay(500);
  motor.write(20);
  delay(500);
  motor.write(30);
  delay(500);
  motor.write(40);
  delay(500);
  motor.write(50);
  delay(500);
  motor.write(60);
  delay(500);
  motor.write(70);
  delay(500);
  motor.write(80);
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(100);
  delay(500);
  motor.write(110);
  delay(500);
  motor.write(120);
  delay(500);
  motor.write(130);
  delay(500);

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(5000);
}
