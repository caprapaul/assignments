bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a2 dw 4
    b2 dw 3
    c2 dw 2
    d2 dw 1
    r2 dw 0

segment code use32 class=code
    start:        
        ;(c+d)+(a-b)+a 
        
        mov ax, [c2]    ; ax = c
        add ax, [d2]    ; ax = c+d = 3
        
        mov bx, [a2]    ; bx = a
        sub bx, [b2]    ; bx = a-b = 1
        
        add ax, bx      ; ax = (c+d)+(a-b)
        add ax, [a2]    ; ax = (c+d)+(a-b)+a = 3+1+4 = 8
        mov [r2], ax    ; r = 8 = 0008h
        
        ; exit(0)
        push dword 0
        call [exit]
