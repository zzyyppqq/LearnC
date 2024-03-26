#NDK_HOME=/Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462
#$NDK_HOME/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang++ \
#    --target=armv7-none-linux-androideabi19 \
#    --gcc-toolchain=$NDK_HOME/toolchains/llvm/prebuilt/darwin-x86_64 \
#    --sysroot=$NDK_HOME/toolchains/llvm/prebuilt/darwin-x86_64/sysroot \
#    main.cpp \
#    -o b.out


/Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang++ \
--target=aarch64-none-linux-android21 \
--gcc-toolchain=/Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64 \
--sysroot=/Users/zhangyipeng/Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/sysroot \
-g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes \
-D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -O0 -fno-limit-debug-info  \
-fPIE main.cpp -o main_cpp -static-libstdc++
#-fPIE -c main.cpp -o main.o -static-libstdc++


#/Users/zhangyipeng/AudioVideoProject/NdkCMakeSample/nativelib/build/intermediates/cxx/RelWithDebInfo/1b6a2p27/obj/arm64-v8a/ndk_example_cpp: CXX_EXECUTABLE_LINKER__ndk_example_cpp_RelWithDebInfo CMakeFiles/ndk_example_cpp.dir/main_cpp.cpp.o
#  FLAGS = -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -O2 -g -DNDEBUG
#  LINK_FLAGS = -Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libgcc_real.a -Wl,--exclude-libs,libatomic.a -static-libstdc++ -Wl,--build-id -Wl,--fatal-warnings -Wl,--no-undefined -Qunused-arguments -Wl,--gc-sections
#  LINK_LIBRARIES = -latomic -lm