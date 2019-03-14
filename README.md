![x808 logo](/_md/logo.png)

## x808

x808 is a cross-platform, high performance game engine currently in development. This readme will be updated with more info eventually.


#### Free and open source

x808 is completely free and open source under the MIT license.


#### Compiling from source

* Get sources from GitHub
* Build spak (engine\tools)
* Run **spak.exe** utility via command line with argument. It will create shader package.
```sh
  $ spak.exe engine\src\gfx\platform\opengl\shaders
```
* Build project with CMake.

#### Use like an library

Check out CMakeLists.txt in **sandbox** project.

#### Shell

Fully functional shell with command history and autocompletion.
![sh0](/_md/shell0.png)

**Adding shell command**

```c++
Shell &shell = app.getShell();

auto func = [&](const std::vector<string> &args, bool hint) -> string {
  if (hint) return "Command description";
  string r = "Hello " + args[0];
  return r;
};

shell.addCommand("cmd", func);
```

#### Screenshots

Sandbox 2D: Performance test.

![2d](/_md/2d.png)

### 3D stuff

GBuffer:
![gbuffer](/_md/gbuffer.png)

Light volumes:
![lw](/_md/lights.png)

Wireframe:
![lw](/_md/wireframe.png)

Specular map:
![specularmap](/_md/specular.png)

Normal map:
![specularmap](/_md/normals.png)

### Shadows

Work in progress...

Spot light shadows:
![specularmap](/_md/spotshadows.png)

Directional light cascaded shadows:
![specularmap](/_md/cascadedshadows.png)
