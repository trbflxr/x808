//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_SHADERMANAGER_HPP
#define X808_SHADERMANAGER_HPP


#include <unordered_map>
#include <string>
#include <gfx/api/shader.hpp>
#include "common.hpp"
#include "utils/noncopyable.hpp"

namespace xe {

	class XE_API ShaderManager : NonCopyable {
	public:
		~ShaderManager() override;

		static void add(api::Shader *shader);
		static api::Shader *get(const std::string_view &name);

		static void clean();

	private:
		ShaderManager();

		void createDefaultShaders();

		void createDefaultCommonShaders();
		void createDefaultFinalShaders();

		static ShaderManager &instance();

	private:
		std::unordered_map<std::string, api::Shader *> shaders;
	};

}

#define GETSHADER(name) xe::ShaderManager::get(name)

#endif //X808_SHADERMANAGER_HPP
