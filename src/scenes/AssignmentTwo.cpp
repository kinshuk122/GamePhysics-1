#include "AssignmentTwo.h"
#include <imgui.h>
#include <core/Draw.h>
#include <glm/vec2.hpp>

void AssignmentTwo::OnEnable() {
    // Initialization code here
}

void AssignmentTwo::OnDisable() {
    // Cleanup code here
}

void AssignmentTwo::Update(float deltaTime) {

    force += 10.0f;  
    force += (mass * gravity); 

    if (circlePosition <= lineY) {
        force += forceFieldForce;
    }

    float accelerationY = force / mass;

    velocity += accelerationY * deltaTime;
    circlePosition += velocity * deltaTime;

    force = 0.0f;
}

void AssignmentTwo::Draw() {
    float particleX = 0.0f;
    float particleRadius = 0.5f;

    glm::vec2 particlePosition = glm::vec2(particleX, circlePosition);
    Draw::Circle(particlePosition, particleRadius);

    glm::vec2 lineStart = glm::vec2(-5.0f, lineY);
    glm::vec2 lineEnd = glm::vec2(5.0f, lineY);
    Draw::Line(lineStart, lineEnd);
}

void AssignmentTwo::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::Text("Particle Y: %f", circlePosition);
    ImGui::Text("Velocity Y: %f", velocity);
    
    ImGui::DragFloat("Mass", &mass, 0.1f, 0.1f, 100.0f);
    
    ImGui::Spacing();
    ImGui::Text("Force Field Properties");
    ImGui::DragFloat("Line Boundary Y", &lineY, 0.1f);
    ImGui::DragFloat("Field Upward Force", &forceFieldForce, 0.5f);
    
    ImGui::End();
}