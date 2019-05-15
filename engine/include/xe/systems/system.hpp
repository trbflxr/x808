//
// Created by FLXR on 11/14/2018.
//

#ifndef X808_SYSTEM_HPP
#define X808_SYSTEM_HPP


#include <xe/app/application.hpp>

namespace xe {

  class System {
  public:
    virtual ~System() = default;

    virtual void init() { }

    virtual void render() { }

    virtual void update(float delta) { }
    virtual void lateUpdate(float delta) { }
    virtual void fixedUpdate(float delta) { }

    virtual void input(Event &event) { }

    inline bool isActive() const { return active; }
    inline void setActive(bool active) { System::active = active; }

  protected:
    explicit System() :
        app(Application::get()),
        window(app.getWindow()),
        active(false) { }

    virtual void resize(int32 width, int32 height) { }

  protected:
    friend class SystemStack;

    Application &app;
    Window &window;

    bool active;
  };

}


#endif //X808_SYSTEM_HPP
