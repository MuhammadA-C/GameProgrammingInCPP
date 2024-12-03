//
// Created by muhammad chambers on 12/3/24.
//

#include "Game.h"
#include "Actor.h"


void Game::AddActor(class Actor *actor) {
    // If updating actors, need to add to pending
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(class Actor *actor) {

}

void Game::UpdateGame() {
    float deltaTime;

    // Update all actors
    mUpdatingActors = true;
    for (auto&  actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    // Move any pending actors to mActors
    for (auto& pending : mPendingActors) {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for (auto& actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    // Delete dead actors (which removes them from mActors
    for (auto& actor : deadActors) {
        delete actor;
    }
}

void Game::UnloadData() {

    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!mActors.empty()) {
        delete mActors.back();
    }
}