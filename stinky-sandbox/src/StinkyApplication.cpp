#include "StinkyApplication.h"
#include "StinkyLayer.h"
#include "application/EntryPoint.h"

#include <filesystem>

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    StinkyApplication::StinkyApplication() : Application(Window::API::GLFW) {
        PushLayer(new StinkyLayer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application *CreateApplication() {
        std::cout << "Current path is " << std::filesystem::current_path() << '\n';
        return new StinkyApplication();
    }

}
