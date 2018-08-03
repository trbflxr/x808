//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERRESOURCE_HPP
#define X808_SHADERRESOURCE_HPP


#include <vector>
#include <string>
#include "xeint.hpp"

namespace xe { namespace api {

	class ShaderResource {
	public:
		virtual const std::string &getName() const = 0;
		virtual uint getRegister() const = 0;
		virtual uint getCount() const = 0;
	};
	typedef std::vector<ShaderResource *> ShaderResourceVec;

}}


#endif //X808_SHADERRESOURCE_HPP
