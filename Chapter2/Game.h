//
// Created by muhammad chambers on 12/3/24.
//

#ifndef CHAPTER2_GAME_H
#define CHAPTER2_GAME_H

#include <vector>
#include "Actor.h"


class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    /** All the actors in the game. */
    std::vector<class Actor*> mActors;
    /** Any pending actors. */
    std::vector<class Actor*> mPendingActors;


};


#endif //CHAPTER2_GAME_H
