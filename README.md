# Axis

A simple, bare-bones math library built in C++.

## Features

 - Vectors
    - `Vector2`, `Vector3`, `Vector4`
 - Matrices
    - `Matrix3`, `Matrix4`
 - Quaternions

## Installation

### Option 1: 
Copy the `include/axis/` folder into your project.
```
your_project/
├── include/
│   └── axis/
├── src/
└── main.cpp
```

### Option 2: 
Use a `git submodule` inside your project's git repository:
```bash
git submodule add https://github.com/alphafetch/Axis.git external/axis
```

### Option 3:
Use CMake `FetchContent`. Enter this into your project's `CMakeLists.txt`:
```cmake
include(FetchContent)
FetchContent_Declare(
    axis
    GIT_REPOSITORY https://github.com/alphafetch/Axis.git
    GIT_TAG master
)
FetchContent_MakeAvailable(axis)

target_link_libraries(your_target PRIVATE axis)
```

## Quick Start
```cpp
void main() {
    axis::Vector3 myVector;
    // More to be added
}
```

## Usage
 - `Vector2`
 ```cpp
 void main() {
    axis::Vector2 myVector;
    // More to be added to Vector2
 }
 ```

 - `Vector3`
 ```cpp
 void main() {
    axis::Vector3 myVector;
    // More to be added to Vector3
 }
 ```

 - `Vector4`
 ```cpp
 void main() {
    axis::Vector4 myVector;
    // More to be added to Vector4
 }
 ```

 - `Matrix3`
 ```cpp
 void main() {
    axis::Matrix3 myMatrix;
    // More to be added to Matrix3
 }
 ```

 - `Matrix4`
 ```cpp
 void main() {
    axis::Matrix4 myMatrix;
    // More to be added to Matrix4
 }
 ```

 - `Quaternion`
 ```cpp
 void main() {
    axis::Quaternion myQuat;
    // More to be added to Quaternion
 }
 ```

## License

MIT License - see LICENSE file for details.