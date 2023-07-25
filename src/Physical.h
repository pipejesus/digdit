//
// Created by pimu on 01.07.23.
//

#ifndef DIGDIT_PHYSICAL_H
#define DIGDIT_PHYSICAL_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>

class Physical {
public:
    Physical(Vector2 position, float mass, bool isGround);

    virtual void Update(float dt, double et);
    void ApplyForce(Vector2 force);
    void ApplyGravity(float gravity);

    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);
    float GetMass() const;
    void SetMass(float newMass);
    bool IsGround() const;
    void SetGround(bool value);

private:
    Vector2 position{0.0f, 0.0f};   // Current position of the object
    Vector2 speed{0.0f, 0.0f};      // Current speed of the object
    Vector2 totalForce{0.0f, 0.0f}; // Accumulated forces acting on the object
    float mass = 0.0f;         // Mass of the object
    bool isGround = false;      // Flag indicating whether the object is ground
    float masScale = 1.0f;
};


#endif //DIGDIT_PHYSICAL_H
