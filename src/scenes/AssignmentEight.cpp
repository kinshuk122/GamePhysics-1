#include "AssignmentEight.h"
#include <imgui.h>
#include <core/Draw.h>
#include <core/Input.h>  
#include <glm/glm.hpp>
#include <cmath>

void AssignmentEight::ResetBall() 
{
    cueBall.position = glm::vec2(-tableWidthX * 0.5f, 0.0f); 
    cueBall.velocity = glm::vec2(0.0f, 0.0f);
    cueBall.radius = 0.3f;
    cueBall.mass = 1.0f;
    cueBall.isPocketed = false;
    cueBall.color = ImColor(255, 255, 255, 255);
    isAiming = false;

    targetBalls.clear();
    float startX = 1.5f; 
    float radius = cueBall.radius;
    float spacing = radius * 2.05f;
    
    int rows = 4;
    for (int col = 0; col < rows; ++col) 
    {
        for (int row = 0; row <= col; ++row) 
        {
            PoolBall newBall;
            newBall.radius = radius;
            newBall.mass = 1.0f;
            newBall.velocity = glm::vec2(0.0f, 0.0f);
            newBall.isPocketed = false;
            
            newBall.color = ImColor(200, 30, 30, 255);
            
            float xPos = startX + col * (spacing * 0.866f);
            float yPos = (row - col * 0.5f) * spacing;
            newBall.position = glm::vec2(xPos, yPos);
            
            targetBalls.push_back(newBall);
        }
    }
}

void AssignmentEight::OnEnable() 
{
    ResetBall();

    boundaries.clear();
    boundaries.push_back({ glm::vec2(-1.0f, 0.0f), -tableWidthX });
    boundaries.push_back({ glm::vec2(1.0f, 0.0f), -tableWidthX });
    boundaries.push_back({ glm::vec2(0.0f, -1.0f), -tableHeightY });
    boundaries.push_back({ glm::vec2(0.0f, 1.0f), -tableHeightY });

    holes.clear();
    float holeRadius = 0.5f; 
    holes.push_back({ glm::vec2(-tableWidthX, tableHeightY), holeRadius });
    holes.push_back({ glm::vec2(tableWidthX, tableHeightY), holeRadius });
    holes.push_back({ glm::vec2(-tableWidthX, -tableHeightY), holeRadius });
    holes.push_back({ glm::vec2(tableWidthX, -tableHeightY), holeRadius });
    holes.push_back({ glm::vec2(0.0f, tableHeightY), holeRadius });
    holes.push_back({ glm::vec2(0.0f, -tableHeightY), holeRadius });
}

void AssignmentEight::OnDisable() 
{


}

void AssignmentEight::HandleBallCollision(PoolBall& b1, PoolBall& b2) 
{
    if (b1.isPocketed || b2.isPocketed) return;

    glm::vec2 delta = b2.position - b1.position;
    float dist = glm::length(delta);
    float minDist = b1.radius + b2.radius;

    if (dist < minDist && dist > 0.0001f) 
    {
        glm::vec2 normal = delta / dist;
        float penetration = minDist - dist;
        float totalMass = b1.mass + b2.mass;
        
        b1.position -= normal * (penetration * (b2.mass / totalMass));
        b2.position += normal * (penetration * (b1.mass / totalMass));

        glm::vec2 relVel = b2.velocity - b1.velocity;
        float velAlongNormal = glm::dot(relVel, normal);

        if (velAlongNormal < 0.0f) {
            float j = -(1.0f + restitution) * velAlongNormal;
            j /= (1.0f / b1.mass + 1.0f / b2.mass);

            glm::vec2 impulse = j * normal;
            b1.velocity -= impulse / b1.mass;
            b2.velocity += impulse / b2.mass;
        }
    }
}

