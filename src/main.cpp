#include <core/Application.h>
#include "scenes/TestScene.h"
#include "scenes/AssignmentOne.h"
#include "scenes/AssignmentTwo.h"
#include "scenes/AssignmentFour.h"
#include "scenes/AssignmentFive.h"

int main(int argc, char** argv) {
    std::vector<Scene*> scenes = {
        new TestScene(),
        new AssignmentOne(),
        new AssignmentTwo(),
        new AssignmentFour(),
        new AssignmentFive()

    };
    Application app(scenes);
    return app.Run();
}
