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
    bool gameOver = false;
    
    while (!WindowShouldClose()) {
        if (gameOver && IsKeyPressed(KEY_R)) {
            scor = 0;
            vitezaInamic = 2.0f;
            gameOver = false;

            player = Jucator(70, 30, screenWidth / 2 - 35, screenHeight - 70, 6);

            inamic = Inamic(
                GetRandomValue(razaInamic, screenWidth - razaInamic),
                -razaInamic,
                vitezaInamic,
                razaInamic,
                true
            );
            elibereazaProiectile(listaProiectile);
        }

        if(!gameOver) {
            //Miscare player
            if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                player.miscareStanga();
            }
            if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                player.miscareDreapta(screenWidth);
            }
            //Tragere
            if(IsKeyPressed(KEY_SPACE) && GetTime() - timpUltimulProiectil >= cooldownProiectil) {
                Proiectil p(
                    player.getX() + player.getLatime() / 2,
                    player.getY(),
                    8,
                    true
                );

                adaugaProiectil(listaProiectile, p);
                timpUltimulProiectil = GetTime();
            }

            //Actualizare proiectile
            actualizeazaProiectile(listaProiectile);
            //Miscare inamic
            inamic.misca();

            //Daca inamicul trece de limita de jos al ecranului
            if(inamic.getY() - inamic.getRaza() > screenHeight) {
                player.scadeHp(1);

                if(!player.esteViu()) {
                    gameOver = true;
                } else {
                    inamic = Inamic(
                        GetRandomValue(razaInamic, screenWidth - razaInamic),
                        -razaInamic,
                        vitezaInamic,
                        razaInamic,
                        true
                    );
                }
            }

            //Hitbox player
            Rectangle playerHitbox = {
                player.getX(),
                player.getY(),
                (float)player.getLatime(),
                (float)player.getInaltime()
            };

            //Coliziune pentru player si inamic
            if(!gameOver && CheckCollisionCircleRec(
                Vector2{inamic.getX(), inamic.getY()},
                inamic.getRaza(),
                playerHitbox
            )){
                player.scadeHp(1);

                if (!player.esteViu()) {
                    gameOver = true;
                } else {
                    inamic = Inamic(
                        GetRandomValue(razaInamic, screenWidth - razaInamic),
                        -razaInamic,
                        vitezaInamic,
                        razaInamic,
                        true
                    );
                }
            }

            //Coliziune player-inamic
            if(!gameOver) {
                bool inamiclovit = verificaLovituraInamic(listaProiectile, inamic, razaProiectil);

                if(inamiclovit && !inamic.esteViu()) {
                    scor++;

                    if(scor % 3 == 0) {
                        vitezaInamic = vitezaInamic + 0.5f;
                    }

                    inamic = Inamic(
                        GetRandomValue(razaInamic, screenWidth - razaInamic),
                        -razaInamic,
                        vitezaInamic,
                        razaInamic,
                        true
                    );
                }

            }

        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Space Attacker", 200, 15, 30, RED);
        DrawText("A / Left", 20, 20, 20, GRAY);
        DrawText("D / Right", 20, 40, 20, GRAY);
        DrawText("Space / Fire", 20, 60, 20, GRAY);
        DrawText(TextFormat("Score: %d", scor), 600, 10, 25, YELLOW);
        //HP Player
        DrawText(TextFormat("HP Player: %d", player.getHp()),20, 100, 20, GREEN);



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

        if(gameOver) {
            const char* gameOverText = "GAME OVER";
            int gameOverFontSize = 60;
            int gameOverTextWidth = MeasureText(gameOverText, gameOverFontSize);

            DrawText(
                gameOverText,
                screenWidth / 2 - gameOverTextWidth / 2,
                screenHeight / 2 - 80,
                gameOverFontSize,
                RED
            );

            const char* restartText = "Press R to restart";
            int restartFontSize = 28;
            int restartTextWidth = MeasureText(restartText, restartFontSize);

            DrawText(
                restartText,
                screenWidth / 2 - restartTextWidth / 2,
                screenHeight / 2,
                restartFontSize,
                RAYWHITE
            );
        }

        EndDrawing();
    }
    elibereazaProiectile(listaProiectile);
    CloseWindow();

    return 0;
}