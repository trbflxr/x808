//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOMASTER_HPP
#define X808_AUDIOMASTER_HPP


#include <xe/string.hpp>
#include <xe/common.hpp>
#include <xe/math/vec3.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  class Camera;

  enum class DistanceModel {
    Inverse = 0,
    InverseClamped,
    Linear,
    LinearClamped,
    Exponent,
    ExponentClamped
  };

  class XE_API AudioMaster : NonCopyable {
  public:
    static void initialize();

    static void update(const Camera *camera);

    static void setDistanceModel(DistanceModel model);

    static std::vector<string> getDeviceList();

    static void setUpVector(const vec3 &up) { get().up = up; }

  private:
    explicit AudioMaster();
    ~AudioMaster() override;

    static AudioMaster &get();

  private:
    void *context;
    void *device;

    vec3 up;
  };
}


#endif //X808_AUDIOMASTER_HPP
