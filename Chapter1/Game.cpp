//
// Created by muhammad chambers on 11/13/24.
//

#include "Game.h"


const int THICKNESS = 15;
const float PADDLE_HEIGHT = 100.0f;


Game::Game()
: mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0) {

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

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mPaddlePosition.x = 10.0f;
    mPaddlePosition.y = 768.0f / 2.0f;
    mBallPosition.x = 1024.0f / 2.0f;
    mBallPosition.y = 768.0f / 2.0f;

    return true;
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
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
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();

    // TODO: Update objects in game world as function of delta time!
    // ...

}

void Game::GenerateOutput() {

    // Set draw color to blue
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);


    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Draw top wall
    SDL_Rect wall {
        0,
        0,
        1024,
        THICKNESS};
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw bottom wall
    wall.y = 768 - THICKNESS;
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw right wall
    wall.x = 1024 - THICKNESS;
    wall.y = 0;
    wall.w = THICKNESS;
    wall.h = 1024;
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw paddle
    SDL_Rect paddle {
            static_cast<int>(mBallPosition.x),
            static_cast<int>(mBallPosition.y - PADDLE_HEIGHT / 2),
            THICKNESS,
            static_cast<int>(PADDLE_HEIGHT)
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    // Draw ball
    SDL_Rect ball {
        static_cast<int>(mBallPosition.x - THICKNESS / 2),
        static_cast<int>(mBallPosition.y - THICKNESS / 2),
        THICKNESS,
        THICKNESS
    };
    SDL_RenderFillRect(mRenderer, &ball);


    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}