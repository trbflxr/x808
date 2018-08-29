//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_CAMERA_HPP
#define X808_CAMERA_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gameobject.hpp>

namespace xe {

	class XE_API Camera : public GameObject {
	public:
		explicit Camera(const mat4 &projection) :
				projection(projection), view(1.0f), entity(nullptr) { }

		virtual void update() {
			if (entity) {
				memcpy(&transform, &entity->transform, sizeof(Transform));
			}

			mat4 rotation = quat::conjugate(transform.getRotation()).toMatrix();
			mat4 translation = mat4::translation(-transform.getPosition());
			view = rotation * translation;

			transform.setDirty(false);
		}

		inline void hookEntity(GameObject *entity) {
			Camera::entity = entity;
			update();
		}

		inline void unhookEntity() {
			entity = nullptr;
		}

		inline const mat4 &getProjection() const { return projection; }
		inline void setProjection(const mat4 &matrix) { Camera::projection = matrix; }

		inline const mat4 &getViewMatrix() {
			if (transform.isDirty()) {
				update();
			}
			return view;
		}

		inline mat4 getViewProjection() {
			if (transform.isDirty()) {
				update();
			}
			return projection * view;
		}

	private:
		GameObject *entity;

		mat4 projection;
		mat4 view;
	};

}


#endif //X808_CAMERA_HPP
