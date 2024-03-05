
#include "Notes.h"

typedef struct {
  char Titre[16];
  char Auteur[16];
  uint16_t NBNotes;
  uint8_t Tempo;
  char* Suite_de_notes;
} DUMP;

typedef struct
{
  uint8_t Note_1;
  uint8_t Note_2;
  uint8_t Duree_Note_2: 4, Duree_Note_1: 4;
} DOUBLE_NOTE;

typedef struct
{
  uint8_t Note;
  uint8_t Duree;
} SIMPLE_NOTE;

const uint8_t diviseur_Tempo[] PROGMEM =
{ 0, 192, 128, 96, 64, 48, 32, 24, 16, 12, 8, 6, 4, 3, 2, 1};


extern unsigned char Dump_rfid[752];
extern uint16_t duree_Note[];
extern bool Melodie_OK;
extern const byte bouton_depart_stop_melody;
extern const byte bouton_load_melody;
extern int note_encours;

void jouer_note_en_cours();
void charger_melodie();
void jouer_melodie();
void calcul_duree_Notes(uint8_t tempo);
SIMPLE_NOTE lire_note(int note_index);
