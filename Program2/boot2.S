
.intel_syntax noprefix
.global writeScr, protectedWrite, segLoader, lgdtLoad, go, schedule
.extern dequeue, enqueue, currPCB


writeScr:
    push ebp
    mov ebp, esp
    pushf
    push eax
    push ebx
    mov esi, [ebp+8]           //move address of string into esi
    mov eax, [ebp+12]          //move row into eax
    mov ebx, [ebp+16]          //move column into ebx
    /*calculate offset using equation
      offset = 0xB8000 + 2(row*80 + column)*/
    imul eax, 80
    add eax, ebx
    imul eax, 2
    add eax, 0xB8000
    mov edi, eax             //move offset into edi

loop:
    cmpb [esi], 0
    je done_printing
    movsb es:[edi], ds:[esi]
    movb es:[edi],31
    inc edi
    jmp loop

done_printing:
    pop ebx
    pop eax
    popf
    pop ebp
    ret


protectedWrite:
    push ebp
    mov ebp, esp
    pushf
    push eax
    push ebx
    push esi
    push edi
    push es
    mov esi, [ebp+8]
    mov eax, [ebp+12]
    mov ebx, [ebp+16]
    /*calculate offset
        offset = 2(row*80 + column)*/
    imul eax, 80
    add eax, ebx
    imul eax, 2
    mov edi, eax
    mov eax, 32
    mov es, eax

_protected_loop:
    cmpb [esi], 0
    je _protected_done
    movsb
    movb es:[edi], 31
    inc edi
    jmp _protected_loop

_protected_done:
    pop es
    pop edi
    pop esi
    pop ebx
    pop eax
    popf
    pop ebp
    ret

segLoader:
    push ebp
    mov ebp, esp
    pushf
    push eax

    mov eax, [ebp+12] // set up ds selector
    mov ds, eax
    mov eax, [ebp+20] // set up es selector
    mov es, eax
    mov eax, [ebp+20] // set up fs selector
    mov fs, eax
    mov eax, [ebp+20] // set up gs selector
    mov gs, eax
    mov eax, [ebp+16] // set up ss selector
    mov ss, eax
    mov eax, [ebp+8] // load cs 
    push eax
    push OFFSET _loadcs
    retf
_loadcs:
    pop eax
    popf
    pop ebp
    ret

lgdtLoad:
    push ebp
    mov ebp, esp
    pushf
    push eax
    /*load the pointer to the gdt to the hardware*/
    mov eax, [ebp+8]
    lgdt [eax]
    pop eax
    popf
    pop ebp
    ret

go:
    call dequeue
    mov [currPCB], eax
    mov esp, [eax]
    mov ss, [eax+4]
    pop gs
    pop fs
    pop es
    pop ds
    popad
    iret

schedule:
    pushf
    push cs
    push OFFSET _afterSwitch
    pushad
    push ds
    push es
    push fs
    push gs
    mov eax, [currPCB]
    mov [eax], esp
    push eax
    call enqueue
    call dequeue
    mov [currPCB], eax
    mov esp, [eax]
    mov ss, [eax+4]
    pop gs
    pop fs
    pop es
    pop ds
    popad
    iret
_afterSwitch:
    ret
