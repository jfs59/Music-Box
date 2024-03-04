#ifndef INTERRUPT
#define INTERRUPT
#endif
#include <Arduino.h>

extern bool manivelle_Rotation;
extern bool manivelle_Appui;

void init_interrupt();
void rotation_manivelle();
void appui_manivelle();
