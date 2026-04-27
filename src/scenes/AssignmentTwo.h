#pragma once

#include <core/Simple2DScene.h>

class AssignmentTwo : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "AssignmentTwo"; };

private:
    float circlePosition = 2.0f;
    float velocity = 0.0f;
    float force = 5.0f; 
    float gravity = -9.8f;
    float mass = 1.0f;

    float lineY = 0.0f;
    float forceFieldForce = 25.0f;
};