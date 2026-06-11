#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${ROOT}/cmake-build-debug"
TARGET="${1:-all}"

echo "🏗️  Building target '${TARGET}' in ${BUILD_DIR}..."
cmake --build "${BUILD_DIR}" --target "${TARGET}"
echo "✅ Build done."
