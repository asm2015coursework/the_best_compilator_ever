global cmm_malloc
global cmm_free
global init_cmm_heap


%define sys_brk               12
%define chunk_info            21
%define NULL                  0
%define free_chunk            byte  0
%define filled_chunk          byte  1

%macro set_free 1
    mov [%1 + 8], free_chunk
%endmacro

%macro set_filled 1
    mov [%1 + 8], filled_chunk
%endmacro

%macro get_state 2
    mov %2, [%1 + 8]
%endmacro

%macro set_len 2
    mov [%1 + 9], %2
%endmacro

%macro set_prev 2
    mov [%1], %2
%endmacro

%macro set_next 2
    mov [%1 + 4], %2
%endmacro

%macro get_len 2
    mov %2, [%1 + 9]
%endmacro

%macro get_prev 2
    mov %2, [%1]
%endmacro

%macro get_next 2
    mov %2, [%1 + 4]
%endmacro


section .data
initial_break:          resq    1 
current_break:          resq    1
first_chunk:            resq    1
last_chunk:             resq    1
;new_break:              resq    0x00000000

;chunk:   |pointer to previous chunk|pointer to next chunk|filled/free|length of chunk| data |
;         |        8 bytes          |        8 bytes      |  1 byte   |    4 bytes    |      |

section .text

init_cmm_heap:
    mov rax, sys_brk
    mov rdi, 0
    syscall
    mov [current_break], rax
    mov [initial_break], rax
    mov rax, NULL
    mov [first_chunk], rax
    mov [last_chunk], rax
    ret


; rdi - number of bytes to allocate
; returns pointer to allocated memory
; allocates memory
cmm_malloc:
    mov rax, [first_chunk]

.cycle
    cmp rax, NULL
    je .break

    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .doesnt_fit

    xor rdx, rdx
    get_len rax, edx
    cmp rdx, rdi
    jl .doesnt_fit

    sub rdx, rdi
    cmp rdx, chunk_info
    jg .divide_chunk

    set_filled rax
    add rax, chunk_info
    ret

.divide_chunk
    mov rcx, rax
    add rcx, chunk_info
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
    sub rdx, chunk_info
    sub rdx, rdi
    set_len rcx, edx

    set_len rax, edi

.doesnt_fit
    get_next rax, rdx
    mov rax, rdx
    jmp .cycle

.break
    
    cmp rax, NULL
    jne .exit
    call allocate_new_chunk

.exit
    ret


;rdi - pointer to memory
;doesn't work
cmm_free:
    sub rdi, chunk_info
    get_prev rdi, rax
    ;rax - pointer to previous chunk
    ;rdi - pointer to current chunk
    cmp rax, NULL
    je .dont_merge_prev
    
    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .dont_merge_prev

    ;merging current chunk and previous chunk
    ;set next chunk in rax
    get_next rdi, rcx
    set_next rax, rcx

    ;set prev chunk
    cmp rcx, NULL
    je .here
    set_prev rcx, rax
.here

    ;set len 
    xor rcx, rcx
    get_len rdi, ecx
    add rcx, chunk_info
    xor r8, r8
    get_len rax, r8d
    add rcx, r8
    set_len rax, ecx

    mov rdi, rax

.dont_merge_prev
    
    get_next rdi, rax
    ;rax - pointer to next chunk
    ;rdi - pointer to current chunk     
    cmp rax, NULL
    je .dont_merge_next

    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .dont_merge_next

    ;merging current chunk and next chunk
    ;set next chunk in rdi
    get_next rax, rcx
    set_next rdi, rcx

    ;set prev chunk
    cmp rcx, NULL
    je .here2
    set_prev rcx, rax
.here2


    ;set len 
    xor rcx, rcx
    get_len rax, ecx
    add rcx, chunk_info
    xor r8, r8
    get_len rdi, r8d
    add rcx, r8
    set_len rdi, ecx    

.dont_merge_next

    call try_to_free
    ret


try_to_free:
    mov rax, [last_chunk]
    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .exit
    
.cycle
    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .exit2

    mov [current_break], rax
    get_prev rax, rcx
    mov rdx, NULL
    set_next rcx, rdx
    mov [last_chunk], rcx 
    
    jmp .cycle

.exit2
    mov rax, sys_brk
    mov rdi, [current_break]
    syscall

.exit
    ret

;rax - length of new chunk 
;returns in rax pointer to allocated memory
allocate_new_chunk:
    mov rdx, rax
    add rax, chunk_info
    add rax, [current_break]
    mov rdi, rax
    mov rax, sys_brk
    syscall
    cmp rax, 0
    je .exit
    push rax
    mov rax, [current_break]
    ;filling prev
    mov rdi, [last_chunk]
    set_prev rax, rdi
    ;filling next
    mov rdi, NULL
    set_next rax, rdi
    ;set_filled
    set_filled rax
    ;set_len
    set_len rax, edx  

    ;setting next last_chunk
    mov rax, [last_chunk]
    mov rdi, [current_break]
    set_next rax, rdi

    mov [last_chunk], rdi

    pop rax
    mov rdx, [current_break]
    mov [current_break], rax
    mov rax, rdx
    add rax, chunk_info

.exit
    ret


