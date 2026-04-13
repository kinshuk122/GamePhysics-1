#pragma once

#include <core/Simple2DScene.h>

class AssignmentOne : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "AssignmentOne"; };
};
