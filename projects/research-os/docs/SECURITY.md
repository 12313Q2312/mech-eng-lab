# Security and data handling

- Installer defaults to preview, and only changes packages + user-local CLI under explicit `--apply`.
- Run as an unprivileged user; APT invokes sudo only after user approval.
- Never commit API keys, private SSH keys, Windows profiles, research secrets or personal datasets.
- The CLI does not send telemetry or make web requests. `doctor` intentionally excludes hostname/username/IP.
- `run` records command arguments, stdout and stderr **locally** and may capture sensitive content. Treat `runs/` as private; `.gitignore` excludes it.
- External-drive OS installation is manual; ResearchOS does **not** format, repartition, or edit EFI.
- Project command execution is an explicit trusted-user action, not sandboxing. Do not run untrusted commands.
- Check scripts before applying, and retain independent backups.

Please report security issues privately to the repository maintainer rather than opening issues containing secrets.
