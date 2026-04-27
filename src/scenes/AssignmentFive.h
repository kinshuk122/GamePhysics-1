#pragma once

#include <core/Simple2DScene.h>
#include <glm/vec2.hpp>
#include <vector>

struct PhysicsCircle {
    glm::vec2 position;
    glm::vec2 velocity;
    float redTimer = 0.0f;
};

class AssignmentFive : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "AssignmentFive"; }

private:
    glm::vec2 lineCenter = glm::vec2(0.0f, -2.0f);
    std::vector<PhysicsCircle> circles;
    float circleRadius = 1.0f;
    float gravity = -9.8f;
};