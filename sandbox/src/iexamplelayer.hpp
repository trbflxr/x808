//
// Created by FLXR on 5/17/2019.
//

#ifndef X808_IEXAMPLELAYER_HPP
#define X808_IEXAMPLELAYER_HPP


#include <xe/gfx/layer.hpp>

#define IEXAMPLE_LAYER_METHODS(className) \
void destroyInstance() override { className::destroy(); } \
inline void *raw() override { return this; } \
static className *create(){\
  if (!instance) {\
    instance = new className();\
  }\
  return instance;\
}\
static void destroy(){\
  delete instance;\
  instance = nullptr;\
}\

class IExampleLayer : public xe::Layer {
public:
  virtual void destroyInstance() = 0;
  virtual void *raw() = 0;
};


#endif //X808_IEXAMPLELAYER_HPP
