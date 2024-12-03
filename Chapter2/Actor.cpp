//
// Created by muhammad chambers on 11/19/24.
//

#include "Actor.h"
#include "Game.h"


Actor::Actor(class Game *game) :
        mState(EActive),
        mPosition(Vector2::Zero),
        mScale(1.0f),
        mRotation(0.0f),
        mGame(game) {
    mGame->AddActor(this);
}

Actor::~Actor() {
    mGame->RemoveActor(this);



}