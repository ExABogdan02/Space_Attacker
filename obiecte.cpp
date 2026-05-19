#include"obiecte.h"

Jucator::Jucator(int latime, int inaltime, float x, float y, float viteza) {
    this->latime = latime;
    this->inaltime = inaltime;
    this->x = x;
    this->y = y;
    this->viteza = viteza;
}

Proiectil::Proiectil(float x, float y, float viteza, bool activ) {
    this->x = x;
    this->y = y;
    this->viteza = viteza;
    this->activ = activ;
}

Inamic::Inamic(float x, float y, float viteza, int raza, bool activ) {
    this->x = x;
    this->y = y;
    this->viteza = viteza;
    this->raza = raza;
    this->activ = activ;
}


// Get pentru jucator.

float Jucator::getX() {
    return x;
}
float Jucator::getY() {
    return y;
}
float Jucator::getViteza(){
    return viteza;
}
int Jucator::getLatime() {
    return latime;
}
int Jucator::getInaltime() {
    return inaltime;
}

// Get pentru proiectil.

float Proiectil::getX() {
    return x;
}
float Proiectil::getY() {
    return y;
}
float Proiectil::getViteza() {
    return viteza;
}
bool Proiectil::getActiv() {
    return activ;
}

// Get pentru inamici.

float Inamic::getX() {
    return x;
}
float Inamic::getY() {
    return y;
}
float Inamic::getViteza() {
    return viteza;
}
int Inamic::getRaza() {
    return raza;
}
bool Inamic::getActiv() {
    return activ;
}


void Jucator::miscareStanga() {
    if(x - viteza >=0) {
        x = x - viteza;
    }
}
    

void Jucator::miscareDreapta(int screenWidth) {
    if(x + latime + viteza <= screenWidth) {
        x = x + viteza;
    }
}


void Proiectil::misca() {
    y = y - viteza;
}
void Proiectil::dezactiveaza() {
    activ = false;
}


void Inamic::misca() {
    y = y + viteza;
}
void Inamic::dezactiveaza() {
    activ = false;
}
