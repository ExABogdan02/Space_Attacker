#ifndef _LISTA_PROIECTILE_H_
#define _LISTA_PROIECTILE_H_
#include"obiecte.h"

struct NodProiectil{
    Proiectil proiectil;
    NodProiectil* urm;
    NodProiectil(Proiectil p);
};

void adaugaProiectil(NodProiectil*& cap, Proiectil p);
void actualizeazaProiectile(NodProiectil*& cap);
void deseneazaProiectile(NodProiectil* cap, int razaProiectil);
void elibereazaProiectile(NodProiectil*& cap);
bool verificaLovituraInamic(NodProiectil*& cap, Inamic& inamic, int razaProiectil);

#endif