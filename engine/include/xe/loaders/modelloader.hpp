//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_MODELLOADER_HPP
#define X808_MODELLOADER_HPP


#include <xe/gfx/model.hpp>
#include <xe/utils/noncopyable.hpp>

class aiNode;
class aiScene;

namespace Assimp {
  class Importer;
}

namespace xe {

  class XE_API ModelLoader : NonCopyable {
  public:
    ~ModelLoader() override;

    static IndexedModel *loadIndexedModel(const string &file);
    static bool loadModel(Model *model, const string &file);

  private:
    explicit ModelLoader();
    static ModelLoader &get();

    static const aiScene *loadScene(Assimp::Importer *importer, const string &file);

  private:
    Assimp::Importer *importer;

    static constexpr const char *basePath = u8"/models/";
  };

}


#endif //X808_MODELLOADER_HPP
