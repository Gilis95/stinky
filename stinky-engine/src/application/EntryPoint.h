#pragma once

#include "application/Application.h"

int main(int argc, char **argv) {
    auto app = stinky::CreateApplication();

    app->Run();

    delete app;
}