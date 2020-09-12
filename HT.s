	.globl	_Z7my_hashPKvm
	.type	_Z7my_hashPKvm, @function
_Z7my_hashPKvm:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L136
	movl	$0, %eax
	jmp	.L137
.L136:
	movq	$0, -8(%rbp)
	movq	$0, -16(%rbp)
.L139:
	movq	-16(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jnb	.L138
	movq	-8(%rbp), %rax
	leaq	0(,%rax,4), %rsi
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	xorb	$-4, %al
	cltq
	imulq	%rdx, %rax
	addq	%rsi, %rax
	movq	%rax, -8(%rbp)
	addq	$1, -16(%rbp)
	jmp	.L139
.L138:
	movq	-8(%rbp), %rax
.L137:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	_Z7my_hashPKvm, .-_Z7my_hashPKvm

