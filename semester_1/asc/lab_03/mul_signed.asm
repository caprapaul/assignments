bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    a dw 1
    b db 2
    c dw 3
    d dd 4
    x dq 5
    r dq 0

segment code use32 class=code
    start:
        ; (a*a+b/c-1)/(b+c)+d-x
        
        mov ax, [a]
        imul word ax        ; dx:ax = a*a
        mov bx, dx  
        shl ebx, 2 * 8  
        mov bx, ax          ; ebx = a*a
            
        mov al, [b] 
        cbw
        cwd                 ; dx:ax = b
        idiv word [c]       ; ax = b/c
        cwde                ; eax = b/c
        add eax, ebx        ; eax = a*a+b/c
        sub eax, 1          ; eax = a*a+b/c-1
            
        mov bx, ax  
        shr eax, 2 * 8  
        mov dx, ax  
        mov ax, bx          ; dx:ax = a*a+b/c-1
        
        mov cx, ax
            
        mov al, [b] 
        cbw                 ; ax = b
        add ax, [c]         ; ax = b+c
        mov bx, ax          ; bx = b+c
        
        mov ax, cx
            
        idiv word bx        ; ax = (a*a+b/c-1)/(b+c)
        cwde                ; eax = (a*a+b/c-1)/(b+c)
        add eax, [d]        ; eax = (a*a+b/c-1)/(b+c)+d
        
        cdq                 ; edx:eax = (a*a+b/c-1)/(b+c)+d
        sub eax, dword[x]
        sbb edx, dword[x+4] ; edx:eax = (a*a+b/c-1)/(b+c)+d-x
        
        mov dword [r], eax
        mov dword [r+4], edx    ; r = (a*a+b/c-1)/(b+c)+d-x = (1*1+2/3-1)/(2+3)+4-5 = -1 = FF FF FF FF FF FF FF FFh
        
        ; exit(0)
        push dword 0
        call [exit]
