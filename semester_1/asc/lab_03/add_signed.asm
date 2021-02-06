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
        ; (c-d-a)+(b+b)-(c+a)
        
        mov ax, [b]
        add ax, [b]
        cwde                ; eax = b+b
        mov ebx, eax        ; ebx = b+b
        
        mov al, [a]
        cbw
        cwde                ; eax = a
        add eax, [c]        ; eax = c+a
        sub ebx, eax        ; ebx = (b+b)-(c+a)
        
        mov al, [a]
        cbw
        cwde
        mov ecx, eax        ; ecx = a
        mov eax, [c]        ; eax = c
        sub eax, ecx        ; eax = c-a
        cdq                 ; edx:eax = c-a
        sub eax, dword [d]
        sbb edx, dword [d+4]; edx:eax = c-d-a
        
        add eax, ebx
        adc edx, 0          ; edx:eax = (c-d-a)+(b+b)-(c+a)
        
        mov dword [r], eax
        mov dword [r+4], edx    ; r = (c-d-a)+(b+b)-(c+a) = (3-4-1)+(2+2)-(3+1) = -2 = FF FF FF FF FF FF FF FEh
        
        ; exit(0)
        push dword 0
        call [exit]
