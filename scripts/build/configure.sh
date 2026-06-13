#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${ROOT}/build"

echo "🔧 Configuring ${BUILD_DIR}..."
cmake -S "${ROOT}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug

if [[ -f "${BUILD_DIR}/compile_commands.json" ]]; then
  cp "${BUILD_DIR}/compile_commands.json" "${ROOT}/compile_commands.json"
  echo "📎 Synced compile_commands.json -> project root"
fi

echo "✅ Configure done."
