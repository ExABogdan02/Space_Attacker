#include"listaProiectile.h"
#include"raylib.h"

NodProiectil::NodProiectil(Proiectil p) : proiectil(p), urm(nullptr) {}

void adaugaProiectil(NodProiectil*& cap, Proiectil p) {
    NodProiectil* nou = new NodProiectil(p);

    if(cap == nullptr) {
        cap = nou;
    } else {
        NodProiectil* curent = cap;
        
        while(curent->urm != nullptr) {
            curent = curent->urm;
        }
        curent->urm = nou;
    }
}

void actualizeazaProiectile(NodProiectil*& cap){
    NodProiectil* curent = cap;
    NodProiectil* anterior = nullptr;

    while(curent != nullptr){
        curent->proiectil.misca();

        if (curent->proiectil.getY() < 0){
            NodProiectil* deSters = curent;

            if(anterior == nullptr){
                cap = curent->urm;
                curent = cap;
            } else{
                anterior->urm = curent->urm;
                curent = curent->urm;
            }

            delete deSters;
        } else{
            anterior = curent;
            curent = curent->urm;
        }
    }
}

void deseneazaProiectile(NodProiectil* cap, int razaProiectil) {
    NodProiectil* curent = cap;

    while(curent != nullptr){
        DrawCircle((int)curent->proiectil.getX(), (int)curent->proiectil.getY(), razaProiectil, YELLOW);

        curent = curent->urm;
    }
}

void elibereazaProiectile(NodProiectil*& cap){
    while(cap != nullptr){
        NodProiectil* deSters = cap;
        cap = cap->urm;
        delete deSters;
    }
}

bool verificaLovituraInamic(NodProiectil*& cap, Inamic& inamic, int razaProiectil) {
    NodProiectil* curent = cap;
    NodProiectil* anterior = nullptr;

    while(curent != nullptr) {
        bool lovit = CheckCollisionCircles(
            Vector2{curent->proiectil.getX(), curent->proiectil.getY() },
            razaProiectil,
            Vector2{inamic.getX(), inamic.getY()},
            inamic.getRaza()
        );

        if(lovit){
            inamic.scadeHp(1);
            NodProiectil* deSters = curent;

            if(anterior == nullptr){
                cap = curent->urm;
                curent = cap;
            } else {
                anterior->urm = curent->urm;
                curent = curent->urm;
            }
            delete deSters;
            return true;
        }
        anterior = curent;
        curent = curent->urm;
    }
    return false;
}