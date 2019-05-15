//
// Created by FLXR on 2/8/2019.
//

#ifndef X808_SYSTEMSTACK_HPP
#define X808_SYSTEMSTACK_HPP


#include <vector>
#include <xe/systems/system.hpp>

namespace xe {

  class SystemStack : NonCopyable {
  public:
    explicit SystemStack() = default;
    ~SystemStack() override;

    void render();

    void update(float delta);
    void lateUpdate(float delta);
    void fixedUpdate(float delta);

    void input(Event &event);

    void resize(int32 width, int32 height);

    void pushSystem(System *system);
    System *popSystem();

    inline std::vector<System *>::iterator begin() { return systems.begin(); }
    inline std::vector<System *>::iterator end() { return systems.end(); }

  private:
    std::vector<System *> systems;
  };

}


#endif //X808_SYSTEMSTACK_HPP
