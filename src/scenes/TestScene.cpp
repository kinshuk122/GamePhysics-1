#include "TestScene.h"

#include <imgui.h>

TestScene::TestScene() : circlePosition(0, 1), circleRadius(1) {
    // This constructor is called when the application starts.
}

TestScene::~TestScene() {
    // This destructor is never called.
}

void TestScene::OnEnable() {
    // This method is called when this scene is shown.
}

void TestScene::OnDisable() {
    // This method is called when switching from this scene to another.
}

void TestScene::Update(float deltaTime) {
    // This method is called every frame. Perform physics calculations here.
}

void TestScene::Draw() {
    // This method is called every frame. Draw objects here.
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void TestScene::DrawGUI() {
    // This method is called every frame. Draw the GUI here.
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::End();
}