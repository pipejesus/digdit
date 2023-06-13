// https://www.raylib.com/examples/models/loader.html?name=models_mesh_picking

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define RLIGHTS_IMPLEMENTATION

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else
#define GLSL_VERSION            100
#endif

#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "shaders/rlights.h"

Model model;
int screenWidth = 1024;
int screenHeight = 512;

Camera camera = {0};
Shader sceneShader;

float ambientLight[4]{0.10f, 0.10f, 0.10f, 1.0f};
int ambientLightLoc;
float lightAngle = 0.0f;

std::vector<Light> sceneLights{};

auto pos = Vector3{0.0, 0.0f, 0.0f};
auto rotAxis = Vector3{0.0f, 1.0f, 0.0f};
auto scale = Vector3{1.0f, 1.0f, 1.0f};

void setupSceneShader() {
    sceneShader = LoadShader(TextFormat("shaders/glsl%i/lighting.vs", GLSL_VERSION),
                             TextFormat("shaders/glsl%i/lighting.fs", GLSL_VERSION));
    sceneShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(sceneShader, "viewPos");
    ambientLightLoc = GetShaderLocation(sceneShader, "ambient");
    SetShaderValue(sceneShader, ambientLightLoc, &ambientLight, SHADER_UNIFORM_VEC4);
}

void createLights() {
    sceneLights.push_back(
            CreateLight(
                    LIGHT_POINT,
                    Vector3{0.0f, 2.0f, 0.0f},
                    Vector3Zero(),
                    Color{100, 100, 100, 255},
                    sceneShader
            )
    );
}

void setupCamera() {
    camera.position = (Vector3) {0.0f, .5f, 1.8f};    // Camera position
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}

extern "C" {
void onResize(int w, int h) {
    screenWidth = w;
    screenHeight = h;
    SetWindowSize(w, h);
}
}

void animateLights(float dt) {
    lightAngle += 1.4f * dt;
    sceneLights[0].position.z = sin(lightAngle);
    sceneLights[0].position.x = cos(lightAngle);
}


void init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Digdit");
    setupSceneShader();
    setupCamera();    
    createLights();    
    SetTargetFPS(60);
}

void deInit() {    
    UnloadShader(sceneShader);    
    CloseWindow();
}

void loop() {
    if (IsWindowResized()) {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();        
    }

    float dt = GetFrameTime();
    float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
    SetShaderValue(sceneShader, sceneShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    UpdateLightValues(sceneShader, sceneLights[0]);

    UpdateCamera(&camera, CAMERA_ORBITAL);

    animateLights(dt);    

    BeginDrawing();
    {
        ClearBackground(BLACK);  // Clear texture background

        BeginMode3D(camera);
        {
            DrawCube(pos, 1.0f, 1.0f, 1.0f, WHITE);
        }
        EndMode3D();
    }

    EndDrawing();
}

int main() {
    init();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!WindowShouldClose()) {
        loop();
    }
#endif

    deInit();

    return 0;
}