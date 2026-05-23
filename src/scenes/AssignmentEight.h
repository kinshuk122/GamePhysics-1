#pragma once
#include <core/Simple2DScene.h>
#include <glm/vec2.hpp>
#include <vector>
#include <imgui.h> 

struct HalfSpace {
    glm::vec2 normal;
    float distance;
};

struct PoolBall {
    glm::vec2 position;
    glm::vec2 velocity;
    float mass = 1.0f;
    float radius = 0.3f;
    bool isPocketed = false;
    ImColor color = ImColor(255, 255, 255, 255); 
};

struct Hole {
    glm::vec2 position;
    float radius;
};

class AssignmentEight : public Simple2DScene {
public:
    void OnEnable() override;
    void OnDisable() override;
    void Update(float deltaTime) override;
    void Draw() override;
    void DrawGUI() override;
    
    const char* GetName() override { return "Assignment 8 - Pool"; }
    
private:
    void ResetBall();
    void HandleBallCollision(PoolBall& b1, PoolBall& b2);
    void UpdateBallPhysics(PoolBall& ball, float deltaTime);

    PoolBall cueBall;
    std::vector<PoolBall> targetBalls;
    std::vector<HalfSpace> boundaries;
    std::vector<Hole> holes;
    
    bool isAiming = false;
    
    float friction = 0.5f;
    float restitution = 0.8f;
    float launchImpulseMultiplier = 10.0f;
    
    float tableWidthX = 5.0f;  
    float tableHeightY = 2.5f; 
};