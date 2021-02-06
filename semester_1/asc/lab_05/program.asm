bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    s db 1, 2, 3, 4
    l equ ($ - s)
    d times (l - 1) dw 0

segment code use32 class=code
    start:
        ; Given a byte string S of length l, obtain the string D of length l-1 as
        ; D(i) = S(i) * S(i+1) 
        ; (each element of D is the product of two consecutive elements of S). 
        
        mov ecx, l - 1
        
        cmp ecx, -1
        je program_end      ; end program if l is 0
        mov esi, 0
        jecxz program_end   ; end program if l is 1
        
        loop_1:
            mov al, [s + esi]       ; al = s(i)
            mul byte [s + esi + 1]  ; ax = s(i) * s(i+1)
            mov [d + esi * 2], ax   ; d(i) = s(i) * s(i+1)
            
            inc esi
        loop loop_1
        
        program_end:
        
        ; exit(0)
        push dword 0
        call [exit]
