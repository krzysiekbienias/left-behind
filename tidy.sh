#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"

if ! command -v clang-tidy >/dev/null 2>&1; then
    echo "clang-tidy nie jest zainstalowany."
    echo "Ubuntu/Debian: sudo apt install clang-tidy"
    exit 1
fi

BUILD_DIR="build"

if [ ! -f "$BUILD_DIR/compile_commands.json" ]; then
    echo "Brak $BUILD_DIR/compile_commands.json — najpierw zbuduj projekt:"
    echo "  cmake -S . -B build && cmake --build build"
    exit 1
fi

run_tidy() {
    echo "tidy: $1"
    clang-tidy "$1" -p "$BUILD_DIR" --quiet
}

usage() {
    cat <<'EOF'
Użycie:
  ./tidy.sh <plik>     sprawdza jeden plik (np. src/main.cpp)
  ./tidy.sh            sprawdza cały projekt (src/, header/, utils/)
  ./tidy.sh --fix      sprawdza i automatycznie poprawia cały projekt

Przykłady:
  ./tidy.sh src/matura2026/ex3_pary.cpp
  ./tidy.sh
EOF
}

tidy_project() {
    local extra="${1:-}"
    find src header utils \( -name '*.cpp' \) -print0 \
        | while IFS= read -r -d '' file; do
        echo "tidy: $file"
        clang-tidy "$file" -p "$BUILD_DIR" --quiet ${extra}
    done
    echo "gotowe."
}

case "${1:-}" in
    -h|--help)
        usage
        ;;
    --fix)
        tidy_project "--fix"
        ;;
    "")
        tidy_project
        ;;
    *)
        run_tidy "$1"
        ;;
esac
