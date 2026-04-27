#include <core/Application.h>
#include "scenes/TestScene.h"
#include "scenes/AssignmentOne.h"
#include "scenes/AssignmentTwo.h"

int main(int argc, char** argv) {
    std::vector<Scene*> scenes = {
        new TestScene(),
        new AssignmentOne(),
        new AssignmentTwo()
    };
    Application app(scenes);
    return app.Run();
}
