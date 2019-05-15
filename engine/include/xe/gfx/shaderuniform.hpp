//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERUNIFORM_HPP
#define X808_SHADERUNIFORM_HPP


#include <vector>
#include <xe/string.hpp>
#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {

  class ShaderUniform {
  private:
    friend class ShaderStruct;

  public:
    virtual ~ShaderUniform() = default;
    virtual const string &getName() const = 0;
    virtual uint getSize() const = 0;
    virtual uint getCount() const = 0;
    virtual uint getOffset() const = 0;

  protected:
    virtual void setOffset(uint offset) = 0;
  };
  typedef std::vector<ShaderUniform *> ShaderUniformVec;


  ///---------------------------///
  class ShaderUniformBuffer {
  public:
    virtual ~ShaderUniformBuffer() = default;
    virtual const string &getName() const = 0;
    virtual int32 getLocation() const = 0;
    virtual uint getSize() const = 0;
    virtual const ShaderUniformVec &getUniforms() const = 0;

    virtual ShaderUniform *findUniform(const string &name) = 0;

    virtual void clear() = 0;
  };
  typedef std::vector<ShaderUniformBuffer *> ShaderUniformBufferVec;


  ///---------------------------///
  class ShaderStruct {
  public:
    explicit ShaderStruct(const string &name) : name(name), size(0), offset(0) { }
    virtual ~ShaderStruct() = default;

    void addField(ShaderUniform *field) {
      size += field->getSize();
      uint offset = 0;
      if (!fields.empty()) {
        ShaderUniform *previous = fields.back();
        offset = previous->getOffset() + previous->getSize();
      }
      field->setOffset(offset);
      fields.push_back(field);
    }

    inline void setOffset(uint offset) { ShaderStruct::offset = offset; }

    inline const string &getName() const { return name; }
    inline uint getSize() const { return size; }
    inline uint getOffset() const { return offset; }
    inline const std::vector<ShaderUniform *> &getFields() const { return fields; }

  private:
    string name;
    std::vector<ShaderUniform *> fields;
    uint size;
    uint offset;
  };
  typedef std::vector<ShaderStruct *> ShaderStructVec;

}


#endif //X808_SHADERUNIFORM_HPP
