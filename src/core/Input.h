#pragma once

#include <glm/vec2.hpp>

namespace Input {

// Returns the mouse position in world coordinates.
glm::vec2 GetMousePos();
// Returns the mouse position in imgui window coordinates.
glm::vec2 GetMousePosInWindow();

// Enum for the mouse buttons.
// See ImGuiMouseButton_
enum MouseButton {
    MouseButton_Left = 0,
    MouseButton_Right = 1,
    MouseButton_Middle = 2,
};

// Returns true if the mouse button is currently pressed.
bool IsMouseButtonPressed(MouseButton mouseButton);
// Returns true if the mouse button was pressed this frame.
bool WasMouseButtonPressedThisFrame(MouseButton mouseButton);
// Returns true if the mouse button was released this frame.
bool WasMouseButtonReleasedThisFrame(MouseButton mouseButton);

} // namespace Input