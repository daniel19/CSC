.intel_syntax noprefix
;.set ERROR_MSG_LEN, 25
;.set first_arg, bp+4
;.equ, second_arg, bp+8

;`.extern curProcess

.global writeScr ;write screen definition and declaration


writeScr: ; label 
    push ebp ;move ebp onto stack
    mov ebp, esp ;move esp to ebp
    
    pushf ; pushing flags register onto the stack
    push eax 

    mov eax, [ebp+8] ; move string into eax register
    cpm eax, 0
    jne done_printing
    mov esi, [ebp+12] ;address of row
    mov ebx, [ebp+14] ;address of column
    
    ;testing video memory
    imul ecx, esi, 0x50 ; 0x50 = 80
    add ecx,ebx
    imul ecx,0x02
    add exc,0xB8000


;print:
 ;   cmpb [esi],0
 ;   je done_printing
    ;print code
    ;mov first char into video memory
    ;Video Memory begins at 0xB8000

;    jmp print
done_printing:
    pop eax
    popf
    pop ebp
    ret
    ;end code

