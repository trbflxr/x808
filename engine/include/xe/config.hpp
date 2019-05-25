//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_CONFIG_HPP
#define X808_CONFIG_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {

  class XE_API Config {
  public:
    uint width;
    uint height;
    uint fullScreen;
    bool vSync;

    uint maxFps;
    uint tickRate;

    bool srgb;

    RenderAPI renderApi;
    uint apiVersion;

    uint maxSpotShadows;
    uint maxDirectionalCascades;
    uint shadowQuality;

  public:
    explicit Config() :
        width(1),
        height(1),
        fullScreen(0),
        vSync(false),
        maxFps(0),
        tickRate(30),
        srgb(true),
        renderApi(RenderAPI::OpenGL),
        apiVersion(330),
        maxSpotShadows(1),
        maxDirectionalCascades(3),
        shadowQuality(3) { }

    static inline const Config &get() {
      if (!cfg) cfg = new Config();
      return *cfg;
    }

  private:
    static Config *cfg;
  };

}


#endif //X808_CONFIG_HPP
