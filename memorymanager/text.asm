init_cmm_heap:
    mov rax, sys_brk
    mov rdi, 0
    syscall
    mov [current_break], rax
    mov [initial_break], rax
    mov rax, NULL
    mov [first_chunk], rax
    mov [last_chunk], rax
    mov [init], byte 1
    ret


; rdi - number of bytes to allocate
; returns pointer to allocated memory
; allocates memory
cmm_malloc:
    push rcx
    push r11
    push rdx
    push rdi
    cmp [init], byte 1
    je .initialized

    push rdi
    call init_cmm_heap
    pop rdi

.initialized

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
    jg .split_chunk

    set_filled rax

    add rax, chunk_info
    jmp .exit

.split_chunk

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

    add rax, chunk_info
    jmp .exit

.doesnt_fit
    get_next rax, rdx
    mov rax, rdx
    jmp .cycle

.break

    cmp rax, NULL
    jne .exit
    mov rax, rdi
    call allocate_new_chunk

.exit

    pop rdi
    pop rdx
    pop r11
    pop rcx
    ret


;rdi - pointer to memory
cmm_free:
    push rcx
    push r11
    push rdx
    push rdi
    push r8
    push rax

    sub rdi, chunk_info
    set_free rdi
    get_prev rdi, rax
    ;rax - pointer to previous chunk
    ;rdi - pointer to current chunk
    cmp rax, NULL
    je .dont_merge_prev

    xor rdx, rdx
    get_state rax, dl
    cmp dl, filled_chunk
    je .dont_merge_prev

    ;check if current chunk is last
    cmp rdi, [last_chunk]
    jne .not_last2
    mov [last_chunk], rax
.not_last2

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

    ;check if rax is last chunk
    cmp [last_chunk], rax
    jne .not_last
    mov [last_chunk], rdi
.not_last

    ;merging current chunk and next chunk
    ;set next chunk in rdi
    get_next rax, rcx
    set_next rdi, rcx

    ;set prev chunk
    cmp rcx, NULL
    je .here2
    set_prev rcx, rdi
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
    cmp dl, filled_chunk
    je .exit
    ; rax - last chunk
    ; rdx - before the last

    get_prev rax, rdx
    cmp rdx, NULL
    je .null2
    mov rcx, NULL
    set_next rdx, rcx
.null2
    mov [last_chunk], rdx

    mov rcx, NULL
    cmp [last_chunk], rcx
    jne .not_null2
    mov [first_chunk], rcx
.not_null2

    mov rdi, rax
    mov rax, sys_brk
    syscall
    mov [current_break], rax

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
    cmp rdi, NULL
    je .null
    set_next rdi, rax
.null
    ;filling next
    mov rdi, NULL
    set_next rax, rdi
    ;set_filled
    set_filled rax
    ;set_len
    set_len rax, edx


    pop rax
    mov rdx, [current_break]
    mov [last_chunk], rdx
    mov [current_break], rax
    mov rax, rdx

    mov rcx, NULL
    cmp [first_chunk], rcx
    jne .not_null
    mov [first_chunk], rax
.not_null

    add rax, chunk_info

.exit
    ret
