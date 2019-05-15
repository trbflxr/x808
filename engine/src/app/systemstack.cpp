//
// Created by FLXR on 2/8/2019.
//

#include "systemstack.hpp"

namespace xe {

  SystemStack::~SystemStack() {
    for (const auto &system   : systems) {
      delete system;
    }
  }

  void SystemStack::pushSystem(System *system) {
    systems.push_back(system);
    system->init();
  }

  System *SystemStack::popSystem() {
    System *system = systems.front();
    systems.erase(begin());
    return system;
  }

  void SystemStack::render() {
    for (auto it = systems.end(); it != systems.begin();) {
      if ((*--it)->isActive()) {
        (*it)->render();
      }
    }
  }

  void SystemStack::update(float delta) {
    for (const auto &system : systems) {
      system->update(delta);
    }
  }

  void SystemStack::lateUpdate(float delta) {
    for (const auto &system : systems) {
      system->lateUpdate(delta);
    }
  }

  void SystemStack::fixedUpdate(float delta) {
    for (const auto &system : systems) {
      system->fixedUpdate(delta);
    }
  }

  void SystemStack::input(Event &event) {
    for (const auto &system : systems) {
      system->input(event);
    }
  }

  void SystemStack::resize(int32 width, int32 height) {
    for (const auto &system : systems) {
      system->resize(width, height);
    }
  }

}
