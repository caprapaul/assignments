bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a1 db 1
    b1 db 2
    c1 db 3
    d1 db 4
    r1 db 0

segment code use32 class=code
    start:
        ; (a+d-c)-(b+b)
        
        mov al, [a1]    ; al = a
        add al, [d1]    ; al = a+d
        sub al, [c1]    ; al = a+d-c = 2
        
        mov bl, [b1]    ; bl = b
        add bl, [b1]    ; bl = b+b = 4
        
        sub al, bl      ; al = (a+d-c)-(b+b) = 2-4 = -2 = 254
        mov [r1], al    ; r = 254 = FEh
        
        ; exit(0)
        push dword 0
        call [exit]
