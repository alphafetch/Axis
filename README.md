# Axis

A simple, bare-bones, header-only math library built in C++.

## Features

- Vectors
  - `Vector2`, `Vector3`, `Vector4`
- Matrices
  - `Matrix3`, `Matrix4`
- Quaternion

> Axis is early in development — most types are currently minimal
> (constructors and basic operators only). See [Roadmap](#roadmap--todo)
> for what's planned.

## Requirements

- Header-only, no external dependencies
- C++17 or later recommended (no build system is wired up yet — see Roadmap)

## Installation

### Option 1: Copy the folder

Copy the `include/axis/` folder into your project:

```
your_project/
├── include/
│   └── axis/
├── src/
└── main.cpp
```

### Option 2: Git submodule

```bash
git submodule add https://github.com/alphafetch/Axis.git external/axis
```

### Option 3: CMake FetchContent

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
#include <axis/Vector3.hpp>

int main() {
    axis::Vector3 a(1.0f, 2.0f, 3.0f);
    axis::Vector3 b(4.0f, 5.0f, 6.0f);

    float d = axis::dot(a, b);
}
```

## Usage

- `Vector2`
  ```cpp
  axis::Vector2 myVector;
  // More to be added to Vector2
  ```

- `Vector3`
  ```cpp
  axis::Vector3 a(1.0f, 2.0f, 3.0f);
  axis::Vector3 b(4.0f, 5.0f, 6.0f);

  float d = axis::dot(a, b);
  // + and - operators are also available (see note below)
  ```

- `Vector4`
  ```cpp
  axis::Vector4 myVector;
  // More to be added to Vector4
  ```

- `Matrix3`
  ```cpp
  axis::Matrix3 myMatrix;
  // More to be added to Matrix3
  ```

- `Matrix4`
  ```cpp
  axis::Matrix4 m;
  m(0, 0) = 1.0f; // element access via operator(), throws std::out_of_range if out of bounds
  ```

- `Quaternion`
  ```cpp
  axis::Quaternion myQuat;
  // More to be added to Quaternion
  ```

## Roadmap / TODO

- Add `CMakeLists.txt` and wire up a build
- Add `tests/` with a test framework (Catch2 planned)
- Fill out `Vector2` / `Vector4` operations
- Fill out `Matrix3` / `Matrix4` operations (multiply, inverse, transpose, etc.)
- Fill out `Quaternion` operations
- Add `constants.hpp` and `scalar.hpp` utilities
- Add an `axis.hpp` umbrella header

## License

MIT License - see LICENSE file for details.
