# left-behind
# 🧩 left-behind

> _"If I ever were to lose you, I'd surely lose myself..."_  
> — *"The Last of Us (Left Behind)" – Gustavo Santaolalla*

**left-behind** is a personal collection of small C++ projects, tools, and unfinished experiments — now revived, organized, and unified under one repo. Like the **Left Behind** DLC from *The Last of Us*, this project aims to breathe new life into what might have been forgotten: snippets, utilities, and algorithmic ideas that never had a home — until now.

## 🗂️ Project Structure
left-behind/
├── CMakeLists.txt        # Top-level build configuration
├── pyproject.toml        # uv / Python project (counterparts and small scripts)
├── config.json           # Central configuration used by various modules
├── data/                 # Sample input files (CSV, JSON, etc.)
├── header/               # Shared headers used across modules
├── src/                  # Main source code files (grouped by topic/project)
├── python/               # Python versions of tasks and small standalone scripts
├── unit_tests/           # Google Test-based unit tests for all modules
├── utils/                # Utility functions: I/O helpers, parsers, etc.
├── xcode_build/          # Optional directory for Xcode build integration
└── rebuild.sh            # Script to clean and rebuild the project

## 🛠️ Build Instructions

This project uses **CMake** for cross-platform builds. You can build it using the following steps:

```bash
# Create a build directory (optional)
mkdir build && cd build

# Generate project files
cmake ..

# Build
make

To rebuild from scratch 
./rebuild.sh

## 🐍 Python (uv)

Small Python projects and second versions of C++ tasks live in `python/`. The environment is managed by [uv](https://docs.astral.sh/uv/).

```bash
# create the virtualenv and install deps (pytest, ...)
uv sync

# run a script
uv run python python/twoja_nazwa.py

# run Python tests
uv run pytest
# or:
scripts/test/run_python.sh
```

Add a runtime package with `uv add requests`, a test/dev tool with `uv add --dev ruff`.

🔑 Configuration

The project uses config.json for defining API keys, feature flags, and runtime options.

Example keys:
```
{
  "STANDARISED_INPUT": true,
  "STUDENTS_DATA": "data/students.json",
  "ALPHA_VENTAGE_API_KEY": "...",
  "FRED_API_KEY": "...",
  "QUANDL_API_KEY": "...",
  "POLYGON_IO_API_KEY": "..."
}
```
