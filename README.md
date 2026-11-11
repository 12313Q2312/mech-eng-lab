# Mechanical Engineering Lab

**把数学推导、C++ 实现与实验结果放在同一份可继续推进的工程档案里。**

本仓库记录机械工程相关的计算与编程实验：从最小构建环境，到二维向量、矩阵和旋转，再到物理推导与实验复盘。每个实验保留实现和原始资料，便于复现、比较与后续扩展。

## 工程作品与思考

从[工程作品索引](docs/portfolio/README.md)查看单片机、机器人状态模拟和本仓库的坐标系实验。索引把每个项目的问题、关键判断、运行证据与验证范围放在一起。

新知识点用[项目卡](docs/portfolio/PROJECT-CARD.md)记录预测、实现和验证。第一份示例是[平面坐标系与位姿变换](projects/planar-frames/README.md)，用一个可手算的反例检查旋转和平移的顺序。接着把同一套变换用于[二连杆机械臂](projects/two-link-arm/README.md)，从关节角计算末端位置。

## 实验地图

| 实验 / 资料 | 要解决的问题 | 入口与已有证据 |
|---|---|---|
| 二维线性代数 | 用 `Vec2`、`Mat2` 表达向量运算、旋转与矩阵复合 | [源码与 VS 工程](projects/day01-linear-algebra/day01-linear-algebra/)；已有数值输出核对 |
| Hello Engine World | 建立最小 C++17 / CMake 构建闭环 | [实验源码](<projects/hello world/day01-hello-world/>)；已有干净构建与运行记录 |
| 单摆仿真 | 比较两个步长下的能量漂移 | [实现与实测](projects/pendulum/README.md) |
| 抽题覆盖率 | 比较两种抽样策略的覆盖与重复 | [脚本与 30 种子结果](projects/question-sampling/README.md) |
| 拉格朗日力学推导 | 保存物理理解与手写推导的上下文 | [推导图片](docs/physics/day-01/) |
| 工具链复盘 | 记录编译器、生成器、终端与 Git 的实际问题 | [Day 01 日志](docs/log/day-01.md)、[原始截图](docs/screenshots/) |

`docs/math/`、`tools/` 等目录目前包含预留位置，不能据此推断已有额外实验或工具。

## 复现第一个实验

需要 **CMake 3.15+** 和支持 **C++17** 的编译器。在仓库根目录执行：

```sh
cmake -S "projects/hello world/day01-hello-world" -B build/hello
cmake --build build/hello
./build/hello/hello
```

预期输出：`Hello, Engine World!`。

Windows Visual Studio 生成器使用：

```powershell
cmake -S "projects/hello world/day01-hello-world" -B build/hello
cmake --build build/hello --config Release
.\build\hello\Release\hello.exe
```

## 运行二维线性代数实验

Windows 可打开原有 [Visual Studio solution](projects/day01-linear-algebra/day01-linear-algebra/day01-linear-algebra.slnx)。Linux / GCC 可以直接编译现有三个源文件：

```sh
mkdir -p build/linear
g++ -std=c++17 \
  projects/day01-linear-algebra/day01-linear-algebra/main.cpp \
  projects/day01-linear-algebra/day01-linear-algebra/vec2.cpp \
  projects/day01-linear-algebra/day01-linear-algebra/mat2.cpp \
  -o build/linear/linear_demo
./build/linear/linear_demo
```

观察旋转结果、点积以及矩阵复合是否符合预期。现有源码仍调用 Windows 的 `system("pause")`，Linux 会出现命令不存在的提示；数值输出和平台行为应分别检查。

## 已有验证

2026-11-03，Linux GCC 环境下：

- Hello World 从干净导出完成配置、编译和运行。
- 线性代数示例编译并运行；90° 旋转、点积 `5`、`R90 × R45 = R135` 的输出在 `1e-5` 容差内核对。
- 清理前后的源码、工程文件、笔记、图片与截图保留原始 Git blob。

详细证据见 [验证与清理记录](docs/hygiene-20261103.md)。当前程序输出中出现“expect”只表示示例给出预期值，尚未构成自动断言测试；Windows 工程尚未实测。

## 如何积累下一次实验

每个实验保留五项信息：**问题、预期、实现、实际结果、差异与下一步**。先将推导变成可观察的预测，再用最小实现取得反馈。

后续可优先将现有旋转与矩阵运算转成可重复的断言检查，再逐步加入与机械系统相关的计算实验。源码、推导和原始图片共同构成实验资产；缓存与编译输出由 `.gitignore` 排除。

项目负责人决定方向与验收标准，AI 工程助手负责实现、验证和文档维护。所有修改通过独立分支、Git 提交和人工审核积累。
