section	.text
global	_start

_start:
	mov	rdx,len			; message length
	mov	rcx,msg			; message location
	mov	rbx,1			; file descriptor stdout
	mov	rax,4			; syscall sys_write
	int	0x80

	mov	rax,1			; syscall sys_exit
	int	0x80

section	.rodata

msg	db	'Hello, world!',0xa
len	equ	$ - msg

