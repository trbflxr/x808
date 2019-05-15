//
// Created by FLXR on 8/6/2018.
//

#include <xe/gfx/context.hpp>
#include <xe/string.hpp>
#include <xe/loaders/shaderloader.hpp>
#include <xe/utils/assert.hpp>
#include "glshaderfile.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"
#include "glshadersampler.hpp"
#include "glshaderuniform.hpp"

namespace xe::internal {

  GLShaderFile::GLShaderFile(ShaderType type, const string &source) :
      type(type),
      source(source) { }

  GLShaderFile::GLShaderFile(ShaderType type, const string &source,
                             const std::vector<string> &dependenciesSource,
                             const std::vector<string> &extensions,
                             bool fromSource) :
      type(type) {

    if (fromSource) {
      createFromSource(source, dependenciesSource, extensions);
    } else {
      createFromFile(source, dependenciesSource, extensions);
    }
  }

  void GLShaderFile::createFromSource(const string &src,
                                      const std::vector<string> &dep,
                                      const std::vector<string> &ext) {
    std::stringstream shaderSource;
    std::stringstream shaderAdditions;

    appendConstants(shaderAdditions);
    appendExtensions(shaderAdditions, ext);
    appendDependencies(shaderAdditions, dep);

    shaderSource << shaderAdditions.str() << "\n";
    shaderSource << src;

    source = shaderSource.str();
  }

  void GLShaderFile::createFromFile(const string &path,
                                    const std::vector<string> &dep,
                                    const std::vector<string> &ext) {

    const string src = ShaderLoader::load(path);

    std::vector<string> dependenciesSource(dep.size());
    for (const auto &d : dep) {
      dependenciesSource.emplace_back(ShaderLoader::load(d));
    }

    std::stringstream shaderSource;
    std::stringstream shaderAdditions;

    appendConstants(shaderAdditions);
    appendExtensions(shaderAdditions, ext);
    appendDependencies(shaderAdditions, dependenciesSource);

    shaderSource << shaderAdditions.str() << "\n";
    shaderSource << src;

    source = shaderSource.str();
  }

  void GLShaderFile::appendConstants(std::stringstream &stream) {
    //constants
    static const char *MATH_PI = "#define MATH_PI 3.1415926535897932384626433832795";
    static const char *MATH_HALF_PI = "#define MATH_HALF_PI 1.57079632679489661923132169163975";
    static const char *MATH_2_PI = "#define MATH_2_PI 6.283185307179586476925286766559";

    stream << "#version " << Context::getRenderAPIVersion() << "\n";
    stream << MATH_PI << "\n";
    stream << MATH_HALF_PI << "\n";
    stream << MATH_2_PI << "\n ";
  }

  void GLShaderFile::appendExtensions(std::stringstream &stream, const std::vector<string> &extensions) {
    std::stringstream shaderExtensions;

    //extensions
    if (!extensions.empty()) {
      for (auto &&extension : extensions) {
        shaderExtensions << extension << "\n";
      }
    }

    stream << shaderExtensions.str() << "\n";
  }

  void GLShaderFile::appendDependencies(std::stringstream &stream, const std::vector<string> &dependencies) {
    if (!dependencies.empty()) {
      for (const auto &d : dependencies) {
        stream << "\n" << d;
      }
    }
  }

  void GLShaderFile::parse(const string &source,
                           ShaderUniformBufferVec &buffers,
                           ShaderSamplerVec &samplers,
                           ShaderStructVec &structs) {

    const char *token;
    const char *sourcePtr;

    //structs
    sourcePtr = source.c_str();
    while ((token = findToken(sourcePtr, "struct"))) {
      parseUniformStruct(getBlock(token, &sourcePtr), structs);
    }

    //uniforms
    sourcePtr = source.c_str();
    while ((token = findToken(sourcePtr, "uniform"))) {
      parseUniform(getStatement(token, &sourcePtr), buffers, samplers, structs);
    }
  }

  void GLShaderFile::parseUniform(const string &statement,
                                  ShaderUniformBufferVec &buffers,
                                  ShaderSamplerVec &samplers,
                                  ShaderStructVec &structs) {

    std::vector<string> tokens = tokenize(statement);
    uint index = static_cast<uint>(tokens.size() - 1);

    if (tokens[2][0] == '{') return; // uniform buffer

    string name = tokens[index--];
    string typeStr = tokens[index];

    // Strip ; from Name if present
    if (const char *s = strstr(name.c_str(), ";")) {
      name = string(name.c_str(), s - name.c_str());
    }

    string n(name);
    uint count = 1;
    const char *nameStr = n.c_str();

    if (const char *s = strstr(nameStr, "[")) {
      name = string(nameStr, s - nameStr);

      const char *end = strstr(nameStr, "]");
      string c(s + 1, end - s);
      count = static_cast<uint>(atoi(c.c_str()));
    }

    if (GLShaderSampler::isTypeStrSampler(typeStr)) {
      auto *decl = new GLShaderSampler(GLShaderSampler::stringToType(typeStr), name, count);
      samplers.push_back(decl);
    } else {
      GLShaderUniform::Type t = GLShaderUniform::stringToType(typeStr);
      GLShaderUniform *uniform = nullptr;

      if (t == GLShaderUniform::Type::None) {
        // Find struct
        ShaderStruct *s = nullptr;
        for (auto &&st : structs) {
          if (st->getName() == typeStr) {
            s = st;
            break;
          }
        }

        if (!s) {
          XE_CORE_FATAL("[GLShaderFile]: Could not find struct:", typeStr.c_str(), " ", name.c_str());
          XE_ASSERT(false);
        }

        uniform = new GLShaderUniform(s, name, count);
      } else {
        uniform = new GLShaderUniform(t, name, count);
      }

      dynamic_cast<GLShaderUniformBuffer *>(buffers.front())->pushUniform(uniform);
    }
  }

  void GLShaderFile::parseUniformStruct(const string &block, ShaderStructVec &structs) {
    std::vector<string> tokens = tokenize(block);

    uint index = 1; // struct

    string name = tokens[index++];
    ShaderStruct *uniformStruct = new ShaderStruct(name);

    index++; // {
    while (index < tokens.size()) {
      if (tokens[index] == "}") break;

      string type = tokens[index++];
      name = tokens[index++];

      // Strip ; from shaderName if present
      if (const char *s = strstr(name.c_str(), ";")) {
        name = string(name.c_str(), s - name.c_str());
      }

      uint count = 1;
      const char *namestr = name.c_str();
      if (const char *s = strstr(namestr, "[")) {
        const char *end = strstr(namestr, "]");
        string c(s + 1, end - s);
        count = static_cast<uint>(atoi(c.c_str()));
        name = string(namestr, s - namestr);
      }

      auto *field = new GLShaderUniform(GLShaderUniform::stringToType(type), name, count);
      uniformStruct->addField(field);
    }

    structs.push_back(uniformStruct);
  }

}