#ifndef _obiecte_h_
#define _obiecte_h_

class Jucator {
private:
    int latime, inaltime;
    int hp;
    float x, y, viteza;

public:
    Jucator();
    Jucator(int latime, int inaltime, float x, float y, float viteza);

    float getX();
    float getY();
    float getViteza();
    int getLatime();
    int getInaltime();
    int getHp();
    void scadeHp(int valoare);
    bool esteViu();

    void miscareStanga();
    void miscareDreapta(int screenWidth);
};

class Proiectil {
private:
    float x,y,viteza;
    bool activ;

public:
    Proiectil();
    Proiectil(float x, float y, float viteza, bool activ);

    float getX();
    float getY();
    float getViteza();
    bool getActiv();

    void misca();
    void dezactiveaza();
};

class Inamic {
private:
    float x, y, viteza;
    int raza;
    int hp;
    bool activ;

public:
    Inamic();
    Inamic(float x, float y, float viteza, int raza, bool activ);

    float getX();
    float getY();
    float getViteza();
    int getRaza();
    bool getActiv();
    int getHp();
    void scadeHp(int valoare);
    bool esteViu();

    void misca();
    void dezactiveaza();
};
#endif