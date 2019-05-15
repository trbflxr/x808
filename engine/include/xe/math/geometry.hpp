//
// Created by FLXR on 8/15/2018.
//

#ifndef X808_GEOMETRY_HPP
#define X808_GEOMETRY_HPP

#include <vector>
#include <map>

#include <xe/xeint.hpp>
#include <xe/math/vec3.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  class XE_API geometry : NonCopyable {
  public:
    static std::pair<std::vector<vec3>, std::vector<uint>> makeIcosphere(uint subdivisions = 1);

    static std::pair<std::vector<vec3>, std::vector<uint>> makeCone(float radius, float height, uint subdivisions);

  private:

  };

}


#endif //X808_GEOMETRY_HPP
