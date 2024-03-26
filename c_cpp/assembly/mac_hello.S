output:
.ascii "hello world!"
.global hello,_main
hello:
    movq $1,%rdi
    leaq output(%rip),%rsi
    movq $11,%rdx
    movq $0x2000000,%rax
    orq $4,%rax
    syscall
    retq
_main:
    call hello
    xorq %rax,%rax
    retq