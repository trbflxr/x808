//
// Created by FLXR on 7/9/2018.
//

#ifndef X808_RANDOM_HPP
#define X808_RANDOM_HPP


#include <random>
#include <xe/xeint.hpp>

namespace xe {

  class random {
  public:
    template<typename T>
    static T next(const T &low, const T &high);

  private:
    random();

    static random &get();

  private:
    std::mt19937_64 mt;

  };

}


#endif //X808_RANDOM_HPP
