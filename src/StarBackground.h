//
// Created by pimu on 07.05.23.
//

#ifndef BANDIT_STARBACKGROUND_H
#define BANDIT_STARBACKGROUND_H

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include <iostream>
#include <cmath>
#include "raylib.h"

class StarBackground {

public:
    StarBackground(int _w, int _h, Vector3 _color, float _speed);

    ~StarBackground();

    void Update();

    void DrawBg();

    void DrawFg();

    void DrawTime();

    void UpdateResolution(int _w, int _h);

private:
    int scrW, scrH;
    const float SEED_FACTOR_BG = 1.0f;
    const float SEED_FACTOR_FG = 1.5f;

    Shader shader;

    /**
     * Shader locations
     */
    int iTimeLoc;
    int iResolutionLoc;
    int iColorLoc;
    int iBaseSpeedLoc;
    int iSeedFactorLoc;
    int iDrawingBgLoc;

    /**
     * Shader uniforms
     */

    Vector2 iResolution{};
    Vector3 iColor{};
    float iTime{0.0f};
    float iBaseSpeed = 1.9f;
    float iSeedFactor = SEED_FACTOR_BG;
    int iDrawingBg = 1;

    void setShaderUniforms();

    void setDrawingFg();

    void setDrawingBg();


};


#endif //BANDIT_STARBACKGROUND_H
