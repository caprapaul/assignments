bits 32
global start

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
extern exit, scanf, printf

extern encode

segment data use32
    s1 resb 32
    s2 resb 32
    message_in db "input = ", 0
    format_string db "%31s", 0
	format_out db "encoded = %s", 0

segment code use32 public code
    start:
        ; printf(message_in)
        push dword message_in
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_string, s1)
        push dword s1
        push dword format_string
        call [scanf]
        add esp, 4 * 2
        
        ; encode(s1, s2)
        push dword s2
        push dword s1
        call encode
        add esp, 4 * 2

        ; printf(format_out, s2)
        push dword s2
        push dword format_out
        call [printf]
        add esp, 4 * 2

        push 0
        call [exit]
