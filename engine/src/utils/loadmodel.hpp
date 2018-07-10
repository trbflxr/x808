//
// Created by FLXR on 7/10/2018.
//

#ifndef X808_LOADMODEL_HPP
#define X808_LOADMODEL_HPP


#include <string>
#include <vector>
#include "common.hpp"
#include "gfx/indexedmodel.hpp"

namespace xe { namespace utils {

	XE_API bool loadModels(const std::string_view &path, std::vector<gfx::IndexedModel> &models);

}}


#endif //X808_LOADMODEL_HPP
