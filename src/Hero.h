//
// Created by pimu on 28.06.23.
//

#ifndef DIGDIT_HERO_H
#define DIGDIT_HERO_H

#include <cmath>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Physical.h"
#include <iostream>

class Hero: public Physical {
public:
    const char * MODEL_PATH = "models-final/clayfi.glb";
    const int MAT_IDX = 1; //
    const int M_BODY = 0;
    const int M_HEAD = 1;
    const int M_EAR = 2; // OK
    const int M_EYE = 3; // OK
    const int M_JAW_BOTTOM = 4; // OK
    const int M_JAW_TOP = 5; // OK
    const int M_HAND = 6; // OK
    const int M_LEG = 7; // OK

    Hero(Vector2 position, float mass, bool isGround);
    ~Hero();
    void Draw();
    void Update(float dt, double et) override;

protected:
    std::vector<Vector3> meshesTranslations {};
    Vector3 pos {0.0f, 0.0f, 0.0f};
    Vector3 acc {0.0f, 0.0f, 0.0f};
    Model model {};

    void CalcMeshesTranslations();
    void DrawMeshAt(int idx, Vector3 pos);
    Vector3 GetMeshCenter(int idx);
};


#endif //DIGDIT_HERO_H
