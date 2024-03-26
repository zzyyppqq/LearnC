# macOS 上的汇编入门
# exit.s
    .section    __DATA, __data 0x114514 # .data 用.data来代替.section __DATA, __data，存放所有非const的已经被初始化过的变量
        .quad   0x114514
    .section    __DATA, __bss  # .bss 用.bss代替.section __DATA, __bss，存放所有未被初始化的static的变量
    .section    __DATA, __common  # __common节存放所有未被初始化过的外部全局变量
    .section    __TEXT,__text  # .text 在macho中，纯代码被放在了__TEXT段的__text节中, 代表之后的语句都是__TEXT段的__text节中, 可以直接用.text代替.section __TEXT, __text
    .globl  _main
    .equ    maxCount, 0x114514
_main:
    movq    $maxCount, %rax   # mov 0 to register rax
    retq