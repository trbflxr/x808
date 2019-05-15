//
// Created by FLXR on 8/17/2018.
//

#include <ctime>
#include <cstring>
#include <xetools/spak.hpp>

static const char *defaultGLSrc = "engine/src/gfx/platform/opengl/shaders";
static const char *defaultDest = "pack001.pak";

void printUsage() {
  printf("Usage:\n");
  printf("\tDefault for OpenGL: spak_exec.exe -gl\n");
  printf("\tsrc = '%s', dest = '%s'\n\n", defaultGLSrc, defaultDest);
  printf("\tCustom: spak_exec.exe <shader dir> (<dest dir>)\n");
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    printUsage();
    return 0;
  }

  const char *src;
  const char *dest;

  if (strcmp(argv[1], "-gl") == 0) {
    src = defaultGLSrc;
    dest = defaultDest;
  } else if (argc == 2) {
    src = argv[1];
    dest = defaultDest;
  } else if (argc == 3) {
    src = argv[1];
    dest = argv[2];
  } else {
    printUsage();
    return 0;
  }

  printf("src: %s\n", src);
  printf("dest: %s\n", dest);

  xe::spak::packShaders(src, dest);

  time_t rawTime;
  struct tm *timeInfo;

  time(&rawTime);
  timeInfo = localtime(&rawTime);

  printf("packed: %s\n", asctime(timeInfo));

  return 0;
}
