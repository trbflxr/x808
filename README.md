![x808 logo](/logo.png)

## x808

x808 is a cross-platform, high performance game engine currently in development. This readme will be updated with more info eventually.


#### Free and open source

x808 is completely free and open source under the MIT license.


#### Compiling from source

* Get sources from GitHub
* Run **spak_exec.exe** utility via command line with argument **-gl**. It will create shader package.
```sh
  $ spak_exec.exe -gl
```
* Build project with CMake.

#### Use like an library

Check out CMakeLists.txt in **sandbox** project.

#### Shell

Fully functional shell with command history and autocompletion.
![sh0](/shell0.png)

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

![2d](/2d.png)

Sandbox 3D: Sponza test.

![3d0](/3d.png)

![3d1](/3dwireframe.png)

![3d2](/3dlightvolumes.png)

![3d3](/3dbuffers.png)
