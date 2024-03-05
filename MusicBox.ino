#include "debug.h"

// MusicBox version 2 jfs59 2024


#define VERSION_MUSICBOX 1 // passer a 0 pour version simplifiée


#define SKETCH_VERSION "2.0.00"
#define DATE_VERSION "04/03/2024 14:00:03"
const char Version[] PROGMEM = "Version "SKETCH_VERSION" ";
const char Copy[] PROGMEM = "jfs59";
const char Annee[] PROGMEM = "2024";


#include "RFID.h"
#include "Melodie.h"
#include "Notes.h"
#include "Interrupt.h"
#include "TwiOled.h"
#include "PixOled.h"


void setup() {

  D_SerialBegin(115200);
  pinMode(buzzerPin, OUTPUT);
  pinMode(bouton_depart_stop_melody, INPUT_PULLUP);// resistance pas presente
  pinMode(bouton_load_melody, INPUT_PULLUP);// resistance pas presente

#if VERSION_MUSICBOX
  initialiser_rfid();
  init_interrupt();
  SetupTwiOled();
  SetupPixOled();
  splash();
#else
  initialiser_rfid();
#endif

}

void loop() {
  
#if VERSION_MUSICBOX
  if (digitalRead(bouton_depart_stop_melody) == LOW) {
    //Serial.println("jouer la melodie");
    delay(100);
    while (digitalRead(bouton_depart_stop_melody) == LOW) {}
    delay(100);
    jouer_melodie();
    manivelle_Rotation = false; //  supression mouvement eventuel
  }
  if (digitalRead(bouton_load_melody) == LOW) {
    //Serial.println("charger la melodie");
    delay(100);
    while (digitalRead(bouton_load_melody) == LOW) {}
    delay(100);
    manivelle_Appui = true;
  }
  // vérifier appui manivelle
  if (manivelle_Appui)
  {
    charger_melodie(); // lecture d'une nouvelle carte
    ClearBas();
    if (Melodie_OK)
    {
      afficheTitre ();
    } else {
      erreurcarte ();
      delay(2500);
      ClearBas();
      splash();
    }
    manivelle_Appui = false;
  }

  // vérifier la rotation sens horaire
  if (manivelle_Rotation) {
    manivelle_Rotation = false;
    jouer_note_en_cours();
    note_encours++;
  }
  
#else
  charger_melodie();
 if(Melodie_OK)jouer_melodie();
 #endif
}
