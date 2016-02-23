#pragma once

/*Standard Library*/
#include <cstddef>

/*Custom Library*/
#include "common.h"

template<typename t_integral>
inline t_integral alignTo(t_integral value, size_t alignment);

template<typename t_ptr>
inline t_ptr* alignTo(t_ptr* value, size_t alignment);

template<typename t_integral>
inline bool isAlignedTo(t_integral value, size_t alignment);

template<typename t_ptr>
inline bool isAlignedTo(t_ptr* value, size_t alignment);

inline bool isPowerOfTwo(size_t value);

#include "..\Source\utility.inl"