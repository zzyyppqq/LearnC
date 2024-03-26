//
// Created by 张宜鹏 on 2023/1/19.
//

#ifndef CPP_LIBRARY_H
#define CPP_LIBRARY_H
// [Linux下__attribute__((visibility ("default")))的使用_fengbingchun的博客-CSDN博客](https://blog.csdn.net/fengbingchun/article/details/78898623 )
// reference: https://gcc.gnu.org/wiki/Visibility
//            https://developer.apple.com/library/content/documentation/DeveloperTools/Conceptual/CppRuntimeEnv/Articles/SymbolVisibility.html

#ifdef __GNUC__ >= 4 // it means the compiler is GCC version 4.0 or later
    #ifdef FBC_EXPORT
        #warning "===== dynamic library ====="
        #define FBC_API_PUBLIC __attribute__((visibility ("default")))
        #define FBC_API_LOCAL __attribute__((visibility("hidden")))
    #else
        #warning "===== static library ====="
        #define FBC_API_PUBLIC
        #define FBC_API_LOCAL
    #endif
#else
    #error "##### requires gcc version >= 4.0 #####"
#endif

#ifdef __cplusplus
extern "C" {
#endif

FBC_API_PUBLIC int library_add(int a, int b);
FBC_API_LOCAL void print_log();

#ifdef FBC_EXPORT
FBC_API_PUBLIC int value;
#endif

#ifdef __cplusplus
}
#endif

template<typename T>
class FBC_API_PUBLIC Simple {
public:
    Simple() = default;

    void Init(T a, T b);

    T Add() const;

private:
    T a, b;
};

#endif //CPP_LIBRARY_H
