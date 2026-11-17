# ResearchOS · Reproducible AI & Engineering Workstation

> **V0.1 alpha.** An Ubuntu-based workstation blueprint and a working research CLI. **Not a standalone Linux distribution or bootable ISO yet.**  
> **V0.1 测试版。** 基于 Ubuntu 的可复现科研工程工作站与可运行命令行工具；**尚不是独立发行版/可启动 ISO**。

ResearchOS aims to make it easier to repeat engineering experiments and rebuild workstations consistently. Its current focus: AI research (KAN/PyTorch), C++ engineering, robotics readiness, and experiment evidence. It intentionally does **not** replace Windows-only CAD tools.

ResearchOS 希望让科研人员更快构建工作环境、可靠复现实验、保存验证证据，而不是在每台机器上重复手动配置。

## What works today / V0.1 已实现

- `researchos doctor`: inspect a minimal machine configuration without displaying username/hostname.
- `researchos init NAME`: create a ready-to-run research project with predictable structure.
- `researchos run PROJECT -- COMMAND...`: execute one experiment, save stdout/stderr, exit code, wall time, kernel/Python info, and Git commit when available.
- Preview-first installer: `core`, `ai`, `robotics` profiles; changes happen **only** when `--apply` is used.
- Unit tests + GitHub Actions workflow; safe non-destructive start.

**Not included yet:** full desktop theme, browser/setup migration, GPU driver/CUDA installer, ROS 2 installer, custom kernel, bootable ISO, performance claims. Ubuntu and upstream packages remain third-party projects with their own licenses.

## Quick start / 快速开始

On an **already installed Ubuntu 24.04 LTS Desktop** machine:

```bash
# Clone the ResearchOS source repository or extract the release ZIP.
cd ResearchOS-v0.1
bash scripts/install.sh --profile core        # dry-run: no changes
bash scripts/install.sh --profile ai --apply  # optional: APT install + CLI copy
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

The `run` command saves reports in `PROJECT/runs/`, ignored by Git by default. Do not put passwords/API keys in command arguments or logs. The installer only accepts Ubuntu 24.04 for `--apply`; preview and CLI can run elsewhere for evaluation.

> **Safety / 安全**: This installer never selects partitions, formats disks, touches EFI/bootloader, removes packages, or changes Windows. It is not an OS installer. See [external-drive installation](docs/INSTALL-EXTERNAL-DRIVE.md) for manual precautions. Never run unreviewed scripts with `sudo`.

## Project layout

```text
bin/researchos            # Python standard-library CLI
scripts/install.sh        # profile installer, preview by default
packages/                # explicit APT package lists
tests/                   # CLI tests
docs/                    # architecture, safety, roadmap
.github/workflows/ci.yml  # proposed smoke checks
```

## Design principles / 设计原则

1. **Simple for the user, complex for the engineer**: a few trustworthy commands.
2. **Evidence, not cosmetics**: run logs and version context over merely rebranding a desktop.
3. **Safe by default**: preview changes, avoid opaque boot/disk modifications.
4. **Reproducible**: no hidden personal files or credentials, portable setup.
5. **Optional complexity**: AI and robotics dependencies are modular, not forced.

## Status, contributions, and roadmap

See [Architecture](docs/ARCHITECTURE.md), [Roadmap](docs/ROADMAP.md) and [Security](docs/SECURITY.md). Tests:

```bash
bash -n scripts/install.sh
bash scripts/install.sh --profile core
python3 -m unittest discover -s tests -v
```

MIT license applies to **this repository's code only**, not Ubuntu, GNOME, ROS 2, PyTorch or other bundled/upstream software.
