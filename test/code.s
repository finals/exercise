	.file	"code.c"
	.text
.globl sum
	.type	sum, @function
sum:
.LFB0:
	.cfi_startproc
	leal	(%rsi,%rdi), %eax
	addl	%eax, accum(%rip)
	ret
	.cfi_endproc
.LFE0:
	.size	sum, .-sum
.globl accum
	.bss
	.align 4
	.type	accum, @object
	.size	accum, 4
accum:
	.zero	4
	.ident	"GCC: (GNU) 4.4.6 20120305 (Red Hat 4.4.6-4)"
	.section	.note.GNU-stack,"",@progbits
