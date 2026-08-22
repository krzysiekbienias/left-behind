#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format nie jest zainstalowany."
    echo "Ubuntu/Debian: sudo apt install clang-format"
    exit 1
fi

format_file() {
    echo "formatuję: $1"
    clang-format -i --style=file "$1"
}

format_project() {
    find src header utils \
        \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) \
        -print0 | while IFS= read -r -d '' file; do
        format_file "$file"
    done
    echo "gotowe."
}

usage() {
    cat <<'EOF'
Użycie:
  ./format.sh <plik>     formatuje jeden plik (np. src/main.cpp)
  ./format.sh            formatuje cały projekt (src/, header/, utils/)
  ./format.sh --check    tylko sprawdza, bez zapisu (cały projekt)

Przykłady:
  ./format.sh src/matura2026/ex3_pary.cpp
  ./format.sh header/matura2026/ex3_pary.hpp
  ./format.sh
EOF
}

case "${1:-}" in
    -h|--help)
        usage
        ;;
    --check)
        find src header utils \
            \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) \
            -print0 | while IFS= read -r -d '' file; do
            clang-format --style=file "$file" | diff -u "$file" - >/dev/null || {
                echo "wymaga formatowania: $file"
                exit 1
            }
        done
        echo "wszystko sformatowane."
        ;;
    "")
        format_project
        ;;
    *)
        format_file "$1"
        ;;
esac
