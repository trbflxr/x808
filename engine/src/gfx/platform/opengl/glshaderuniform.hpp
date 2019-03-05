//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLSHADERUNIFORM_HPP
#define X808_GLSHADERUNIFORM_HPP


#include <xe/gfx/shaderuniform.hpp>
#include <xe/string.hpp>

namespace xe { namespace internal {

	class GLShaderUniform : public ShaderUniform {
	private:
		friend class GLBaseShader;
		friend class GLShaderUniformBuffer;

	public:
		enum class Type {
			None, Int32, Float32, Vec2, Vec3, Vec4, Mat4, Image2D, Image3D, Struct
		};

	public:
		explicit GLShaderUniform(Type type, const string &name, uint count = 1);
		explicit GLShaderUniform(ShaderStruct *uniformStruct, const string &name, uint count = 1);

		inline const string &getName() const override { return name; }
		inline uint getSize() const override { return size; }
		inline uint getCount() const override { return count; }
		inline uint getOffset() const override { return offset; }
		inline uint getAbsoluteOffset() const { return struct_ ? struct_->getOffset() + offset : offset; }

		int32 getLocation() const { return location; }
		inline Type getType() const { return type; }
		const ShaderStruct &getShaderUniformStruct() const;

		static uint sizeOfUniformType(Type type);
		static Type stringToType(const string &type);
		static string typeToString(Type type);

	protected:
		void setOffset(uint offset) override;

	private:
		Type type;
		string name;
		uint count;

		uint size;
		uint offset;

		ShaderStruct *struct_;
		mutable int32 location;
	};

	///------------------------------///
	class GLShaderUniformBuffer : public ShaderUniformBuffer {
	public:
		explicit GLShaderUniformBuffer(const string &name);

		void pushUniform(GLShaderUniform *uniform);

		void clear() override { uniforms.clear(); }

		inline const string &getName() const override { return name; }
		inline int32 getLocation() const override { return location; }
		inline uint getSize() const override { return size; }
		inline const ShaderUniformVec &getUniforms() const override { return uniforms; }

		ShaderUniform *findUniform(const string &name) override;

	private:
		string name;
		uint size;
		uint location;
		ShaderUniformVec uniforms;
	};
	typedef std::vector<ShaderUniformBuffer *> ShaderUniformBufferVec;

}}


#endif //X808_GLSHADERUNIFORM_HPP
