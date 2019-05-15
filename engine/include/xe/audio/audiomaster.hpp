//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOMASTER_HPP
#define X808_AUDIOMASTER_HPP


#include <xe/string.hpp>
#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

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

    static void setDistanceModel(DistanceModel model);

    static std::vector<string> getDeviceList();

  private:
    ~AudioMaster() override;

    static AudioMaster &get();

  private:
    void *context;
    void *device;
  };
}


#endif //X808_AUDIOMASTER_HPP
