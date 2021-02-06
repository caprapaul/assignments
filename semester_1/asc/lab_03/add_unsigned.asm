bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a db 1
    b dw 2
    c dd 3
    d dq 4
    r dq 0
    
segment code use32 class=code
    start:
        ; (c-b+a)-(d+a)
        
        mov eax, [c]            ; ecx = c
        mov ebx, 0
        mov bx, [b]             ; ebx = b
        sub eax, ebx            ; eax = c - b
        mov ebx, 0
        mov bl, [a]             ; ebx = a
        add eax, ebx            ; eax = c - b + a
        
        mov ebx, eax            ; ebx = c - b + a = 2
        
        mov eax, dword [d]
        mov edx, dword [d+4]    ; edx:eax = d
        
        add al, [a]
        adc ah, 0               ; edx:eax = d + a = 5
        
        mov ecx, 0
        sub ebx, eax
        sbb ecx, edx            ; ecx:ebx = (c - b + a) - (d + a)
        
        mov dword [r], ebx
        mov dword [r+4], ecx    ; r = (c - b + a) - (d + a) = (3 - 2 + 1) - (4 + 1) = -3 = FF FF FF FF FF FF FF FDh
        
        ; exit(0)
        push dword 0
        call [exit]
