bits 32 
global encode

segment data use32 public data
    alphabet db "OPQRSTUVWXYZABCDEFGHIJKLMN", 0
                        
segment code use32 public code
    ; Read a string s1 (which contains only lowercase letters). 
    ; Using an alphabet (defined in the data segment), determine and 
    ; display the string s2 obtained by substitution of each letter of the string s1 
    ; with the corresponding letter in the given alphabet.
    ; Example:
    ; The alphabet:  OPQRSTUVWXYZABCDEFGHIJKLMN
    ; The string s1: anaaremere
    ; The string s2: OBOOFSASFS
    encode:
        ; s1: [esp + 4]
        ; s2: [esp + 8]
        mov esi, [esp + 4]
        mov edi, [esp + 8]
        
        cld
        
        repeat: 
            lodsb
            cmp al, 0
            je end
            sub al, 'a'
            mov ebx, alphabet
            xlat
            stosb
        loop repeat
        
        end:
        ret
