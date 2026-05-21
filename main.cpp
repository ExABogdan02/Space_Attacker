#include <iostream>
#include"obiecte.h"
#include"listaProiectile.h"
#include"raylib.h"
using namespace std;

int main() {
    const int screenWidth = 720;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Space Attacker");
    SetTargetFPS(60);

    Jucator player(70, 30, screenWidth / 2 - 35, screenHeight - 70, 6);

    int razaInamic = 20;
    Inamic inamic(GetRandomValue(razaInamic, screenWidth - razaInamic), razaInamic, 2, razaInamic, true);
    double vitezaInamic = 2.0f;

    int razaProiectil = 5;
    NodProiectil* listaProiectile = nullptr;
    double timpUltimulProiectil = 0;
    double cooldownProiectil = 0.15;

    int scor = 0;
    
    while (!WindowShouldClose()) {
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player.miscareStanga();
        }

        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player.miscareDreapta(screenWidth);
        }

        //Tragere proiectil
        if(IsKeyPressed(KEY_SPACE) && GetTime() - timpUltimulProiectil >= cooldownProiectil){
            Proiectil p(
                player.getX() + player.getLatime() / 2,
                player.getY(),
                8,
                true
            );
            adaugaProiectil(listaProiectile, p);
            timpUltimulProiectil = GetTime();
        }

        actualizeazaProiectile(listaProiectile);

        //Miscare inamic
        inamic.misca();

        if(inamic.getY() - inamic.getRaza() > screenHeight) {
            inamic = Inamic(GetRandomValue(razaInamic, screenWidth - razaInamic), -razaInamic, 2, razaInamic, true);
        }


        Rectangle playerRect = {player.getX(), player.getY(), (float)player.getLatime(), (float)player.getInaltime()};

        if(CheckCollisionCircleRec(Vector2{inamic.getX(), inamic.getY()}, inamic.getRaza(), playerRect)) {
            inamic = Inamic(GetRandomValue(razaInamic, screenWidth - razaInamic), -razaInamic, 2, razaInamic, true);
        }

        bool inamicLovit = verificaLovituraInamic(listaProiectile, inamic, razaProiectil);

        if(inamicLovit && !inamic.esteViu()) {
            scor++;
            if(scor % 3 == 0) {
                vitezaInamic = vitezaInamic + 1.0f;
            }

            inamic = Inamic(
                GetRandomValue(razaInamic, screenWidth - razaInamic),
                -razaInamic,
                vitezaInamic,
                razaInamic,
                true
            );
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Space Attacker", 20, 20, 24, RAYWHITE);
        DrawText("A / Stanga", 20, 55, 18, GRAY);
        DrawText("D / Dreapta", 20, 80, 18, GRAY);
        DrawText("Space / Trage", 20, 105, 18, GRAY);

        //Scor Mijloc Sus
        const char* textScor = TextFormat("Scor: %d", scor);
        int fontSizeScor = 25;
        int latimeTextScor = MeasureText(textScor, fontSizeScor);

        DrawText(
            textScor,
            screenWidth / 2 - latimeTextScor / 2,
            20,
            fontSizeScor,
            YELLOW
        );

        //HP Player
        DrawText(
            TextFormat("HP Player: %d", player.getHp()),
            20, 140, 20, GREEN
        );

        //HP Inamic
        DrawText(
            TextFormat("HP Player: %d", inamic.getHp()),
            screenWidth - 160,
            20, 20, RED
        );

        DrawRectangle(
            (int)player.getX(),
            (int)player.getY(),
            player.getLatime(),
            player.getInaltime(),
            BLUE
        );

        DrawCircle(
            (int)inamic.getX(),
            (int)inamic.getY(),
            inamic.getRaza(),
            RED
        );

        deseneazaProiectile(listaProiectile, razaProiectil);

        EndDrawing();
    }
    elibereazaProiectile(listaProiectile);
    CloseWindow();

    return 0;
}