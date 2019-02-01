//
// Created by FLXR on 9/29/2018.
//

#ifndef X808_SHADERLOADER_HPP
#define X808_SHADERLOADER_HPP


#include <xe/common.hpp>
#include <xe/string.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	struct XE_API ShaderLoader : NonCopyable {
		static string load(const string &path);
		static string load(const char *path);
	};

}

#endif //X808_SHADERLOADER_HPP
