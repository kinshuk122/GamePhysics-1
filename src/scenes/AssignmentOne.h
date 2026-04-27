#pragma once

#include <core/Simple2DScene.h>

class AssignmentOne : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "AssignmentOne"; };

    private:
        float myParticleY = 2.0f;
        float myVelocityY = 0.0f;
        float myGravity = -9.8f;
};
