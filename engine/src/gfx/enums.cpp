//
// Created by FLXR on 8/20/2018.
//

#include <xe/gfx/enums.hpp>

namespace xe {
  const char *shaderTypeToString(ShaderType type) {
    switch (type) {
      case ShaderType::Vert: return "Vert";
      case ShaderType::Frag: return "Frag";
      case ShaderType::Geom: return "Geom";
      case ShaderType::TessEval: return "TessEval";
      case ShaderType::TessControl: return "TessControl";
      case ShaderType::Compute: return "Compute";
    }
    return "Invalid";
  }
}