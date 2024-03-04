#ifndef INTERRUPT
#include "Interrupt.h"
#endif



// encodeur rotatif

int old_CLK;
int old_DT;
bool manivelle_Rotation;
bool manivelle_Appui;


void init_interrupt() {
  pinMode(2, INPUT_PULLUP);// resistance pas presente
  pinMode(3, INPUT); // resistance deja presente
  pinMode(4, INPUT); // resistance deja presente
  manivelle_Rotation = false;
  manivelle_Appui = false;
  attachInterrupt(digitalPinToInterrupt(3),  rotation_manivelle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2),  appui_manivelle, CHANGE);

}

void rotation_manivelle() {

  // Lecture des lignes CLK et DT
  int new_CLK = digitalRead(3);
  int new_DT  = digitalRead(4);

  // vérifier uniquement le sens horaire

  if ((new_CLK == HIGH) && (new_DT == LOW) && (old_CLK == LOW) && (old_DT == HIGH))
  {
    manivelle_Rotation = true;
  }

  // anti_rebond
  old_CLK = new_CLK;
  old_DT = new_DT;
}

void appui_manivelle() {

  int new_SW = digitalRead(2);

  if (new_SW == LOW) {
    manivelle_Appui = true;
  }

}
