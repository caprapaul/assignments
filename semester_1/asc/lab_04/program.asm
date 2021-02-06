bits 32

global start        

extern exit
import exit msvcrt.dll    

segment data use32 class=data
    M dd 10110100_11110000_00001101_00010110b
    N dd 01010101_00001111_11001100_00010001b
    P dd 0
    
segment code use32 class=code
    start:
        ; the bits 0-6 of P are the same as the bits 10-16 of M
        ; the bits 7-20 of P are the same as the bits 7-20 of (M AND N).
        ; the bits 21-31 of P are the same as the bits 1-11 of N.
        
        mov eax, [M]
        and eax, 00000000_00000001_11111100_00000000b   ; isolate bits 10-16 of M
        ror eax, 10
        or [P], eax ; the bits 0-6 of P are the same as the bits 10-16 of M
        
        mov eax, [M]
        and eax, [N]
        and eax, 00000000_00011111_11111111_10000000b   ; isolate bits 7-20 of (M AND N)
        or [P], eax ; the bits 7-20 of P are the same as the bits 7-20 of (M AND N).
        
        mov eax, [N]
        and eax, 00000000_00000000_00001111_11111110b   ; isolate bits 1-11 of N
        rol eax, 20
        or [P], eax ; the bits 21-31 of P are the same as the bits 1-11 of N.
        
        ;                         X_XXXXXX
        ; M     = 10110100_11110000_00001101_00010110b
        ;                               XXXX_XXXXXXX
        ; N     = 01010101_00001111_11001100_00010001b
        ;                     XXXXX_XXXXXXXX_X
        ; M&N   = 00010100_00000000_00001100_00010000b
        ; P     = 11000001_00000000_00001100_00000011b = C1000C03h
        
        ; exit(0)
        push dword 0
        call [exit]
