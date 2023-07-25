//
// Created by pimu on 01.07.23.
//

#include "Physical.h"

Physical::Physical(Vector2 position, float mass, bool isGround): position{position}, mass{mass}, isGround{isGround}
{

}

void Physical::Update(float dt, double et)
{
    if (isGround)
    {
        return;
    }

//    std::cout << "Updating in Phyci" << std::endl;

    Vector2 acceleration = Vector2{totalForce.x / (mass * masScale), totalForce.y / (mass * masScale)};
    speed.x += acceleration.x * dt;
    speed.y += acceleration.y * dt;

    position.x += speed.x * dt;
    position.y += speed.y * dt;
}

void Physical::ApplyGravity(float gravity)
{
    ApplyForce({0, mass * gravity * masScale});
}

void Physical::ApplyForce(Vector2 force)
{
    totalForce.x += force.x;
    totalForce.y += force.y;
}

Vector2 Physical::GetPosition() const
{
    return position;
}

void Physical::SetPosition(Vector2 newPosition)
{
    position = newPosition;
}

float Physical::GetMass() const
{
    return mass;
}

void Physical::SetMass(float newMass)
{
    mass = newMass;
}

bool Physical::IsGround() const
{
    return isGround;
}

void Physical::SetGround(bool value)
{
    isGround = value;
}

