#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "${ROOT}"

if ! command -v uv >/dev/null 2>&1; then
  echo "uv is not installed. See https://docs.astral.sh/uv/getting-started/installation/" >&2
  exit 1
fi

uv sync --group dev

if [[ $# -eq 0 ]]; then
  echo "🐍 Running all Python tests..."
  exec uv run pytest
fi

echo "🐍 Running Python tests: $*"
exec uv run pytest "$@"
