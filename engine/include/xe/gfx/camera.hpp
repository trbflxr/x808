//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_CAMERA_HPP
#define X808_CAMERA_HPP


#include <xe/gameobject.hpp>

namespace xe {

	class Camera : public ITransformable {
	public:
		explicit Camera(const mat4 &projection) :
				projection(projection), view(1.0f), entity(nullptr) { }

		~Camera() override = default;

		virtual void update() const {
			if (entity) {
				const mat4 rotation = quat::conjugate(entity->getRotation()).toMatrix();
				const mat4 translation = mat4::translation(-entity->getPosition());
				view = rotation * translation;
			} else {
				const mat4 rotation = quat::conjugate(getRotation()).toMatrix();
				const mat4 translation = mat4::translation(-getPosition());
				view = rotation * translation;
			}
			toMatrix();
		}

		inline void hookEntity(GameObject *entity) {
			Camera::entity = entity;
			update();
		}

		inline void unhookEntity() {
			entity = nullptr;
			update();
		}

		inline const mat4 &getProjection() const { return projection; }
		inline void setProjection(const mat4 &matrix) { projection = matrix; }

		inline const mat4 &getView() const {
			if (isDirty()) {
				update();
			}
			return view;
		}

	private:
		mutable mat4 projection;
		mutable mat4 view;

		GameObject *entity;
	};

}


#endif //X808_CAMERA_HPP
