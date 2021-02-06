bits 32

global start        

extern exit, fopen, fread, fprintf, fclose, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    message_c db "c= ", 0
    message_n db "n= ", 0
    message_in db "in= ", 0
    
    format_c db "%c", 0
    format_n db "%d", 0
    format_s db "%s", 0
    
    in_f_name resb 32
    in_f_descriptor dd -1
    in_f_access db "r", 0
    
    out_f_name db "out.txt", 0
    out_f_descriptor dd -1
    out_f_access db "w", 0
    
    c db 0
    n db 0
    text resb 100
    len db 0
    counter db 0
    

segment code use32 class=code
    start:
        ; A character c, a number n (n<20) and the name of the input file 
        ; are read from the keyboard. Write the content of the input file 
        ; in other file, but replace the bytes from the positions that are 
        ; multiple of n with the character c.
        
        ; printf(message_c)
        push dword message_c
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_c, c)
        push dword c
        push dword format_c
        call [scanf]
        add esp, 4 * 2
        
        
        ; printf(message_n)
        push dword message_n
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_n, n)
        push dword n
        push dword format_n
        call [scanf]
        add esp, 4 * 2
        
        
        ; printf(message_in)
        push dword message_in
        call [printf]
        add esp, 4 * 1
        
        ; scanf(format_s, in_f_name)
        push dword in_f_name
        push dword format_s
        call [scanf]
        add esp, 4 * 2
        
        
        ; fopen(in_f_name, in_f_access)
        push dword in_f_access     
        push dword in_f_name
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je program_end
        mov [in_f_descriptor], eax
        
        
        ; fopen(out_f_name, out_f_access)
        push dword out_f_access     
        push dword out_f_name
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je close_in
        mov [out_f_descriptor], eax
        
        
        ;fread(text, 1, 100, in_f_descriptor)
        push dword [in_f_descriptor]
        push dword 100
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        mov [len], eax
        mov ecx, [len]
        jecxz close_out ; stop program if there's no text
        
        mov esi, text
        mov edi, text
        cld
        
        loop_1:
            lodsb   ; al = text(i)
            ; if counter is 0, the current position is a multiple of n
            cmp [counter], byte 0
            jne next
            
            ; replace current character with the character from c
            mov al, [c]
            
            next:
            stosb   ; text(i) = al
            inc byte [counter]
            ; check if counter is equal to n, that means the next position is a multiple of n
            ; so we set counter to 0, otherwise we skip to the next loop step
            mov bl, [n]
            cmp bl, [counter]
            jne next_end
            
            mov [counter], byte 0   ; counter = 0
            
        next_end:
        loop loop_1
            
        
        ;fprintf(out_f_descriptor, format_s, text)
        push dword text
        push dword format_s
        push dword [out_f_descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        close_out:
        ; fclose(out_f_descriptor)
        push dword [out_f_descriptor]
        call [fclose]
        add esp, 4 * 1
        
        close_in:
        ; fclose(in_f_descriptor)
        push dword [in_f_descriptor]
        call [fclose]
        add esp, 4 * 1
        
        program_end:
        ; exit(0)
        push dword 0
        call [exit]
