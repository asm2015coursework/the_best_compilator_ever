;;;;;;;;CMM memory manager;;;;;;;;
%macro set_free 1
    mov [%1 + 16], byte  0
%endmacro
%macro set_filled 1
    mov [%1 + 16], byte  1
%endmacro
%macro get_state 2
    mov %2, [%1 + 16]
%endmacro
%macro set_len 2
    mov [%1 + 17], %2
%endmacro   
%macro set_prev 2
    mov [%1], %2
%endmacro
%macro set_next 2
    mov [%1 + 8], %2
%endmacro
%macro get_len 2
    mov %2, [%1 + 17]
%endmacro
%macro get_prev 2
    mov %2, [%1]
%endmacro
%macro get_next 2
    mov %2, [%1 + 8]
%endmacro

section .data
initial_break:          dq  0 
current_break:          dq  0
first_chunk:            dq  0
last_chunk:             dq  0
init:                   db  0

section .text

init_cmm_heap:
    mov rax, 12
    mov rdi, 0
    syscall
    mov [current_break], rax
    mov [initial_break], rax
    mov rax, 0
    mov [first_chunk], rax
    mov [last_chunk], rax
    mov [init], byte 1
    ret

cmm_malloc:
    push rcx
    push r11
    push rdx
    push rdi
    mov rdi, [rsp + 40]
    cmp [init], byte 1
    je .initialized
    push rdi
    call init_cmm_heap
    pop rdi
.initialized
    mov rax, [first_chunk]
.cycle
    cmp rax, 0
    je .break
    xor rdx, rdx
    get_state rax, dl
    cmp dl, byte  1
    je .doesnt_fit
    xor rdx, rdx
    get_len rax, edx
    cmp rdx, rdi
    jl .doesnt_fit
    sub rdx, rdi
    cmp rdx, 21
    jg .split_chunk
    set_filled rax
    add rax, 21
    jmp .exit
.split_chunk
    mov rcx, rax
    add rcx, 21
    add rcx, rdi
    get_next rax, rdx 
    set_next rax, rcx
    set_next rcx, rdx
    set_prev rdx, rcx
    set_prev rcx, rax
    set_filled rax
    set_free rcx
    xor rdx, rdx
    get_len rax, edx
    sub rdx, 21
    sub rdx, rdi
    set_len rcx, edx
    set_len rax, edi
    add rax, 21
    jmp .exit
.doesnt_fit
    get_next rax, rdx
    mov rax, rdx
    jmp .cycle
.break
    cmp rax, 0
    jne .exit
    mov rax, rdi
    call allocate_new_chunk
.exit
    pop rdi
    pop rdx
    pop r11
    pop rcx
    ret

cmm_free:
    push rcx
    push r11
    push rdx
    push rdi
    push r8
    push rax
    mov rdi, [rsp + 56]
    sub rdi, 21
    set_free rdi
    get_prev rdi, rax
    cmp rax, 0
    je .dont_merge_prev
    xor rdx, rdx
    get_state rax, dl
    cmp dl, byte  1
    je .dont_merge_prev
    cmp rdi, [last_chunk]
    jne .not_last2
    mov [last_chunk], rax
.not_last2
    get_next rdi, rcx
    set_next rax, rcx
    cmp rcx, 0
    je .here
    set_prev rcx, rax
.here
    xor rcx, rcx
    get_len rdi, ecx
    add rcx, 21
    xor r8, r8
    get_len rax, r8d
    add rcx, r8
    set_len rax, ecx
    mov rdi, rax
.dont_merge_prev
    get_next rdi, rax
    cmp rax, 0
    je .dont_merge_next
    xor rdx, rdx
    get_state rax, dl
    cmp dl, byte  1
    je .dont_merge_next
    cmp [last_chunk], rax
    jne .not_last
    mov [last_chunk], rdi
.not_last
    get_next rax, rcx
    set_next rdi, rcx
    cmp rcx, 0
    je .here2
    set_prev rcx, rdi
.here2
    xor rcx, rcx
    get_len rax, ecx
    add rcx, 21
    xor r8, r8
    get_len rdi, r8d
    add rcx, r8
    set_len rdi, ecx    
.dont_merge_next
    call try_to_free
    pop rax
    pop r8
    pop rdi
    pop rdx
    pop r11
    pop rcx
    ret

try_to_free:
    mov rax, [last_chunk]
    xor rdx, rdx
    get_state rax, dl
    cmp dl, byte  1
    je .exit
    get_prev rax, rdx
    cmp rdx, 0
    je .null2
    mov rcx, 0
    set_next rdx, rcx
.null2
    mov [last_chunk], rdx
    mov rcx, 0
    cmp [last_chunk], rcx
    jne .not_null2
    mov [first_chunk], rcx
.not_null2
    mov rdi, rax
    mov rax, 12
    syscall
    mov [current_break], rax
.exit
    ret

allocate_new_chunk:
    mov rdx, rax
    add rax, 21
    add rax, [current_break]
    mov rdi, rax
    mov rax, 12
    syscall
    cmp rax, 0
    je .exit
    push rax
    mov rax, [current_break]
    mov rdi, [last_chunk]
    set_prev rax, rdi
    cmp rdi, 0
    je .null
    set_next rdi, rax
.null
    mov rdi, 0
    set_next rax, rdi
    set_filled rax
    set_len rax, edx  
    pop rax
    mov rdx, [current_break]
    mov [last_chunk], rdx
    mov [current_break], rax
    mov rax, rdx
    mov rcx, 0
    cmp [first_chunk], rcx
    jne .not_null
    mov [first_chunk], rax
.not_null
    add rax, 21
.exit
    ret
;;;;;;;;End;;;;;;;;;
