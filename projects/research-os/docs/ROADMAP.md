# ResearchOS roadmap (evidence gates)

## V0.1 · Workstation as code (current alpha)

- Preview/apply profile installer
- `doctor`, `init`, `run` CLI
- Tests and setup guide
- No claim of original kernel, ready-made ISO, GPU/CUDA setup, or production support

**Acceptance:** local unit tests pass; installer preview causes no changes; one project scaffolds and runs, with a local evidence JSON/log pair.

## V0.2 · Reliable full desktop

- Optional UI launcher (desktop entry)
- User-customizable GNOME profile (no forced overwrites)
- Interactive, non-destructive Windows-to-Linux migration planner
- Signed packages, dependency version checks, rollback notes

**Acceptance:** 2 clean Ubuntu 24.04 installations reproduce the same profile; independent user completes setup without developer assistance.

## V0.3 · Research profiles

- AI profile with reproducible venvs and CPU/GPU-specific checks
- Official ROS 2 Jazzy setup automation with signed-source verification
- C++ / CMake presets; test reports; experiment comparison

**Acceptance:** a KAN project and a ROS 2 demonstration run with documented dependency manifests on tested hardware.

## V0.4 · Image and release engineering

- Test an official Ubuntu image customization or autoinstall pipeline in disposable VMs
- Publish checksums/signatures and installation compatibility matrix
- Produce opt-in bootable ISO only after full install/rollback QA

**Acceptance:** automated VM installs and independent manual verification; no unattended destructive external-disk operation.

## Future · Distinctive OS experience

Only after user research: one-click scientific workflows, experiment indexing, hardware-specific edge-AI deployment, optional kernel instrumentation. A new kernel fork is **not** a milestone by itself.
