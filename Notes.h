#include <avr/pgmspace.h>
#include <Arduino.h>

extern const byte buzzerPin;

void HP_Tone (int frequence , int duree);
void jouer_note(int index_note,int index_duree);
