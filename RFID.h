
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10
extern MFRC522 mfrc522;

extern bool Dump_OK;
void initialiser_rfid();
bool selectionner_rfid();
void desactiver_rfid();
void lire_bloc_rfid(int bloc);
bool lire_contenu_rfid ();
void dump_rfid();
void dump_byte_array(byte *buffer, int bufferSize);
void dump_deci_byte_array(byte *buffer, byte bufferSize);
