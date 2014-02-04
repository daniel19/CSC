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