void AssignmentEight::UpdateBallPhysics(PoolBall& ball, float deltaTime) 
{
    if (ball.isPocketed) return;

    if (glm::length(ball.velocity) > 0.01f) 
    {
        glm::vec2 frictionForce = -glm::normalize(ball.velocity) * friction;
        ball.velocity += (frictionForce / ball.mass) * deltaTime;
    } else 
    {
        ball.velocity = glm::vec2(0.0f, 0.0f);
    }

    ball.position += ball.velocity * deltaTime;

    for (const auto& boundary : boundaries) {
        float distanceToPlane = glm::dot(ball.position, boundary.normal) - boundary.distance;
        if (distanceToPlane < ball.radius) {
            float penetrationDepth = ball.radius - distanceToPlane;
            ball.position += boundary.normal * penetrationDepth;
            
            float velocityAlongNormal = glm::dot(ball.velocity, boundary.normal);
            if (velocityAlongNormal < 0.0f) { 
                float j = -(1.0f + restitution) * velocityAlongNormal;
                ball.velocity += j * boundary.normal;
            }
        }
    }

    for (const auto& hole : holes) 
    {
        float distance = glm::length(ball.position - hole.position);
        if (distance < hole.radius) 
        {
            ball.isPocketed = true;
            ball.velocity = glm::vec2(0.0f, 0.0f);
            if (&ball == &cueBall) isAiming = false;
        }
    }
}

void AssignmentEight::Update(float deltaTime) 
{
    if (!cueBall.isPocketed) 
    {
        glm::vec2 mousePos = Input::GetMousePos();
        bool isMouseDown = Input::IsMouseButtonPressed(Input::MouseButton_Left);

        if (Input::WasMouseButtonPressedThisFrame(Input::MouseButton_Left)) {
            float distToMouse = glm::length(mousePos - cueBall.position);
            if (distToMouse <= cueBall.radius * 3.0f) {
                isAiming = true;
            }
        }
        
        if (isAiming && !isMouseDown) {
            glm::vec2 impulseVector = cueBall.position - mousePos; 
            cueBall.velocity += impulseVector * (launchImpulseMultiplier / cueBall.mass);
            isAiming = false;
        }
    }

    UpdateBallPhysics(cueBall, deltaTime);
    for (auto& target : targetBalls) {
        UpdateBallPhysics(target, deltaTime);
    }

    for (auto& target : targetBalls) {
        HandleBallCollision(cueBall, target);
    }
    
    for (size_t i = 0; i < targetBalls.size(); ++i) {
        for (size_t j = i + 1; j < targetBalls.size(); ++j) {
            HandleBallCollision(targetBalls[i], targetBalls[j]);
        }
    }
}

void AssignmentEight::Draw() 
{
    glm::vec2 tl(-tableWidthX, tableHeightY);
    glm::vec2 tr(tableWidthX, tableHeightY);
    glm::vec2 bl(-tableWidthX, -tableHeightY);
    glm::vec2 br(tableWidthX, -tableHeightY);

    Draw::Line(tl, tr); 
    Draw::Line(bl, br); 
    Draw::Line(tl, bl); 
    Draw::Line(tr, br); 
    
    for (const auto& hole : holes) 
    {
        Draw::Circle(hole.position, hole.radius);
    }
    
    if (isAiming && !cueBall.isPocketed) 
    {
        glm::vec2 mousePos = Input::GetMousePos();
        Draw::SetColor(ImColor(255, 255, 255, 100)); 
        Draw::Line(mousePos, cueBall.position); 
        Draw::Reset(); 
    }

    if (!cueBall.isPocketed) 
    {
        Draw::SetColor(cueBall.color);
        Draw::Circle(cueBall.position, cueBall.radius, true);
        Draw::Reset();
    }
    
    for (const auto& ball : targetBalls) 
    {
        if (!ball.isPocketed) {
            Draw::SetColor(ball.color);
            Draw::Circle(ball.position, ball.radius, true);
            Draw::Reset();
        }
    }
}

void AssignmentEight::DrawGUI() 
{
    ImGui::Begin("Pool Game Settings (Assignment 8)");
    
    if (cueBall.isPocketed) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "BALL POCKETED!");
    } else if (isAiming) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "AIMING...");
    } else {
        ImGui::Text("Cue Ball Position: (%.2f, %.2f)", cueBall.position.x, cueBall.position.y);
        ImGui::Text("Cue Ball Velocity: (%.2f, %.2f)", cueBall.velocity.x, cueBall.velocity.y);
    }
    
    ImGui::Separator();
    
    if (ImGui::Button("Reset Ball")) {
        ResetBall();
    }
    
    ImGui::End();
}