//
// Created by pimu on 28.06.23.
//

#include "Hero.h"
Hero::Hero(Vector2 position, float mass, bool isGround) : Physical(position, mass, isGround) {
    model = LoadModel(TextFormat(MODEL_PATH));
    CalcMeshesTranslations();

//    model.materials[MAT_IDX].maps->color = (Color){253,231,76,255};
//    model.materials[MAT_IDX].shader = sceneShader;
}

Hero::~Hero() {
    UnloadModel(model);
}

void Hero::Draw() {
//    int whichMesh = (int)fmod(GetTime(), 8);

    /** Draw Body **/
    Vector3 centerBody = GetMeshCenter(M_BODY);
    Matrix matCenterBody = MatrixTranslate(-centerBody.x,-centerBody.y, -centerBody.z);
    Vector2 mPosition = GetPosition();

    Matrix matRealCenter = MatrixTranslate(mPosition.x, 0.0f, mPosition.y);
    Matrix finalPos = MatrixAdd(matCenterBody, matRealCenter);
//    DrawModel(model, Vector3{mPosition.x, 0.0f, mPosition.y},1.0, WHITE);
    DrawMesh(model.meshes[M_BODY], model.materials[MAT_IDX], finalPos);
    //    DrawMesh(model.meshes[M_BODY], model.materials[MAT_IDX], matCenterBody);
    std::cout << "MX: " << mPosition.x << std::endl;

//    DrawMesh(model.meshes[M_BODY], model.materials[MAT_IDX], matCenterBody);

//    Vector3 centerHead = GetMeshCenter(M_HEAD);
//    Matrix matCenterHead = MatrixTranslate(-centerHead.x,-centerHead.y, -centerHead.z);
//    Matrix moveHeadUp = MatrixTranslate(0.0f, 0.0f, -0.4f);
//    // rotate: MatrixMultiply(MatrixRotateX(DEG2RAD * 90.0f),MatrixAdd(matCenterHead, moveHeadUp))
//    DrawMesh(model.meshes[M_HEAD], model.materials[MAT_IDX], MatrixAdd(matCenterHead, moveHeadUp));
//
//    Vector3 centerEye = GetMeshCenter(M_EYE);
//    Matrix matCenterEye = MatrixTranslate(-centerEye.x,-centerEye.y, -centerEye.z);
//    Matrix moveEyeUp = MatrixTranslate(0.0f, 0.0f, -0.4f);
//    DrawMesh(model.meshes[M_EYE], model.materials[MAT_IDX], MatrixAdd(matCenterEye, moveEyeUp));

}

Vector3 Hero::GetMeshCenter(int idx) {
    auto box = GetMeshBoundingBox(model.meshes[idx]);

    Vector3 size = {
            fabsf(box.max.x - box.min.x),
            fabsf(box.max.y - box.min.y),
            fabsf(box.max.z - box.min.z)
    };

    return Vector3 {
        box.min.x + size.x/2.0f,
        box.min.y + size.y/2.0f,
        box.min.z + size.z/2.0f
    };
}

void Hero::DrawMeshAt(int idx, Vector3 pos) {

}

void Hero::Update(float dt, double et) {
    Physical::Update(dt, et);
//    std::cout << "Updating hero, too" << std::endl;
}

void Hero::CalcMeshesTranslations() {
    for (int i = 0; i < model.meshCount; i++) {
        meshesTranslations.push_back(GetMeshCenter(i));
    }
}
