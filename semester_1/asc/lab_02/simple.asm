bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    r dw 0

segment code use32 class=code
    start:
        ; -2*5
        mov al, -2  ; al = -2 = 254
        mov bl, 5   ; bl = 5
        mul bl      ; ax = 254 * 5 = 1270
        mov [r], ax ; r = 1270 = 04F6h
        
        ; exit(0)
        push dword 0
        call [exit]
