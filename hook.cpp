#include <algorithm> // std::swap
#include <assert.h>  // assert
#include <cstring>   // std::memmove
#include <dlfcn.h>   // dlsym
#include <iostream>  // std::cout

namespace {
inline bool intervalsIntersect(size_t a, size_t b, size_t count) {
    if (a > b) {
        std::swap(a, b);
    }
    assert(a <= b);
    return (count > 0) && (b < a + count); // a --- b --- a+count
}

typedef void*(*memcpy_t)(void*, const void*, size_t);
memcpy_t cp = (memcpy_t)dlsym(RTLD_NEXT, "memcpy");
}

extern "C" {
void* memcpy(void* dest, const void* src, size_t count) {
    if (!intervalsIntersect((size_t)dest, (size_t)src, count)) {
        return cp(dest, src, count);
    } else {
        std::cerr << "Copy of intersected intervals "
            "(" << (size_t)src << ";" << (size_t)(src) + count << "[ -> "
            "(" << (size_t)dest << ";" << (size_t)(dest) + count << "[!\t"
            "Using memmove()!\n";
        return std::memmove(dest, src, count);
    }
}
}