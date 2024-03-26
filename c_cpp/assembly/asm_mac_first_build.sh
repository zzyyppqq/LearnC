# https://zhuanlan.zhihu.com/p/23618489
# elf64作用于linux、macho64作用于macOS, 通过 nasm --help查看命令
#nasm -f elf64 first.asm -o first.o
#nasm -f macho64 first.asm -o first.o
# --prefix是为gobal的标签添加前缀, 链接时根据的都是以_开头的
nasm -f macho64 --prefix _ mac_first.asm -o mac_first.o
gcc -m64 mac_first.o -o mac_first
./mac_first; echo $?

