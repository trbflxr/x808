//
// Created by FLXR on 3/18/2019.
//

#ifndef X808_SHADERCONSTANT_HPP
#define X808_SHADERCONSTANT_HPP


#include <xe/string.hpp>

namespace xe {

  struct ShaderConstant {
    string name;
    string value;
  };

  typedef std::vector<ShaderConstant> ShaderConstantVec;
}


#endif //X808_SHADERCONSTANT_HPP
