//
// Created by muhammad chambers on 11/19/24.
//

#pragma once

#include <vector>
#include "Math.h"

class Actor {
public:
    /** Used to track state of actor. */
    enum State {
        EActive,
        EPaused,
        EDead
    };

    /** Constructor. */
    Actor(class Game* game);
    /** Destructor */
    virtual ~Actor();

    /** Update function called from Game (not overridable). */
    void Update(float deltaTime);
    /** Updates all the components attached to the actor (not overridable). */
    void UpdateComponents(float deltaTime);
    /** Any actor-specific update code (overridable). */
    virtual void UpdateActor(float deltaTime);

    // Getters/Setters
    //
    //
    //

    /** Add components. */
    void AddComponent(class Component* component);
    /** Remove components. */
    void RemoveComponent(class Component* component);


private:
    /** Actor's state. */
    State mState;
    /** Transform - Center position of actor. */
    Vector2 mPosition;
    /** Uniforms scale of actor (1.0f or 100%). */
    float mScale;
    /** Rotation angle (in radians). */
    float mRotation;
    /** Components held by this actor. */
    std::vector<class Component*> mComponents;
    class Game* mGame;

};



