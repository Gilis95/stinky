#pragma once

#include "application/application.h"

int main(int argc, char **argv) {
  auto app = stinky::create_application();

  app->register_event_handlers();
  app->init();

  app->run();

  delete app;
}