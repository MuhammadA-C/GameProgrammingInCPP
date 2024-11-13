//
// Created by muhammad chambers on 11/13/24.
//

#ifndef CHAPTER1_GAME_H
#define CHAPTER1_GAME_H

#include <SDL.h>


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

    /** Window created by SDL. */
    SDL_Window* mWindow;
    /** Game should continue to run. */
    bool mIsRunning;
};


#endif //CHAPTER1_GAME_H