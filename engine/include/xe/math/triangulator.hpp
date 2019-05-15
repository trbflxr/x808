//
// Created by FLXR on 9/20/2018.
//

#ifndef X808_TRIANGULATOR_HPP
#define X808_TRIANGULATOR_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>

namespace xe {

  class XE_API triangulator {
  public:
    static void compute(const std::vector<vec2> &vertices, std::vector<uint> &triangleIndices);

  private:
    static void triangulate(std::vector<int32> &types, const vec2 *vertices, std::vector<uint> &indices,
                            std::vector<uint> &triangles, uint count);

    static int32 classifyVertex(const vec2 *vertices, const uint *indices, uint index, uint count);

    static bool areVerticesClockwise(const vec2 *vertices, uint count);
    static int32 computeSpannedAreaSign(const vec2 &p1, const vec2 &p2, const vec2 &p3);

    static uint findEarTip(const int32 *types, const vec2 *vertices, const uint *indices, uint count);
    static void cutEarTip(std::vector<int32> &types, std::vector<uint> &indices, std::vector<uint> &triangles,
                          uint index, uint &count);

    static bool isEarTip(const int32 *types, const vec2 *vertices, const uint *indices, uint index, uint count);

    static inline uint previousIndex(uint index, uint count) { return (index == 0 ? count : index) - 1; }
    static inline uint nextIndex(uint index, uint count) { return (index + 1) % count; }
  };

}


#endif //X808_TRIANGULATOR_HPP
