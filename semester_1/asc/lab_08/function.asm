bits 32

global start        

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

; 15
; Read two numbers a and b (in base 10) from the keyboard and calculate a+b. 
; Display the result in base 16 

segment data use32 class=data
    a dd 0
    b dd 0
    message_a db "a = ", 0
    message_b db "b = ", 0
    message_sum db "a + b = %xh", 0
    format_dec db "%d", 0

segment code use32 class=code
    start:
        ; printf(message_a)
        push dword message_a
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_dec, a)
        push dword a
        push dword format_dec
        call [scanf]
        add esp, 4 * 2
        
        ; printf(message_b)
        push dword message_b
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_dec, b)
        push dword b
        push dword format_dec
        call [scanf]
        add esp, 4 * 2
        
        mov eax, [a]
        add eax, [b]
        
        ; printf(message_sum, eax)
        push dword eax
        push dword message_sum
        call [printf]
        add esp, 4 * 2
        
        ; exit(0)
        push dword 0
        call [exit]
