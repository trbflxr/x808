//
// Created by FLXR on 7/3/2018.
//

#include "texturemanager.hpp"
#include "utils/log.hpp"
#include "gfx/api/texture2d.hpp"
#include "../../embedded/embedded.hpp"

xe::TextureManager::TextureManager() {
	using namespace gfx::api;

	TextureParameters params(TextureFilter::NEAREST);

	Texture2D *texture = new Texture2D(internal::DEFAULT_TEXTURE_WIDTH,
	                                   internal::DEFAULT_TEXTURE_HEIGHT, params);
	texture->setData(internal::DEFAULT_TEXTURE);

	textures.emplace("default", texture);
}

xe::TextureManager::~TextureManager() {
	clean();
}

xe::TextureManager &xe::TextureManager::instance() {
	static TextureManager tm;
	return tm;
}

void xe::TextureManager::add(xe::gfx::api::Texture *texture) {
	auto &&it = instance().textures.find(texture->getName());

	if (it != instance().textures.end()) {
		XE_ERROR(texture->getName(), " already exist!");
		return;
	}

	instance().textures.emplace(texture->getName(), texture);
}

const xe::gfx::api::Texture &xe::TextureManager::get(const std::string_view &name) {
	auto &&it = instance().textures.find(name.data());
	if (it == instance().textures.end()) {
		XE_ERROR("Texture '", name, "' not found!");

		return get("default");
	}

	return *it->second;
}

void xe::TextureManager::clean() {
	instance().textures.clear();
}
