# mech-eng-lab

机械工程、数学与 C++ 实验档案。保留实验源码、手写推导、截图和学习记录，让每个实验可以定位、复现和继续扩展。

## 实验与资料索引

| 入口 | 当前内容 |
|---|---|
| [二维线性代数](projects/day01-linear-algebra/day01-linear-algebra/) | Vec2、Mat2、旋转与矩阵乘法示例；保留 Visual Studio 工程 |
| [Hello Engine World](<projects/hello world/day01-hello-world/>) | 最小 C++17 / CMake 程序 |
| [Day 01 复盘](docs/log/day-01.md) | 原有学习与实验记录 |
| [物理推导](docs/physics/day-01/) | 原有拉格朗日力学图片 |
| [实验截图](docs/screenshots/) | 原有运行截图 |
| [整理与验证记录](docs/hygiene-20261103.md) | 清理清单、实际验证与恢复说明 |

保留原目录名称与占位文件，现有图片、链接和学习上下文不因整理而移动。

## 复现

Hello World，在仓库根目录执行（路径含空格，需要引号）：

```sh
cmake -S "projects/hello world/day01-hello-world" -B build/hello
cmake --build build/hello
./build/hello/hello
```

Windows Visual Studio 生成器使用 --config Release，输出通常位于 build/hello/Release/hello.exe。

二维线性代数：Windows 可打开原有 .slnx / .vcxproj；Linux 可直接编译现有源码：

```sh
mkdir -p build/linear
g++ -std=c++17 "projects/day01-linear-algebra/day01-linear-algebra/main.cpp" "projects/day01-linear-algebra/day01-linear-algebra/vec2.cpp" "projects/day01-linear-algebra/day01-linear-algebra/mat2.cpp" -o build/linear/linear_demo
./build/linear/linear_demo
```

该示例仍有 Windows 的 system("pause")；Linux 运行可能报告 pause 不存在。本轮不修改数学源码或平台行为，具体运行结果见验证记录。示例打印“expect”并不等于具有自动断言的测试套件。

## 文件维护

只将源文件、工程配置、必要数据、笔记和验证证据纳入版本控制。编译目录、VS 缓存与调试数据库由 .gitignore 排除。下一次实验可补充“目标、预期、实际输出、差异与下一步”，不以提交数量作为成果。
