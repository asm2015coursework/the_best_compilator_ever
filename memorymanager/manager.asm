%define sys_brk               qword 12

global my_malloc
global my_free
global init_my_heap

section .data
initial_break:          resq    1 
current_break:          resq    1
;new_break:              resq    0x00000000

section .text

init_my_heap:
    mov rax, sys_brk
    mov rdi, 0
    syscall
    mov [current_break], rax
    mov [initial_break], rax
    ret


; rdi - number of bytes to allocate
; allocates memory
my_malloc:
    mov rax, sys_brk
    add rdi, [current_break]
    ;rax = 12 - number of syscall(brk), rdi - pointer to memory to allocate
    syscall
    cmp rax, 0
    jl .err_exit
    push qword [current_break]
    mov [current_break], rax
    pop rax
    ret
    .err_exit:
    xor rax, rax
    ret



;rdi - pointer to memory
;doesn't work
my_free:
    mov rax, sys_brk
    mov rdi, [initial_break]
    ;rax = 12 - number of syscall(brk), rdi - pointer to memory to free
    syscall
    mov [current_break], rax
    ;mov rax, initial_break
    ret
