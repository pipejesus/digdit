//
// Created by pimu on 07.05.23.
//

#include "StarBackground.h"

StarBackground::StarBackground(int _w, int _h, Vector3 _color, float _speed) : scrW{_w}, scrH{_h} {
    iResolution = Vector2{(float) scrW, (float) scrH};
    iColor = _color;
    iBaseSpeed = _speed;

    shader = LoadShader(nullptr, TextFormat("shaders/glsl%i/starfield.fs.glsl", GLSL_VERSION));

    iResolutionLoc = GetShaderLocation(shader, "iResolution");
    iTimeLoc = GetShaderLocation(shader, "iTime");
    iColorLoc = GetShaderLocation(shader, "iColor");
    iBaseSpeedLoc = GetShaderLocation(shader, "iBaseSpeed");
    iSeedFactorLoc = GetShaderLocation(shader, "iSeedFactor");
    iDrawingBgLoc = GetShaderLocation(shader, "iDrawingBg");

    setShaderUniforms();
}

StarBackground::~StarBackground() {
    UnloadShader(shader);
}

void StarBackground::Update() {
    iTime = GetTime();
    setShaderUniforms();
}

void StarBackground::setShaderUniforms() {
    SetShaderValue(shader, iResolutionLoc, &iResolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, iTimeLoc, &iTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, iColorLoc, &iColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, iBaseSpeedLoc, &iBaseSpeed, SHADER_UNIFORM_FLOAT);
}

void StarBackground::setDrawingFg() {
    iSeedFactor = SEED_FACTOR_FG;
    iDrawingBg = 0;

    SetShaderValue(shader, iSeedFactorLoc, &iSeedFactor, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, iDrawingBgLoc, &iDrawingBg, SHADER_UNIFORM_INT);
}

void StarBackground::setDrawingBg() {
    iSeedFactor = SEED_FACTOR_BG;
    iDrawingBg = 1;

    SetShaderValue(shader, iSeedFactorLoc, &iSeedFactor, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, iDrawingBgLoc, &iDrawingBg, SHADER_UNIFORM_INT);
}

void StarBackground::DrawBg() {
    setDrawingBg();

    BeginShaderMode(shader);
    DrawRectangle(0, 0, scrW, scrH, WHITE);
    EndShaderMode();
}

void StarBackground::DrawTime() {
    const char *tw = TextFormat("W: %i", scrW);
    const char *th = TextFormat("H: %i", scrH);
    int twx = (scrW / 2) - (MeasureText(tw, 20) / 2);
    int twy = (scrW / 2) - (MeasureText(th, 20) / 2);

//    DrawText(tw, twx, (scrH / 2 - 20), 20, WHITE);
//    DrawText(th, twy, (scrH / 2 + 20), 20, WHITE);
}

void StarBackground::DrawFg() {
    setDrawingFg();

    BeginBlendMode(BLEND_ADD_COLORS);
    {
        BeginShaderMode(shader);
        {
            DrawRectangle(0, 0, scrW, scrH, WHITE);
        }
        EndShaderMode();
    }
    EndBlendMode();
}

void StarBackground::UpdateResolution(int _w, int _h) {
    scrW = _w;
    scrH = _h;
    iResolution = Vector2{(float) scrW, (float) scrH};
}


