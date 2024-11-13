//
// Created by muhammad chambers on 11/13/24.
//

#include "Game.h"


Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    const char WINDOW_TITLE[] = "Game Programming in C++ (Chapter 1)";
    const int TOP_LEFT_X_COORDINATE_OF_WINDOW = 100;
    const int TOP_LEFT_Y_COORDINATE_OF_WINDOW = 100;
    const int WIDTH_OF_WINDOW = 1024;
    const int HEIGHT_OF_WINDOW = 768;
    mWindow = SDL_CreateWindow(WINDOW_TITLE, TOP_LEFT_X_COORDINATE_OF_WINDOW,TOP_LEFT_Y_COORDINATE_OF_WINDOW,
                                     WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW, 0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    // While there are still events in the queue
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            // If this is an SDL_QUIT event, end loop
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }

        // Get state of keyboard
        const Uint8* state = SDL_GetKeyboardState(NULL);
        // If escape is pressed, also end loop
        if (state[SDL_SCANCODE_ESCAPE]) {
            mIsRunning = false;
        }
    }
}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}