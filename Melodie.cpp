#include "debug.h"
#include "RFID.h"
#include "Melodie.h"
#include "Notes.h"

uint8_t tempo; // Vitesse de chant
uint16_t nombre_notes;
int note_encours = 0;
boolean stop_melody;
char Titre_melody[17];
char Auteur_melody[17];
DOUBLE_NOTE* premier_triplet;
DOUBLE_NOTE* triplet_en_cours;

const byte bouton_depart_stop_melody = 6;
const byte bouton_load_melody = 7;
bool Melodie_OK = false;

void charger_melodie()
{
 D_println("Chargement melodie" );
  Melodie_OK = false;
  if (lire_contenu_rfid())
  {
    DUMP* p = (DUMP*)Dump_rfid;
    memcpy(Titre_melody, p->Titre, 16);
    memcpy(Auteur_melody, p->Auteur, 16);
    nombre_notes = p->NBNotes;
    tempo = p->Tempo;

    premier_triplet = (DOUBLE_NOTE*) & (p->Suite_de_notes);
    triplet_en_cours = premier_triplet;

    D_print(F("Auteur: ")); D_println(Titre_melody);
    D_print(F("Titre: ")); D_println(Auteur_melody);
    D_print(F("NBNotes: ")); D_println(nombre_notes);
    D_print(F("Tempo: ")); D_println(tempo);

    calcul_duree_Notes(tempo);
    Melodie_OK = true;
  }
}

void calcul_duree_Notes(uint8_t tempo) {

  long note_entiere =  (60000 * 4) / tempo;// duree note entiere en ms
  D_println(F("Durée des notes en ms"));
  for (int i = 1; i < 16; i++)
  {
    duree_Note[i] = note_entiere / 128 * pgm_read_byte(&diviseur_Tempo[i]);
    D_print(duree_Note[i]);   D_print(F(" | "));
  }
  D_println();
}

void jouer_melodie()
{
  note_encours = 0;
  D_println(F("Lecture melodie"));
  for  (int i = 0; i < nombre_notes; i++)
  {
    if (digitalRead(bouton_depart_stop_melody) == LOW)
    {
      delay(100);
      while (digitalRead(bouton_depart_stop_melody) == LOW) {}
      D_println(F("Stop melodie"));
      note_encours = 0;
      delay(2000);
      return;
    }
    jouer_note_en_cours();
    note_encours++;
  }
  note_encours = 0;
}
void jouer_note_en_cours()
{
  if ( note_encours > nombre_notes) note_encours = 0;
  SIMPLE_NOTE note ;
  note = lire_note(note_encours);
  jouer_note(note.Note, note.Duree);
}
SIMPLE_NOTE lire_note(int note_index)
{
  int saut;
  SIMPLE_NOTE result;

  triplet_en_cours = premier_triplet;
  saut = floor(note_index / (float)2 );
  triplet_en_cours += saut;
  //D_print(note_index); D_print(" "); D_println(saut);
  if (note_index & 1) {
    result.Note = triplet_en_cours->Note_2;
    result.Duree = triplet_en_cours->Duree_Note_2;
  } else {
    result.Note = triplet_en_cours->Note_1;
    result.Duree = triplet_en_cours->Duree_Note_1;
  }
  //D_print("Note:"); D_print( result.Note); D_print(", duree:"); D_println(result.Duree);
  return result;
}
