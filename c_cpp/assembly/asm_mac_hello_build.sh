# https://zhuanlan.zhihu.com/p/73627228
# BigSur 移走了 /usr/lib/ 下的 lib 文件需要重新指定下 -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
# macOS 12 改到Xcode app的目录下面。举个例子：/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/lib
as mac_hello.S -o mac_hello.o
# -e _main指定主函数
ld -e _main mac_hello.o -o mac_hello -L /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/lib  -lSystem
./mac_hello

