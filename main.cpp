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
#include "rcamera.h"
#include "src/Hero.h"

int screenWidth = 1024;
int screenHeight = 512;

Camera camera = {0};
Shader sceneShader;

float ambientLight[4]{0.10f, 0.10f, 0.10f, 1.0f};
int ambientLightLoc;
float lightAngle = 0.0f;
Hero *hero = nullptr;

std::vector<Light> sceneLights{};

auto pos = Vector3{0.0, 0.0f, 0.0f};
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
                    LIGHT_DIRECTIONAL,
                    Vector3{0.0f, 2.0f, 5.0f},
                    Vector3Zero(),
                    Color{0, 20, 100, 2},
                    sceneShader
            )
    );
}

void setupCamera() {
    camera.position = (Vector3) {0.0f, 6.0f, 0.01f};    // Camera position
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;
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
    lightAngle += 0.4f * dt;
    sceneLights[0].position.z = sin(lightAngle);
    sceneLights[0].position.x = cos(lightAngle);
}

void loadModels() {
    hero = new Hero(Vector2{0.0f, -1.0f}, 1.0f, false);
//    hero->ApplyGravity(9.81f);
    hero->ApplyForce(Vector2{0.0f, 1/9.81});
}

void init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Digdit");
    loadModels();
    setupSceneShader();
    setupCamera();    
    createLights();
    SetTargetFPS(60);
}

void deInit() {
    delete hero;
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
//    UpdateLightValues(sceneShader, sceneLights[0]);

//    UpdateCamera(&camera, CAMERA_ORBITAL);
//    UpdateCameraPro(&camera, Vector3{0.0f ,0.002f, 0.0f},Vector3{0.0f ,0.0f, 0.0f}, 0.0f);
//    CameraMoveToTarget(&camera, -0.1f);
    camera.position = Vector3Add(camera.target, Vector3Scale(GetCameraForward(&camera), -2.0f));
    animateLights(dt);

    hero->Update(dt, GetTime());

    BeginDrawing();
    {
        ClearBackground(BLACK);  // Clear texture background

        BeginMode3D(camera);
        {
            hero->Draw();
//            DrawGrid(200, 0.25f);
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