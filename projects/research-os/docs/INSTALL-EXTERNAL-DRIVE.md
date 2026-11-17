# External SSD installation: safety plan / 外置 SSD 安装安全指南

**This file is guidance, not an unattended installer. Do NOT run partition commands copied from the internet.**

Target architecture: Windows on internal disk, Ubuntu 24.04 LTS on separate external SSD. Exact machine/UEFI/SSD hardware is unknown until checked.

1. **Back up both drives** before installing anything; don't store your only backup on the target SSD. Export existing WSL and preserve uncommitted project work.
2. Use Windows Disk Management / `Get-Disk` to identify drives, capacity, model, and free space. Record BitLocker recovery key; check UEFI / Secure Boot hardware compatibility.
3. Download the official Ubuntu 24.04 LTS Desktop ISO and create installer media using a **separate** >=8GB USB drive (writing it erases that USB).
4. Boot the installer in **Try Ubuntu** mode first and check Wi-Fi, GPU, audio, input devices, external SSD stability, USB speed, and suspend/resume.
5. At install time, **manually verify target disk** by model/capacity. The installer must not erase the internal Windows disk. EFI partition and GRUB should reside on the external disk where feasible, but installer/firmware behavior varies and must be checked. Consider qualified help if any doubt remains.
6. Before first normal use, test boot with and without the external SSD and verify Windows still starts. Then install ResearchOS using its dry-run-first script.

**No automatic partition tables or bootloader writing in V0.1.**

Official Ubuntu tutorial: https://ubuntu.com/desktop/docs/en/24.04/tutorial/install-ubuntu-desktop/
