
#include "RFID.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

// Tampon lecture
byte bufferLen = 18;
unsigned char readBlockData[18];
// Contenu RFID
unsigned char Dump_rfid[752];
bool Dump_OK = false;

void initialiser_rfid () {
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF; // Preparation de la clé (usine tout a FF)
}

void lire_bloc_rfid(int bloc) {
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloc, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_Read(bloc, readBlockData, &bufferLen);
}

bool selectionner_rfid () {

  if ( ! mfrc522.PICC_IsNewCardPresent()) // Vérification nouvelle carte
  {
    Serial.println(F("Pas de nouvelle carte"));
    return false;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // sélectionner la carte
  {
    Serial.println(F("Pas de serial"));
    return false;
  }
  return true;
}

bool lire_contenu_rfid()
{
  bool result = false;
  if (selectionner_rfid ())
  {
    int plage = 0;
    for (byte secteur = 0; secteur <= 15 ; secteur++)
    {
      for (byte blockNum = secteur * 4; blockNum < (secteur * 4) + 3 ; blockNum++)
      {
        if (blockNum != 0)
        {
          lire_bloc_rfid(blockNum);
          memcpy(&Dump_rfid[plage], readBlockData, 16);// copier le secteur en memoire
          plage += 16;
        }
      }
    }
    desactiver_rfid();
    result = true;
  }
  return result;
}

void desactiver_rfid() // désactivation pour permettre nouvelle lecture
{
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// ********** Dump ***************
void dump_rfid()
{
  dump_byte_array(Dump_rfid, 752);
}
void dump_deci_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
void dump_byte_array(byte * buffer, int bufferSize) {
  for (int i = 0; i < bufferSize; i++) {
    if (i % 16 == 0) Serial.println();
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
