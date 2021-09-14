
#include "gui_application_draw_tree/random.h"
#include "gui_application_draw_tree/application.h"

namespace gui_application_draw_tree {

    Random::Random(Application& app) 
        : app(app)
        , gui_application::Random(1337)
    {}

    Random::~Random() 
    {}

    void Random::setup()
    {
        gui_application::Random::seed(1337);
    }

    void Random::frame()
    {}

} // namespace gui_application_draw_tree
