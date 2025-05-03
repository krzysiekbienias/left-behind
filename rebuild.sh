#!/bin/bash

echo "🧹 Cleaning..."
rm -rf xcode_build

echo "📁 Creating build directory..."
mkdir -p xcode_build

echo "🔧 Generating Xcode project..."
cmake -G Xcode -S . -B xcode_build

echo "✅ Done. You can now run:"
echo "   open xcode_build/left_behind.xcodeproj"
