.text
.globl    _start

start = 0                       /* starting value for the loop index; note that this is a symbol (constant), not a variable */
max = 31                        /* loop exits when the index hits this number (loop condition is i<max) */
cvt = 48

d = 10
_start:
    mov     $start,%r15         /* loop index */

loop:
    /* body of the loop */
    movq    $msg,%rsi
    movq    $d,%r10
    movq    %r15,%rax 		/*putting increment into rax because div divides by rax*/
    xor     %rdx, %rdx 		/* makes rdx 0*/
    div     %r10      		/*rax div 10  (increment/10) */
    cmp     %r10, %r15		/* see if we need to print the first number */
    jl      skip	        /* skip the first number if counter is greater than 10 */
    movq    %rax,%r9  		/*store quotient to r9 */
    add     $cvt,%r9
    movb    %r9b, msg+6   
 
skip:
    movq    %rdx,%r8            /* storing remainder, needed to display 2nd digit */
    add     $cvt,%r8
    movq    $len,%rdx
    movb    %r8b,msg+7
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
