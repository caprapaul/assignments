bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a1 db 1
    b1 db 2
    c1 db 3
    d1 dw 4
    r1 db 0

segment code use32 class=code
    start:
        ; (d-b*c+b*2)/a 
        
        mov bx, [d1]    ; bx = d = 4
        
        mov al, [b1]    ; al = b
        mul byte [c1]   ; ax = b*c = 6
        sub bx, ax      ; bx = d-b*c
        
        mov al, [b1]    ; al = b
        mov cl, 2       ; cl = 2
        mul cl          ; ax = b*2 = 4
        add bx, ax      ; bx = d-b*c+b*2
        
        mov ax, bx      ; ax = d-b*c+b*2
        div byte [a1]   ; al = (d-b*c+b*2)/a = (4-6+4)/1 = 2
        
        mov [r1], al    ; r = 2 = 02h
        
        ; exit(0)
        push dword 0
        call [exit]
