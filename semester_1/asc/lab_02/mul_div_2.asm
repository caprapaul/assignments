bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a2 db 1
    b2 db 2
    c2 db 3
    d2 db 4
    e2 dw 5
    f2 dw 6
    g2 dw 7
    h2 dw 8
    r2 dw 0

segment code use32 class=code
    start:
        ; a*d*e/(f-5) 
        
        mov al, [a2]    ; al = a = 1
        mul byte [d2]   ; ax = a*d = 4
        mul word [e2]   ; dx:ax = a*d*e = 20
        
        mov bx, [f2]    ; bx = f
        sub bx, 5       ; bx = f-5 = 1
        
        div bx          ; ax = a*d*e/(f-5) = 20/1 = 20
        mov [r2], al    ; r = 20 = 0014h
        
        ; exit(0)
        push dword 0
        call [exit]
