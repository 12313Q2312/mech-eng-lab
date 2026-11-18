# ResearchOS · Reproducible AI & Engineering Workstation

> **V0.1 alpha.** An Ubuntu-based workstation blueprint and a working research CLI. **Not a standalone Linux distribution or bootable ISO yet.**  
> **V0.1 测试版。** 基于 Ubuntu 的可复现科研工程工作站与可运行命令行工具；**尚不是独立发行版/可启动 ISO**。

ResearchOS aims to make it easier to repeat engineering experiments and rebuild workstations consistently. Its current focus: AI research (KAN/PyTorch), C++ engineering, robotics readiness, and experiment evidence. It intentionally does **not** replace Windows-only CAD tools.

ResearchOS 希望让科研人员更快构建工作环境、可靠复现实验、保存验证证据，而不是在每台机器上重复手动配置。

## What works today / V0.1 已实现

- `researchos doctor`：查看最小机器配置，不显示用户名或主机名。
- `researchos init NAME`：按固定结构创建可运行的科研项目；同名目录已存在时拒绝覆盖。
- `researchos run PROJECT -- COMMAND...`：执行一次实验，并在项目内保存 stdout/stderr、退出码、耗时、内核与 Python 信息；能读到 Git 提交时一并记录。
- 默认只预览的安装脚本，配置档为 `core`、`ai`、`robotics`。不带 `--apply` 时不调用 APT，也不复制 CLI。
- `tests/test_cli.py` 里的单元测试，只使用 Python 标准库。
- 本仓库根目录的 [`.github/workflows/research-os.yml`](../../.github/workflows/research-os.yml)：权限只有 `contents: read`。仅当 `projects/research-os/**` 有改动，或手动 `workflow_dispatch` 时，在 Ubuntu 上运行 `bash -n`、ShellCheck、安装脚本预览和上述单元测试。预览步骤不会传入 `--apply`。

`projects/research-os/.github/workflows/ci.yml` 仍留在子目录中，便于以后放到独立仓库的根目录。GitHub 不会执行子目录里的工作流，所以那个文件本身不是 CI 证据。

## What is missing / V0.1 尚未具备

- 不是 Linux 发行版，没有可启动 ISO，也没有自定义内核。
- 安装脚本不改分区、不安装或修改 GRUB/UEFI、不改 `/etc/fstab`，也不覆盖用户已有系统。
- 没有完整桌面主题、浏览器或环境迁移、GPU/CUDA 安装程序、ROS 2 安装程序。
- 没有签名发布包、回滚说明、性能声明或硬件兼容矩阵。
- Ubuntu、GNOME、ROS 2、PyTorch 和其他上游软件仍是第三方项目，许可证各自独立。

## Freeze / V0.1 冻结

V0.1 到此冻结。`projects/research-os/` 保留现有 CLI、预览安装脚本、测试和文档，不再在 `mech-eng-lab` 里继续加功能。这次收尾只补上 GitHub 能真正触发的根目录检查，并写明边界。

**是否迁到独立仓库，由 Founder 决定。** 本变更不新建仓库，不合并到 `main`，也不代替这个决定。

## Quick start / 快速开始

On an **already installed Ubuntu 26.04 LTS Desktop** machine (Ubuntu 24.04 LTS also supported):

```bash
# Clone the ResearchOS source repository or extract the release ZIP.
cd ResearchOS-v0.1
bash scripts/install.sh --profile core        # dry-run: no changes
bash scripts/install.sh --profile ai --apply  # optional, only on a machine you choose
~/.local/bin/researchos doctor
~/.local/bin/researchos init hello_lab
cd hello_lab
~/.local/bin/researchos run . -- python3 experiments/hello.py
```

**Without installing any APT packages** (from an extracted source ZIP), use:

```bash
python3 bin/researchos doctor
python3 bin/researchos init hello_lab
python3 bin/researchos run hello_lab -- python3 experiments/hello.py
```

Set `--timeout` before `PROJECT` if needed: `researchos run --timeout 60 PROJECT -- command`.

The `run` command saves reports in `PROJECT/runs/`, ignored by Git by default. Do not put passwords/API keys in command arguments or logs. The installer accepts Ubuntu 24.04 and 26.04 for `--apply`; preview and CLI can run elsewhere for evaluation. The robotics profile does **not** install ROS 2 automatically: use Jazzy on 24.04, Lyrical on 26.04. Compatibility with GPU drivers and third-party robotics components depends on tested hardware.

> **Safety / 安全**: This installer never selects partitions, formats disks, touches EFI/bootloader, removes packages, or changes Windows. It is not an OS installer. See [external-drive installation](docs/INSTALL-EXTERNAL-DRIVE.md) for manual precautions. Never run unreviewed scripts with `sudo`.

## Project layout

```text
bin/researchos                         # Python standard-library CLI
scripts/install.sh                     # profile installer, preview by default
packages/                              # explicit APT package lists
tests/                                 # CLI tests
docs/                                  # architecture, safety, roadmap
.github/workflows/ci.yml               # staged copy; GitHub does not run it here
```

仓库根目录（本目录之外）的 `.github/workflows/research-os.yml` 才是 GitHub 会运行的工作流。

## Design principles / 设计原则

1. **Simple for the user, complex for the engineer**: a few trustworthy commands.
2. **Evidence, not cosmetics**: run logs and version context over merely rebranding a desktop.
3. **Safe by default**: preview changes, avoid opaque boot/disk modifications.
4. **Reproducible**: no hidden personal files or credentials, portable setup.
5. **Optional complexity**: AI and robotics dependencies are modular, not forced.

## Status, contributions, and roadmap

See [Architecture](docs/ARCHITECTURE.md), [Roadmap](docs/ROADMAP.md) and [Security](docs/SECURITY.md). Tests:

在 `projects/research-os/` 下执行。安装脚本只做预览，不要加 `--apply`。

```bash
bash -n scripts/install.sh
shellcheck scripts/install.sh
bash scripts/install.sh --profile core
bash scripts/install.sh --profile ai
bash scripts/install.sh --profile robotics
python3 -m unittest discover -s tests -v
```

MIT license applies to **this repository's code only**, not Ubuntu, GNOME, ROS 2, PyTorch or other bundled/upstream software.
