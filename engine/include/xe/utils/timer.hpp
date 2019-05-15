//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_TIMER_HPP
#define X808_TIMER_HPP


#include <xe/xeint.hpp>
#include <xe/common.hpp>

namespace xe {

  struct TimerMembers;

  class XE_API Timer {
  public:
    Timer();

    void reset();

    float elapsed();
    float elapsedMillis();

  private:
    byte reserved[32];
    TimerMembers *members;
  };

}


#endif //X808_TIMER_HPP
