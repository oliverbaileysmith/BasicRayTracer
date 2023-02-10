#ifndef RT_STB_IMAGE_H
#define RT_STB_IMAGE_H

#pragma warning(disable : 4996)

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb/stb_image_write.h"

// Restore warning levels.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
#pragma warning (pop)
#endif

#endif