
#include "gui_application_draw_tree/application.h"

namespace gui_application_draw_tree {
    
    Application::Application() 
        : gui_application::GuiApplication(true)
        , time(*this)
        , cameras(*this)
        , entityBrowser(*this)
        , renderer(*this)
        , simulationClock(*this)
        , random(*this)
    {

    }

    Application::~Application() 
    {

    }

    void Application::setup()
    {
        root = pool.create<Transform>("root");
        time.setup();
        simulationClock.setup();
        cameras.setup();
        entityBrowser.setup();
        renderer.setup();
        random.setup();
        
        setupDrawables();
    }

    void Application::setupDrawables()
    {
        for (auto it = root->begin_recurse_data<Drawable>(); it != root->end_recurse_data<Drawable>(); ++it)
        {
            Drawable* drawable = static_cast<Drawable*>(it);
            if(drawable) drawable->setup();
        }
    }

    void Application::frame()
    {
        time.frame();
        simulationClock.frame();
        cameras.frame();
        entityBrowser.frame();
        renderer.frame();
        random.frame();
    }

} // namespace gui_application_draw_tree
