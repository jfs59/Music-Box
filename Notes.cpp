
#include "Notes.h"
#include <avr/pgmspace.h>

uint16_t duree_Note[] = { 0, 192, 128, 96, 64, 48, 32, 24, 16, 12, 8, 6, 4, 3, 2, 1};

const uint16_t frequenceNotes[] PROGMEM =
{ 0, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131,
  139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
  523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661,
  1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978
};

const byte buzzerPin = 5;


void HP_Tone (int frequence , int duree) {
  tone(buzzerPin,  frequence, duree * 0.9);
  delay(duree);
  noTone(buzzerPin);
}

void jouer_note(int index_note,int index_duree)
{
  int frequence; int duree;
  frequence = pgm_read_word_near(frequenceNotes + index_note);
  duree = duree_Note[index_duree];
  HP_Tone (frequence , duree);
}
