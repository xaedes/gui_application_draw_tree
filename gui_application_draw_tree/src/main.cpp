
#include <iostream>
#include "gui_application_draw_tree/version.h"
#include "gui_application_draw_tree/application.h"

using namespace gui_application_draw_tree;

int main(int argc, char **argv)
{   
    std::cout << "gui_application_draw_tree::Version " << VersionMajor << "." << VersionMinor << "." << VersionPatch << std::endl;
    Application app;
    return app.run();
}