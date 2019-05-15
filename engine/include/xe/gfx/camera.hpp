//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_CAMERA_HPP
#define X808_CAMERA_HPP


#include <xe/math/itransformable.hpp>

namespace xe {

  class Camera : public ITransformable {
  public:
    explicit Camera(const mat4 &projection) :
        ITransformable(false),
        projection(projection), view(1.0f) { }

    inline const mat4 &getProjection() const { return projection; }
    inline void setProjection(const mat4 &matrix) { projection = matrix; }

    inline const mat4 &getView() const {
      if (isDirty()) {
        const mat4 rotation = quat::conjugate(getRotation()).toMatrix();
        const mat4 translation = mat4::translation(-getPosition());
        view = rotation * translation;
      }
      return view;
    }

  private:
    mutable mat4 projection;
    mutable mat4 view;
  };

}


#endif //X808_CAMERA_HPP
