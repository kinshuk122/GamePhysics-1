#include "AssignmentFive.h"
#include <imgui.h>
#include <core/Draw.h>
#include <core/Input.h>
#include <glm/geometric.hpp>
#include <algorithm>
#include <cmath>

void AssignmentFive::OnEnable() {
    circles.clear();
    circles.push_back({ glm::vec2(0.0f, 5.0f), glm::vec2(0.0f, 0.0f), 0.0f });
}

void AssignmentFive::OnDisable() {
    circles.clear();
}

void AssignmentFive::Update(float deltaTime) {
    if (Input::WasMouseButtonPressedThisFrame(Input::MouseButton_Left)) {
        glm::vec2 mousePos = Input::GetMousePos();
        circles.push_back({ mousePos, glm::vec2(0.0f, 0.0f), 0.0f });
    }

    glm::vec2 p1 = lineCenter - glm::vec2(5.0f, 0.0f);
    glm::vec2 p2 = lineCenter + glm::vec2(5.0f, 0.0f);
    glm::vec2 lineVec = p2 - p1;
    float lineLenSq = glm::dot(lineVec, lineVec);

    for (auto& circle : circles) {
        if (circle.redTimer > 0.0f) {
            circle.redTimer -= deltaTime;
        }

        circle.velocity.y += gravity * deltaTime;
        circle.position += circle.velocity * deltaTime;

        glm::vec2 pointVec = circle.position - p1;
        float t = 0.0f;
        if (lineLenSq > 0.0001f) {
            t = std::clamp(glm::dot(pointVec, lineVec) / lineLenSq, 0.0f, 1.0f); 
        }
        
        glm::vec2 closestPoint = p1 + lineVec * t;
        glm::vec2 distVec = circle.position - closestPoint;
        float distanceSq = glm::dot(distVec, distVec);

        if (distanceSq < circleRadius * circleRadius && distanceSq > 0.0001f) {
            float distance = std::sqrt(distanceSq);
            float penetration = circleRadius - distance;
            glm::vec2 normal = distVec / distance;

            circle.position += normal * penetration;

            float normalVelocity = glm::dot(circle.velocity, normal);
            if (normalVelocity < 0.0f) {
                circle.velocity -= 2.0f * normal * normalVelocity;
            }
        }
    }

    for (size_t i = 0; i < circles.size(); ++i) {
        for (size_t j = i + 1; j < circles.size(); ++j) {
            glm::vec2 distVec = circles[i].position - circles[j].position;
            float distSq = glm::dot(distVec, distVec);
            
            float minDistance = circleRadius * 2.0f;

            if (distSq < minDistance * minDistance && distSq > 0.0001f) {
                circles[i].redTimer = 0.2f;
                circles[j].redTimer = 0.2f;

                float distance = std::sqrt(distSq);
                float penetration = minDistance - distance;
                glm::vec2 normal = distVec / distance;

                circles[i].position += normal * (penetration * 0.5f);
                circles[j].position -= normal * (penetration * 0.5f);

                glm::vec2 relativeVelocity = circles[i].velocity - circles[j].velocity;
                float velocityAlongNormal = glm::dot(relativeVelocity, normal);

                if (velocityAlongNormal < 0.0f) {
                    glm::vec2 impulseNormal = normal * velocityAlongNormal;
                    circles[i].velocity -= impulseNormal;
                    circles[j].velocity += impulseNormal;
                }
            }
        }
    }
}

void AssignmentFive::Draw() {
    glm::vec2 p1 = lineCenter - glm::vec2(5.0f, 0.0f);
    glm::vec2 p2 = lineCenter + glm::vec2(5.0f, 0.0f);

    Draw::Line(p1, p2);

    for (const auto& circle : circles) {
        if (circle.redTimer > 0.0f) {
            Draw::SetColor(IM_COL32(255, 0, 0, 255)); 
        } else {
            Draw::Reset(); 
        }

        Draw::Circle(circle.position, circleRadius);
    }
    
    Draw::Reset(); 
}

void AssignmentFive::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::Text("Assignment Five - Collision Resolution");
    
    ImGui::Spacing();
    ImGui::Text("Simulation Stats");
    ImGui::Text("Active Circles: %zu", circles.size());

    if (ImGui::Button("Clear All Circles")) {
        circles.clear();
    }
    
    ImGui::End();
}