#pragma once

#include <cstdint>
#include <cstddef>

// Very small pattern scan stub: provided so code compiles. Real patterns added later.
uintptr_t find_pattern_in_module(const char* module_name, const char* pattern, const char* mask);
