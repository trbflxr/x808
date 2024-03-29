//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_GLSHADERFILE_HPP
#define X808_GLSHADERFILE_HPP


#include <sstream>
#include <xe/resources/shaderfile.hpp>

namespace xe::internal {

  class GLShaderFile : public ShaderFile {
  public:
    explicit GLShaderFile(ShaderType type, const string &source);

    explicit GLShaderFile(ShaderType type, const string &source,
                          const std::vector<string> &dependenciesSource,
                          const std::vector<string> &extensions,
                          bool fromSource = true);

    inline ShaderType getType() const override { return type; }
    inline const string &getSource() const override { return source; }

    static void parse(const string &source,
                      ShaderUniformBufferVec &buffers,
                      ShaderSamplerVec &samplers,
                      ShaderStructVec &structs);

    static void parseUniform(const string &statement,
                             ShaderUniformBufferVec &buffers,
                             ShaderSamplerVec &samplers,
                             ShaderStructVec &structs);

    static void parseUniformStruct(const string &block, ShaderStructVec &structs);

  private:
    void appendConstants(std::stringstream &stream);
    void appendExtensions(std::stringstream &stream, const std::vector<string> &extensions);
    void appendDependencies(std::stringstream &stream, const std::vector<string> &dependencies);

    void createFromSource(const string &src, const std::vector<string> &dep, const std::vector<string> &ext);
    void createFromFile(const string &path, const std::vector<string> &dep, const std::vector<string> &ext);

  private:
    ShaderType type;

    string source;
  };

}


#endif //X808_GLSHADERFILE_HPP
