//
// Created by muhammad chambers on 11/13/24.
//

#include "Game.h"


const int THICKNESS = 15;
const float PADDLE_HEIGHT = 100.0f;


Game::Game()
: mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0), mPaddleDirection(0) {

}

bool Game::Initialize() {
    // Initialize SDL
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
    mBallVelocity.x = -200.0f;
    mBallVelocity.y = 235.0f;

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

        // Update paddle direction based on W/S keys
        mPaddleDirection = 0;
        if (state[SDL_SCANCODE_W]) {
            mPaddleDirection -= 1;
        }
        if (state[SDL_SCANCODE_S]) {
            mPaddleDirection += 1;
        }
    }
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
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

    // Update paddle position based on direction
    if (mPaddleDirection != 0) {
        mPaddlePosition.y += mPaddleDirection * 300.0f * deltaTime;

        // Make sure paddle doesn't move off-screen
        if (mPaddlePosition.y < (PADDLE_HEIGHT / 2.0f + THICKNESS)){
            mPaddlePosition.y = PADDLE_HEIGHT / 2.0f + THICKNESS;
        } else if (mPaddlePosition.y > (768.0f - PADDLE_HEIGHT / 2.0f - THICKNESS)) {
            mPaddlePosition.y = 768.0f - PADDLE_HEIGHT / 2.0f - THICKNESS;
        }
    }

    // Update ball position based on ball velocity
    mBallPosition.x += mBallVelocity.x * deltaTime;
    mBallPosition.y += mBallVelocity.y * deltaTime;

    // Bounce if needed
    // Did we interest with the paddle
    float difference = mPaddlePosition.y - mBallPosition.y;
    difference = (difference > 0.0f) ? difference : -difference;
    if (
            // Our y-difference is small enough
            difference <= PADDLE_HEIGHT / 2.0f &&
            // We are in the correct x-position
            mBallPosition.x <= 25.0f && mBallPosition.x >= 20.0f &&
            // The ball is moving to the left
            mBallVelocity.x < 0.0f) {
        mBallVelocity.x *= -1.0f;
    }
    // Did the ball go off the screen? (if so, end game)
    else if (mBallPosition.x <= 0.0f) {
        mIsRunning = false;
    }
    // Did the ball collide with the right wall
    else if (mBallPosition.x >= (1024.0f - THICKNESS) && mBallVelocity.x > 0.0f) {
        mBallVelocity.x *= 1.0f;
    }

    // Did the ball collide with the top wall
    if (mBallPosition.y <= THICKNESS && mBallVelocity.y < 0.0f) {
        mBallVelocity.y *= -1;
    }
    // Did the ball collide with the bottom wall
    else if (mBallPosition.y >= (768 - THICKNESS) && mBallVelocity.y > 0.0f) {
        mBallVelocity.y *= -1;
    }
}

void Game::GenerateOutput() {
    // Set draw color to blue
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    // Draw walls
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
            static_cast<int>(mPaddlePosition.x),
            static_cast<int>(mPaddlePosition.y - PADDLE_HEIGHT / 2),
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