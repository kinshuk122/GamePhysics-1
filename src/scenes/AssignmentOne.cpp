#include "AssignmentOne.h"
#include <imgui.h>
#include <core/Draw.h>
#include <glm/vec2.hpp>



void AssignmentOne::OnEnable() {}

void AssignmentOne::OnDisable() {}

void AssignmentOne::Update(float deltaTime) {
    myVelocityY = myVelocityY + (myGravity * deltaTime);
    
    myParticleY = myParticleY + (myVelocityY * deltaTime);


    if (myParticleY < 0.5f) {
        myParticleY = 0.5f;
        myVelocityY = myVelocityY * -1.0f; 
    }
}

void AssignmentOne::Draw() {
    float particleX = 0.0f;
    float particleRadius = 0.5f;
    
    glm::vec2 particlePosition = glm::vec2(particleX, myParticleY);
    Draw::Circle(particlePosition, particleRadius);

    float groundLeftX = -20.0f;
    float groundLeftY = 0.0f;
    float groundRightX = 20.0f;
    float groundRightY = 0.0f;
    
    glm::vec2 lineStart = glm::vec2(groundLeftX, groundLeftY);
    glm::vec2 lineEnd = glm::vec2(groundRightX, groundRightY);
    Draw::Line(lineStart, lineEnd);
}

void AssignmentOne::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::Text("Particle Y: %f", myParticleY);
    ImGui::Text("Velocity Y: %f", myVelocityY);
    ImGui::End();
}
