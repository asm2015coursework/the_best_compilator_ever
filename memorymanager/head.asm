;global malloc
;global free

%define sys_brk               12
%define chunk_info            21
%define NULL                  0
%define free_chunk            byte  0
%define filled_chunk          byte  1

%macro set_free 1
    mov [%1 + 16], free_chunk
%endmacro

%macro set_filled 1
    mov [%1 + 16], filled_chunk
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

