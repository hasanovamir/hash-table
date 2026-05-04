segment .text
global HashFindElementAsm:function (HashFindElementAsm_end - HashFindElementAsm)
extern memcmp

HashFindElementAsm:

;==============================================

    push    r13
    push    r14

;==============================================

    mov     r8, rdx    ;r8 = str_len
    mov     r13, rcx    ;r13 = hash
    mov     r14, rsi    ;r14 = str

;————————————————————————————————————————————————————————————————————————————————

    movabs  r11, 1843384038543976
    mov     rax, r13
    mul     r11
    imul    r11, rdx, 10007
    sub     rcx, r11
    jns     .rem_ok
    add     rcx, 10007

;————————————————————————————————————————————————————————————————————————————————

.rem_ok:

    cmp     rcx, 10007
    jae     .not_found

;list_t* target_list = hash_ctx->src[rcx]
    mov     rax, [rdi]
    mov     rax, [rax + rcx*8]
    test    rax, rax
    jz      .not_found

;r12d = size
    mov     r12d, [rax + 36]
    test    r12d, r12d
    jle     .not_found

    mov     r11, [rax]
    test    r11, r11
    jz      .not_found

    mov     eax, 1
.loop:
    cmp     eax, r12d
    jg      .not_found

;data[i]
    imul    rdx, rax, 24
    add     rdx, r11

;===========STR_CMP===================================

    cmp     qword [rdx], r8
    jne     .next

;============HASH_CMP==================================

    cmp     qword [rdx + 8], r13
    jne     .next

;—————————————————————MEMCMP———————————————————————————————————————————————————————————

    mov     rdi, r14
    mov     rsi, [rdx + 16]
    mov     rdx, r8
    call    memcmp wrt ..plt
    test    eax, eax
    je      .found

;==============================================

.next:
    inc     eax
    jmp     .loop

;==============================================    

.not_found:
    xor     eax, eax
    jmp     .exit

;==============================================

.found:
    mov     eax, 1

;==============================================

.exit:
    
    pop     r14
    pop     r13
    
    ret

HashFindElementAsm_end: