#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${ROOT}/cmake-build-debug"
TEST_BIN="${BUILD_DIR}/test_environment"

usage() {
  cat <<'EOF'
Usage:
  scripts/test/run.sh [suite_or_filter] [--no-build]

Examples:
  scripts/test/run.sh
  scripts/test/run.sh MyHashMapTests
  scripts/test/run.sh "MyHashMapTests.PutThenGetReturnsValue"
  scripts/test/run.sh LRUCacheV2Tests --no-build
EOF
}

FILTER=""
BUILD_FIRST=1

for arg in "$@"; do
  case "${arg}" in
    --no-build)
      BUILD_FIRST=0
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      if [[ -z "${FILTER}" ]]; then
        FILTER="${arg}"
      else
        echo "Unknown extra argument: ${arg}" >&2
        usage
        exit 1
      fi
      ;;
  esac
done

if [[ "${BUILD_FIRST}" -eq 1 ]]; then
  "${ROOT}/scripts/build/build.sh" test_environment
fi

if [[ ! -x "${TEST_BIN}" ]]; then
  echo "Test binary not found: ${TEST_BIN}" >&2
  echo "Run: scripts/build/all.sh test_environment" >&2
  exit 1
fi

if [[ -n "${FILTER}" ]]; then
  if [[ "${FILTER}" != *"*"* ]]; then
    FILTER="${FILTER}.*"
  fi
  echo "🧪 Running tests with filter: ${FILTER}"
  exec "${TEST_BIN}" --gtest_filter="${FILTER}"
fi

echo "🧪 Running all tests..."
exec "${TEST_BIN}"
