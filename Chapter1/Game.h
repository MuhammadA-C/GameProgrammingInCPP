//
// Created by muhammad chambers on 11/13/24.
//

#pragma once

#include <SDL.h>


struct Vector2 {
    float x;
    float y;
};

/**
 *
 */
class Game {
public:
    Game();
    /**
     * Initialize the game.
     * @return
     */
    bool Initialize();
    /**
     * Run the game loop until the game is over.
     */
    void RunLoop();
    /**
     * Shutdown the game.
     */
    void Shutdown();


private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Renderer* mRenderer;
    /** Window created by SDL. */
    SDL_Window* mWindow;
    /** Game should continue to run. */
    bool mIsRunning;
    /** Number of ticks since start of game. */
    Uint32 mTicksCount;

    /** Direction of paddle. */
    int mPaddleDirection;
    /** Position of paddle. */
    Vector2 mPaddlePosition;

    /** Position of ball. */
    Vector2 mBallPosition;
    /** Velocity of ball. */
    Vector2 mBallVelocity;
};