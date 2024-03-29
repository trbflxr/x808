//
// Created by FLXR on 7/6/2018.
//

#include "glshadersampler.hpp"

namespace xe::internal {

  GLShaderSampler::GLShaderSampler(Type type, const string &name, uint count) :
      type(type),
      name(name),
      count(count),
      location(static_cast<uint>(-1)) { }


  GLShaderSampler::Type GLShaderSampler::stringToType(const string &type) {
    if (type == "sampler1D") return Type::Sampler1D;
    else if (type == "sampler2D") return Type::Sampler2D;
    else if (type == "sampler2DArray") return Type::Sampler2DArray;
    else if (type == "sampler3D") return Type::Sampler3D;
    else if (type == "samplerCube") return Type::SamplerCube;
    else if (type == "samplerCubeArray") return Type::SamplerCubeArray;

    return Type::None;
  }

  string GLShaderSampler::typeToString(GLShaderSampler::Type type) {
    switch (type) {
      case Type::Sampler1D: return "sampler1D";
      case Type::Sampler2D: return "sampler2D";
      case Type::Sampler2DArray: return "sampler2DArray";
      case Type::Sampler3D: return "sampler3D";
      case Type::SamplerCube: return "samplerCube";
      case Type::SamplerCubeArray: return "samplerCubeArray";
      case Type::None: break;
    }
    return "invalid";
  }

  bool GLShaderSampler::isTypeStrSampler(const string &type) {
    if (type == "sampler1D") return true;
    else if (type == "sampler2D") return true;
    else if (type == "sampler2DArray") return true;
    else if (type == "sampler3D") return true;
    else if (type == "samplerCube") return true;
    else if (type == "samplerCubeArray") return true;
    return false;
  }


}