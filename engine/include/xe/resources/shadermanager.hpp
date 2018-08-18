//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_SHADERMANAGER_HPP
#define X808_SHADERMANAGER_HPP


#include <unordered_map>
#include <xe/gfx/baseshader.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/utils/string.hpp>

namespace xe {

	class XE_API ShaderManager : NonCopyable {
	public:
		~ShaderManager() override;

		static void add(BaseShader *shader);
		static BaseShader *get(const string &name);
		static const string &getSource(const string &name);

		static void clean();

	private:
		ShaderManager();

		void createDefaultShaders();

		static ShaderManager &instance();

	private:
		std::unordered_map<string, BaseShader *> shaders;
		std::unordered_map<string, string> sources;
	};

}

#define GETSHADER(name) xe::ShaderManager::get(name)

#endif //X808_SHADERMANAGER_HPP
