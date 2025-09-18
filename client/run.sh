#!/bin/bash
BUILD_DIR=build

# Step 1 - Configure
cmake -S . -B $BUILD_DIR

# Step 2 - Build Debug
cmake --build $BUILD_DIR --target Spirit_Warrior_Client -- -j$(nproc)

# Step 3 - Run
echo "Running Spirit_Warrior_Client..."
./$BUILD_DIR/Spirit_Warrior_Client