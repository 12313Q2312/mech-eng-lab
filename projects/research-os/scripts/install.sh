#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROFILE="core"
APPLY=0

usage() {
  cat <<'EOF'
ResearchOS installer (Ubuntu 24.04 LTS, x86_64 / aarch64)
Usage: bash scripts/install.sh [--profile core|ai|robotics] [--apply]
Default is PREVIEW ONLY. --apply installs APT packages and the user-level CLI.
This script does NOT partition disks, install bootloaders, remove software or configure CUDA.
Robotics profile prepares base tooling only; ROS 2 must be added using the official instructions.
EOF
}

while (($#)); do
  case "$1" in
    --profile) [[ $# -ge 2 ]] || { echo 'Missing profile' >&2; exit 2; }; PROFILE="$2"; shift 2 ;;
    --apply) APPLY=1; shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown argument: $1" >&2; usage; exit 2 ;;
  esac
done

case "$PROFILE" in core|ai|robotics) ;; *) echo "Unknown profile: $PROFILE" >&2; exit 2 ;; esac

read_packages() {
  local filename="$1"
  while IFS= read -r line || [[ -n "$line" ]]; do
    [[ -z "$line" || "$line" == \#* ]] && continue
    [[ "$line" =~ ^[a-z0-9][a-z0-9+.-]*$ ]] || { echo "Invalid package: $line" >&2; exit 2; }
    printf '%s\n' "$line"
  done < "$filename"
}
mapfile -t PACKAGES < <(read_packages "$ROOT_DIR/packages/core.txt")
if [[ "$PROFILE" == ai || "$PROFILE" == robotics ]]; then
  mapfile -t EXTRAS < <(read_packages "$ROOT_DIR/packages/${PROFILE}.txt")
  PACKAGES+=("${EXTRAS[@]}")
fi

cat <<EOF
ResearchOS installer
Mode: $([[ "$APPLY" -eq 1 ]] && echo APPLY || echo PREVIEW)
Profile: $PROFILE
Packages: ${PACKAGES[*]}
CLI: ~/.local/bin/researchos
EOF
if [[ "$PROFILE" == robotics ]]; then
  echo 'NOTE: ROS 2 Jazzy is NOT auto-installed. Follow the official ROS 2 Ubuntu instructions after this step.'
fi
if [[ "$APPLY" -eq 0 ]]; then
  echo 'No changes made. Review the package list, then rerun with --apply.'
  exit 0
fi

if [[ ! -r /etc/os-release ]]; then echo 'Cannot identify OS' >&2; exit 1; fi
# shellcheck disable=SC1091
source /etc/os-release
if [[ "${ID:-}" != ubuntu || "${VERSION_ID:-}" != '24.04' ]]; then
  echo "Only Ubuntu 24.04 LTS is supported (detected ${ID:-?} ${VERSION_ID:-?})." >&2
  exit 1
fi
case "$(uname -m)" in x86_64|aarch64) ;; *) echo 'Unsupported architecture' >&2; exit 1 ;; esac
if [[ "$EUID" == 0 ]]; then echo 'Run as your regular user, not root; sudo is used for APT only.' >&2; exit 1; fi
sudo apt-get update
sudo apt-get install -y "${PACKAGES[@]}"
mkdir -p "$HOME/.local/bin"
install -m 0755 "$ROOT_DIR/bin/researchos" "$HOME/.local/bin/researchos"
echo 'ResearchOS CLI installed. Run: ~/.local/bin/researchos doctor'
echo 'Tip: ensure ~/.local/bin is in your PATH for the short command "researchos".'
