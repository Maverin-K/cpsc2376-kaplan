#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Game.h"
#include "Engine.h"
#include "main.h"

void drawWinScreen(Game& game, Engine& engine) {
    auto status = game.getStatus();
    std::string msg;
    SDL_Color bgColor;
    SDL_Color textColor;
    if (status == Game::X_WON) {
        msg = "X WON IN " + std::to_string(game.moveCount()) + " MOVES!!!";
        bgColor = {0, 0, 0, 200};
        textColor = {255, 255, 255, 255};
    } else if (status == Game::O_WON) {
        msg = "O WON IN " + std::to_string(game.moveCount()) + " MOVES!!!";
        bgColor = {255, 255, 255, 200};
        textColor = {0, 0, 0, 255};
    } else {
        msg = "DRAW";
        bgColor = {128, 128, 128, 200};
        textColor = {255, 255, 255, 255};
    }
    engine.drawRectangle(350, 350, 700, 700, bgColor);
    engine.drawText(msg, 350, 350, textColor);
    engine.drawText("Press space to play again.", 350, 650, textColor);
}

int main() {
    Engine engine;
    Game game;
    bool running = true;
    SDL_Event event;

    int row = 0, col = 0;
    int cursorRow = 0, cursorCol = 0;

    bool animating = false;
    float animY = 0;
    int animTargetRow = -1;
    int animCol = -1;
    Game::Cell animToken = Game::BLANK;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
                else if (event.key.keysym.sym == SDLK_SPACE && game.getStatus() != Game::ONGOING)
                    game = Game();
                else if (event.key.keysym.sym == SDLK_UP && cursorRow > 0) cursorRow--;
                else if (event.key.keysym.sym == SDLK_DOWN && cursorRow < 6) cursorRow++;
                else if (event.key.keysym.sym == SDLK_LEFT && cursorCol > 0) cursorCol--;
                else if (event.key.keysym.sym == SDLK_RIGHT && cursorCol < 6) cursorCol++;
                else if ((event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) && game.getStatus() == Game::ONGOING) {
                    if (game.play(cursorRow, cursorCol)) {
                        engine.playSound();
                        animating = true;
                        animY = -100;
                        animTargetRow = cursorRow;
                        animCol = cursorCol;
                        animToken = game.getCurrentToken() == Game::X ? Game::O : Game::X;
                    }
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                col = event.motion.x / 100;
                row = event.motion.y / 100;
                cursorRow = row;
                cursorCol = col;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && game.getStatus() == Game::ONGOING) {
                int clickCol = event.button.x / 100;
                int clickRow = event.button.y / 100;
                cursorRow = clickRow;
                cursorCol = clickCol;
                if (game.play(clickRow, clickCol)) {
                    engine.playSound();
                    animating = true;
                    animY = -100;
                    animTargetRow = clickRow;
                    animCol = clickCol;
                    animToken = game.getCurrentToken() == Game::X ? Game::O : Game::X;
                }
            }
        }

        engine.clear();
        game.draw(&engine, cursorRow, cursorCol);

        if (animating) {
            animY += 20;
            if (animY >= animTargetRow * 100 + 50) animating = false;
            else {
                engine.drawCircle(animCol * 100 + 50, (int)animY, 30,
                    animToken == Game::X ? SDL_Color{0,0,0,255} : SDL_Color{255,255,255,255});
            }
        }

        if (game.getStatus() != Game::ONGOING)
            drawWinScreen(game, engine);

        engine.flip();
    }

    return 0;
}
