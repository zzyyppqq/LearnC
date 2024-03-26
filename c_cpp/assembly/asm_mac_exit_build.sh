# https://zhuanlan.zhihu.com/p/73627228
# BigSur 移走了 /usr/lib/ 下的 lib 文件需要重新指定下 -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
# macOS 12 改到Xcode app的目录下面。举个例子：/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/lib
# 使用的汇编器as是"Mac OS X Mach-O GNU-based assemblers", 调试器是LLVM的lldb
as mac_exit.s -o mac_exit.o
ld mac_exit.o -o mac_exit -L /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/lib  -lSystem
./mac_exit; echo $?
echo "=======MachOView .text======="
otool -v -t mac_exit # MachOView 软件来查看生成的可执行文件中__TEXT段__text节的内容
echo "=======查看的符号表======="
nm -n -m mac_exit # 查看的符号表
