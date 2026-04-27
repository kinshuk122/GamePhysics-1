#pragma once
#include <core/Simple2DScene.h>
#include <glm/vec2.hpp>

class AssignmentFour : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "AssignmentFour"; }

private:
    glm::vec2 linePoint1 = glm::vec2(-10.0f, -2.0f);
    glm::vec2 linePoint2 = glm::vec2(10.0f, 2.0f);

    glm::vec2 circlePosition = glm::vec2(0.0f, 5.0f);
    glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
    float circleRadius = 1.0f;
    float gravity = -9.8f;
};
