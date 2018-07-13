//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "gfx/camera/camera.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "model.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRenderer {
	public:
		explicit ForwardRenderer();
		~ForwardRenderer();

		inline void setAmbientLight(AmbientLight *light) { ambientLight = light; }
		inline void addLight(BaseLight *light) { lights.push_back(light); }

		void render(const Model *model, const Camera *camera);

	private:
		std::vector<BaseLight *> lights;
		AmbientLight *ambientLight;
	};

}}


#endif //X808_FORWARDRENDERER_HPP
