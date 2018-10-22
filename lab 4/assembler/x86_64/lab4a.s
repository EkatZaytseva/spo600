.text
.globl    _start

start = 0                       /* starting value for the loop index; note that this is a symbol (constant), not a variable */
max = 10                        /* loop exits when the index hits this number (loop condition is i<max) */
cvt = 48			/* this is a number that needs to be added to the inary value of the registry to change value to decimal */

_start:
    mov     $start,%r15         /* loop index */

loop:
    /* body of the loop */
    movq    $len,%rdx
    movq    $msg,%rsi
    movq    $cvt,%r14
    movq    %r15,%r13
    add     %r13,%r14 
    movb    %r14b,msg+6		/* treating the string to be printed as a pointer, so msg+6 points to the 6th character */
    movq    $1,%rdi
    movq    $1,%rax
   
    syscall

    inc     %r15                /* increment index */
    cmp     $max,%r15           /* see if we're done */
    jne     loop                /* loop if we're not */

    mov     $0,%rdi             /* exit status */
    mov     $60,%rax            /* syscall sys_exit */
    syscall


.section .data

msg:     .ascii     "Loop:      \n"
	 len = . - msg
