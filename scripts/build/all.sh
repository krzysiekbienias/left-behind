#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
TARGET="${1:-all}"

"${ROOT}/scripts/build/configure.sh"
"${ROOT}/scripts/build/build.sh" "${TARGET}"

echo "✅ Configure + build done."
