.intel_syntax noprefix

.global writeScr #write screen definition and declaration


writeScr: # label 
    push ebp #move ebp onto stack
    mov ebp, esp #move esp to ebp
    
    pushf # pushing flags register onto the stack
    push eax 
    push ebx
    push ecx


    mov esi, [ebp+8] # move string into esi register
    cmp esi, 0
    je done_printing
    mov eax, 0xB8000
    mov ebx, [ebp+12] #address of row
    mov ecx, [ebp+16] #address of column

    imul ebx,80
    add ebx,ecx
    imul ebx,2
    add ebx, eax
    mov edi, ebx
    
loop:
    cmpb [esi],0
    je done_printing
    movsb es:[edi], ds:[esi]
    movb es:[edi], 31
    
    inc edi
    jmp loop
done_printing:
    pop ecx
    pop ebx
    pop eax
    popf
    pop ebp
    ret
