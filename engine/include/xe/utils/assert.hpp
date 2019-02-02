//
// Created by FLXR on 2/2/2019.
//

#ifndef X808_ASSERT_HPP
#define X808_ASSERT_HPP


#include <xe/utils/log.hpp>

#ifdef XE_DEBUG
#define XE_ASSERT(x, ...) \
        if (!(x)) {\
            XE_CORE_FATAL("ASSERTION FAILED"); \
            XE_CORE_FATAL("{0}: {1}", __FILE__, __LINE__); \
            XE_CORE_FATAL("Condition: {0}", #x); \
            XE_CORE_FATAL(#__VA_ARGS__); \
            __debugbreak(); \
        }
#else
#define XE_ASSERT(x, ...)
#endif


#endif //X808_ASSERT_HPP
