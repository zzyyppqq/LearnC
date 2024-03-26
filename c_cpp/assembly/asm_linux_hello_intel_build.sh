# https://zhuanlan.zhihu.com/p/73627228
# BigSur 移走了 /usr/lib/ 下的 lib 文件需要重新指定下 -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
# macOS 12 改到Xcode app的目录下面。举个例子：/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/lib
nasm -f elf64 linux_hello_intel.asm -o linux_hello_intel.o
# -e _main指定主函数
ld linux_hello_intel.o -o linux_hello_intel
./linux_hello_intel

