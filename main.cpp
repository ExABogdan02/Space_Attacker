#include <iostream>
#include"obiecte.h"
#include"listaProiectile.h"
#include"raylib.h"
using namespace std;

int main() {
    const int screenWidth = 1090;
    const int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "Space Attacker");
    SetTargetFPS(60);

    Jucator player(70, 30, screenWidth / 2 - 35, screenHeight - 70, 6);

    int razaInamic = 20;
    Inamic inamic(GetRandomValue(razaInamic, screenWidth - razaInamic), razaInamic, 2, razaInamic, true);

    int razaProiectil = 5;
    NodProiectil* listaProiectile = nullptr;

    
    while (!WindowShouldClose()) {
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player.miscareStanga();
        }

        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player.miscareDreapta(screenWidth);
        }

        //Tragere proiectil
        if(IsKeyPressed(KEY_SPACE)){
            Proiectil p(
                player.getX() + player.getLatime() / 2,
                player.getY(),
                8,
                true
            );
            adaugaProiectil(listaProiectile, p);
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



        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Space Attacker", 20, 20, 24, RAYWHITE);
        DrawText("A / Stanga", 20, 55, 18, GRAY);
        DrawText("D / Dreapta", 20, 80, 18, GRAY);
        DrawText("Space / Trage", 20, 105, 18, GRAY);

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