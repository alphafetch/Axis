# Axis

A simple, header-only math library built in C++.

## Features

- Vectors — `Vector2`, `Vector3`, `Vector4`
  - Arithmetic: `+`, `-`, `*` (scalar, both orders)
  - `dot`, `cross` (Vector3 only), `distance`, `reflect`, `project`, `reject`, `lerp`
  - `len`, `lensq`, `normalize`, `normalized`
  - `min`, `max`, `clamp`
- Matrices — `Matrix3`, `Matrix4` (stub only, see Roadmap)
- Quaternion (stub only, see Roadmap)

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

    axis::Vector3 sum = a + b;
    float d = axis::dot(a, b);
    float dist = axis::distance(a, b);
}
```

## Usage

### Vector2 / Vector3 / Vector4

All three vector types share the same API shape (`Vector3` additionally has `cross`):

```cpp
axis::Vector3 a(1.0f, 0.0f, 0.0f);
axis::Vector3 b(0.0f, 1.0f, 0.0f);

// Arithmetic
axis::Vector3 sum  = a + b;
axis::Vector3 diff = a - b;
axis::Vector3 scaled = a * 2.0f;
axis::Vector3 scaledOther = 2.0f * a;   // scalar on the left also works

// Products
float d = axis::dot(a, b);
axis::Vector3 c = axis::cross(a, b);    // Vector3 only

// Length
float length = a.len();
float lengthSq = a.lensq();

// Normalization
axis::Vector3 unit = a.normalized();    // returns a new normalized vector
a.normalize();                          // normalizes in place

// Distance and geometry
float dist = axis::distance(a, b);
axis::Vector3 bounced = axis::reflect(a, b);   // reflect a vector off a normal
axis::Vector3 proj    = axis::project(a, b);   // project a onto b
axis::Vector3 rej     = axis::reject(a, b);    // component of a perpendicular to b

// Interpolation
axis::Vector3 mid = axis::lerp(a, b, 0.5f);

// Component-wise
axis::Vector3 lo = axis::min(a, b);
axis::Vector3 hi = axis::max(a, b);
axis::Vector3 clamped = axis::clamp(a, lo, hi);
```

- `Vector2` and `Vector4` support the same functions except `cross`, operating on 2 and 4 components respectively.

### Matrix3

```cpp
axis::Matrix3 myMatrix;
// Not yet implemented — see Roadmap
```

### Matrix4

```cpp
axis::Matrix4 m;
m(0, 0) = 1.0f;   // element access via operator(), throws std::out_of_range if out of bounds
```

### Quaternion

```cpp
axis::Quaternion myQuat;
// Not yet implemented — see Roadmap
```

## Roadmap / TODO

- [ ] Add `tests/` with a test framework
- [ ] Fill out `Matrix3` / `Matrix4` operations (multiply, inverse, transpose, etc.)
- [ ] Fill out `Quaternion` operations
- [ ] Add `constants.hpp` and `scalar.hpp` utilities
- [ ] Add an `axis.hpp` umbrella header

## License

MIT License - see LICENSE file for details.
