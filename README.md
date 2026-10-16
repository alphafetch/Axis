# Axis

[![License: MIT](https://img.shields.io/github/license/alphafetch/Axis?style=flat)](LICENSE)
[![Release](https://img.shields.io/github/v/release/alphafetch/Axis?style=flat)](https://github.com/alphafetch/Axis/releases)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![Header only](https://img.shields.io/badge/header--only-yes-brightgreen)
![Tested with GoogleTest](https://img.shields.io/badge/tested%20with-GoogleTest-blue)

A small, header-only C++17 math library: 2D, 3D and 4D vectors and 3x3 and 4x4 matrices.

## Features

- Vectors — `Vector2`, `Vector3`, `Vector4`
  - Arithmetic: `+`, `-`, `*` (scalar, both orders)
  - `dot`, `cross` (Vector3 only), `distance`, `reflect`, `project`, `reject`, `lerp`
  - `len`, `lensq`, `normalize`, `normalized`
  - `min`, `max`, `clamp`
- Matrices — `Matrix3`, `Matrix4` (row-major storage)
  - Default constructor is the identity matrix; `identity()`
  - Element-wise `+` and `-`
  - Matrix * matrix and matrix * vector (`Matrix3 * Vector3`, `Matrix4 * Vector4`)
  - `transpose` (in place), `transposed` (copy)
  - `determinant`
- Single-include umbrella header: `#include <axis/axis.hpp>`
- Unit-tested with GoogleTest (see [Building and testing](#building-and-testing))

## Requirements

- C++17 or later (uses `std::clamp`)
- Header-only, no external dependencies
- To build the tests: CMake 3.14 or newer and internet access on the first configure (GoogleTest is downloaded automatically)

## Installation

### Option 1: Copy the folder

Copy the `include/axis/` folder into your project:

```
your_project/
├── include/
│   └── axis/
...
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
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(axis)

target_link_libraries(your_target PRIVATE axis)
```

`axis` is a header-only `INTERFACE` target, so linking it just adds Axis's `include/` folder to your include path.
Axis's tests are not built when you pull it in this way.

## Quick Start

```cpp
#include <axis/axis.hpp>

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

// Normalization (both throw std::runtime_error on a zero-length vector)
axis::Vector3 unit = a.normalized();    // returns a new normalized vector
a.normalize();                          // normalizes in place

// Distance and geometry
float dist = axis::distance(a, b);
axis::Vector3 bounced = axis::reflect(a, b);   // reflect a vector off a (unit) normal
axis::Vector3 proj    = axis::project(a, b);   // project a onto b
axis::Vector3 rej     = axis::reject(a, b);    // component of a perpendicular to b

// Interpolation
axis::Vector3 mid = axis::lerp(a, b, 0.5f);

// Component-wise
axis::Vector3 lo = axis::min(a, b);
axis::Vector3 hi = axis::max(a, b);
axis::Vector3 clamped = axis::clamp(a, lo, hi);
```

`Vector2` and `Vector4` support the same functions except `cross`, operating on 2 and 4 components respectively.

### Matrix3 / Matrix4

Both matrix types share the same API shape. The example below uses `Matrix3`:

```cpp
#include <axis/Matrix3.hpp>

axis::Matrix3 identity;                          // default constructor is the identity
axis::Matrix3 m(1.0f, 2.0f, 3.0f,                // row 0
                4.0f, 5.0f, 6.0f,                // row 1
                7.0f, 8.0f, 10.0f);              // row 2

// Element access (row, column); throws std::out_of_range if out of bounds
m(0, 0) = 2.0f;
float e = m(1, 2);

// Arithmetic
axis::Matrix3 sum  = m + identity;               // element-wise
axis::Matrix3 diff = m - identity;               // element-wise
axis::Matrix3 prod = m * identity;               // matrix product (not commutative)
axis::Vector3 v    = m * axis::Vector3(1.0f, 0.0f, 0.0f);

// Transpose
axis::Matrix3 t = m.transposed();                // returns a new matrix
m.transpose();                                   // transposes in place

// Determinant
float det = axis::determinant(m);
```

`Matrix4` works the same way with 16 constructor values, `Vector4`, and `#include <axis/Matrix4.hpp>`.

## Conventions and behavior

- **Storage and multiplication:** matrices are row-major, and matrix * vector treats the vector as a column (`M * v`).
- **Points and directions:** with `Matrix4 * Vector4`, use `w = 1` for a point and `w = 0` for a direction. A translation matrix moves points but leaves directions unchanged.
- **Errors:** `normalize`, `normalized`, `project` and `reject` throw `std::runtime_error` on a zero-length vector. Matrix element access throws `std::out_of_range` for an invalid index.
- **Preconditions:** `reflect` expects a unit-length normal, `lerp` does not clamp `t` (values outside 0 to 1 extrapolate), and `clamp` expects each lower bound to be at most the matching upper bound.
- **Precision:** everything uses `float`, so compare computed results with a tolerance rather than `==`.

## Building and testing

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

- GoogleTest is downloaded automatically the first time you configure.
- Pass `-DAXIS_BUILD_TESTS=OFF` to skip the tests.
- `ctest --test-dir` needs CMake 3.20 or newer. On older versions, run `ctest` from inside `build/`.
- With multi-config generators such as Visual Studio, build with `--config Debug` and run `ctest -C Debug`.

Test Log as of 10/12/26: [axis_test_log.log](https://gist.github.com/alphafetch/08289371fb06a4d8202df8c7f8d18dd5)

## Project structure

```
Axis/
├── include/axis/     # the library (header-only)
├── tests/            # GoogleTest unit tests
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Roadmap

- [ ] Matrix `inverse`
- [ ] Matrix transform builders (translation, rotation, scale, projection, look-at)
- [ ] `Quaternion`
- [ ] `==`, `+=`, `-=`, `*=` and `<<` operators
- [ ] `constants.hpp` and `scalar.hpp` utilities

## License

MIT License - see the [LICENSE](LICENSE) file for details.
