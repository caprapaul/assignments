bits 32

global start        

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; 15
; A file name and a text (defined in the data segment) are given. 
; The text contains lowercase letters, uppercase letters, digits and special characters. 
; Replace all the special characters from the given text with the character 'X'. 
; Create a file with the given name and write the generated text to file. 

segment data use32 class=data
    text db "a#bCd1)23[4{}5;", 0    ; aXbCd1X23X4XX5X
    len equ ($-text)
    
    file_name db "test.txt", 0
    access_mode db "w", 0
    file_descriptor dd -1

segment code use32 class=code
    start:
        ; fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je program_end      ; end program if file was not created successfully
        
        mov [file_descriptor], eax
        
        mov esi, text
        mov edi, text
        cld
        mov ecx, len
        jecxz close_file    ; close file if len is 0
        
        loop_1:
            lodsb           ; al = text(i)
            
            ; ' ' to '/'
            cmp al, ' '
            jb not_special
            cmp al, '/'
            jb special
            
            ; ':' to '@' 
            cmp al, ';'
            jb not_special
            cmp al, '@'
            jb special
            
            ; '[' to '`' 
            cmp al, '['
            jb not_special
            cmp al, '`'
            jb special
            
            ; '{' to '~' 
            cmp al, '{'
            jb not_special
            cmp al, '~'
            jb special
            
            special:
            mov al, "X"
            
            not_special:
            stosb
            
        loop loop_1
        
        ; fprintf(file_descriptor, text)
        push dword text
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 2
        
        close_file:
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4 * 1
        
        program_end:
        ; exit(0)
        push dword 0
        call [exit]
