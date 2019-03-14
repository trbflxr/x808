//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_SHADERMANAGER_HPP
#define X808_SHADERMANAGER_HPP


#include <xe/gfx/shader.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/config.hpp>

namespace xe {

	class XE_API ShaderManager : NonCopyable {
	public:
		~ShaderManager() override;

		static void init(const Config &config);

		static bool add(Shader *shader);
		static const Shader *get(const string &name);
		static const string &getSource(const string &name);

		static void clean();

		static const std::unordered_map<string, const Shader *> &getShaders() { return instance().shaders; }
		static const std::unordered_map<string, string> &getSources() { return instance().sources; }

	private:
		ShaderManager();

		static ShaderManager &instance();

		void setConstants(const Config &config);

		void createDefaultShaders();
		void createGLShaders();

	private:
		std::unordered_map<string, const Shader *> shaders;
		std::unordered_map<string, string> sources;
	};

}

#define GETSHADER(name) xe::ShaderManager::get(name)

#endif //X808_SHADERMANAGER_HPP
