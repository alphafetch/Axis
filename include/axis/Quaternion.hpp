/**
 * @file include/axis/Quaternion.hpp
 * @brief Quaternion header for Axis math library
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef AXIS_QUATERNION_HPP
#define AXIS_QUATERNION_HPP

namespace axis {
    /// @brief Quaternion for representing 3D rotations (currently just the data members; no operations yet)
    class Quaternion {
    public:
        /// @brief Scalar (real) part
        float w;
        /// @brief Vector (imaginary) part, i component
        float x;
        /// @brief Vector (imaginary) part, j component
        float y;
        /// @brief Vector (imaginary) part, k component
        float z;
    };
}

#endif
