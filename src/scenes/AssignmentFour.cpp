#include "AssignmentFour.h"
#include <imgui.h>
#include <core/Draw.h>
#include <glm/geometric.hpp>

void AssignmentFour::OnEnable() {
    circlePosition = glm::vec2(0.0f, 5.0f);
    velocity = glm::vec2(0.0f, 0.0f);
}

void AssignmentFour::OnDisable() {
}

void AssignmentFour::Update(float deltaTime) {
    velocity.y += gravity * deltaTime;
    circlePosition += velocity * deltaTime;

    glm::vec2 lineVector = linePoint2 - linePoint1;
    if (glm::length(lineVector) > 0.0001f) {
        glm::vec2 lineDir = glm::normalize(lineVector);
        
        glm::vec2 normal = glm::vec2(-lineDir.y, lineDir.x);

        glm::vec2 pointToCircle = circlePosition - linePoint1;

        float distanceToPlane = glm::dot(pointToCircle, normal);

        if (distanceToPlane < circleRadius) {
            float penetrationDepth = circleRadius - distanceToPlane;
            
            circlePosition += normal * penetrationDepth;

            float normalVelocity = glm::dot(velocity, normal);
            if (normalVelocity < 0.0f) {
                velocity -= normal * normalVelocity;
            }
        }
    }
}

void AssignmentFour::Draw() {
    Draw::Line(linePoint1, linePoint2);

    glm::vec2 lineVector = linePoint2 - linePoint1;
    if (glm::length(lineVector) > 0.0001f) {
        glm::vec2 lineDir = glm::normalize(lineVector);
        glm::vec2 normal = glm::vec2(-lineDir.y, lineDir.x);
        glm::vec2 midpoint = (linePoint1 + linePoint2) * 0.5f;
        
        Draw::Line(midpoint, midpoint + normal * 2.0f);
    }

    Draw::Circle(circlePosition, circleRadius);
}

void AssignmentFour::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::Text("Assignment Four Scene");
    
    ImGui::Spacing();
    ImGui::Text("Environment");
    ImGui::DragFloat2("Line Point 1", &linePoint1.x, 0.1f);
    ImGui::DragFloat2("Line Point 2", &linePoint2.x, 0.1f);
    
    ImGui::Spacing();
    ImGui::Text("Circle Stats");
    ImGui::Text("Position: (%.2f, %.2f)", circlePosition.x, circlePosition.y);
    ImGui::Text("Velocity: (%.2f, %.2f)", velocity.x, velocity.y);

    if (ImGui::Button("Reset Circle")) {
        circlePosition = glm::vec2(0.0f, 5.0f);
        velocity = glm::vec2(0.0f, 0.0f);
    }
    
    ImGui::End();
}
