# nlohmann_json_learn
learn nlohmann json

在这个[地址](https://github.com/nlohmann/json/releases) 下载 include.zip, 然后将压缩包中的 include/nlohmann 或者 single_include/nlohmann 目录放到项目的 include 目录下即可。

目录结构为

```
├─include
│  └─nlohmann
│    └─...
├─.gitignore
├─CMakeLists.txt
├─main.cpp
├─main.h
├─lib.cpp
├─lib.h
...
```

编译命令

```base
mkdir build && cd build
cmake ../
cmake --build ./ -j 8 --config Release
cmake --install ./ --config Release
```
