	.globl	_Z7my_hashPKvm
	.type	_Z7my_hashPKvm, @function
_Z7my_hashPKvm:
LFB40:
	.cfi_startproc
        testq   %rdi, %rdi
        je      .L5
        testq   %rsi, %rsi
        je      .L5
        xorl    %edx, %edx
        xorl    %r8d, %r8d
.L3:
        addq    $1, %rdx
        movsbl  -1(%rdi,%rdx), %eax
        xorb    $-4, %al
        cltq
        imulq   %rdx, %rax
        leaq    (%rax,%r8,4), %r8
        cmpq    %rsi, %rdx
        jne     .L3
        movq    %r8, %rax
        ret
.L5:
        xorl    %r8d, %r8d
        movq    %r8, %rax
        ret
	.cfi_endproc
LFE40:
	.size	_Z7my_hashPKvm, .-_Z7my_hashPKvm
