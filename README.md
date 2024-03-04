
![image](https://github.com/jfs59/Music-Box/assets/34236389/703e9e96-b567-47d7-be0c-8042a5210584)

Idée: Réaliser une Music Box basée sur arduino tone() et avec mélodie interchangeable.
Les mélodies sont codées dans la zone données d'une carte RFID Mifare 1 K.

le schéma est des plus classique.

![212003fcb3375099934f585dbe29999894e53eaa](https://github.com/jfs59/Music-Box/assets/34236389/95f5f3de-4b36-423b-8c9f-9e851ba706c3)


codage de la carte RFID

les notes et leurs durées (blanche, noires etc ..) sont codés sur 2 octets.
Dans le programme les fréquences sont dans un tableau en PROGMEM on a juste donc besoin de l'indice, idem pour les durées recalculées a partir de la tempo.

la mélodie est codée par triplet 3 octets pour 2 notes et 2 durées.
Titre , Auteur, Nombre de note et tempo enregistrés sur la carte.

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

publication initiale et discussions : https://forum.arduino.cc/t/music-box-nano-rfid/1230087
