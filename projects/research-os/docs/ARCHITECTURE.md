# Architecture / 系统架构

```
Ubuntu 26.04 / 24.04 LTS (standard installer and kernel)
  ├─ GNOME Desktop (upstream)
  ├─ ResearchOS profile installer (preview/apply)
  │     ├─ core: C/C++, Python, Git, utilities
  │     ├─ ai: core + Python headers (PyTorch installed separately)
  │     └─ robotics: core + Python headers (ROS 2 installed separately)
  └─ ResearchOS CLI
        ├─ doctor: privacy-minimal environment checks
        ├─ init: project scaffolding (does not overwrite)
        └─ run: run evidence (version, exit, logs, elapsed)
```

This is a reproducible *workstation layer*, not an independent kernel or image. Rebuild a fresh Ubuntu system by running the same installer version and profile. A true image-based distribution is a future milestone conditional on compatibility and maintenance evidence.

ResearchOS does not ingest personal Windows settings or credentials. Windows-only apps (SolidWorks, desktop AutoCAD) remain Windows workloads. Disk provisioning, GPU drivers, and official ROS 2 repositories are deliberately out of scope for V0.1.

## Experiment evidence

A run creates three local files: JSON metadata, stdout log, stderr log. The JSON records machine/software context (not hostname or username) and exit code. **Wall time alone is not a valid microbenchmark**; CPU isolation, repeated trials, clocks and statistical reporting are future work.

Commands are executed without a shell, reducing injection risk. However, user-provided commands can still alter files: only execute commands you understand. Run outputs can contain secrets, so `runs/` stays ignored by Git.
