bits 32

global start        

extern exit
import exit msvcrt.dll

; 23
; Being given a string of bytes, build a string of words which contains 
; in the low bytes of the words the set of distinct characters from the given string 
; and in the high byte of a word it contains the number of occurrences of the low byte 
; of the word in the given byte string.

segment data use32 class=data
    s db 2, 4, 2, 5, 2, 2, 4, 4
    len equ ($ - s)
    r times (len) dw 0      ; 0402h, 0304h, 0105h
    

segment code use32 class=code
    start:
        mov esi, s
        cld
        mov ecx, len
        jecxz program_end   ; end program if len is 0
        
        loop_1:
            lodsb           ; al = s(i)
            mov bl, al      ; bl = s(i)
            
            push esi
            
            mov esi, r
            mov edi, r
            loop_2:
                lodsw               ; ax = r(j)
                cmp al, bl  
                je increase_count   ; if r_low(j) == s(i)
                cmp ah, 0
                jne next            ; if r_high(j) != 0
                
                mov al, bl          ; al = s(i)
                
                increase_count:
                inc ah
                stosw               ; r(j) = count(s(i):s(i)
                jmp end_loop_2
                
                next:
                add edi, 2
                jmp loop_2
                
            end_loop_2:
            
            pop esi
            
        loop loop_1
        
        
        program_end:
        
        ; exit(0)
        push dword 0
        call [exit]
