.text
    .global ListSearch
ListSearch:
        .intel_syntax noprefix
        
        vlddqu ymm1, [rsi]

        mov     rax, QWORD PTR [rdi+24]
        mov     r8, QWORD PTR [rdi+16]
        xor     edi, edi
        lea     rax, [rax+rax*2]
        lea     rax, [r8+rax*8]
        test    rax, rax
        jne     .L2
        ret
.L4:
        mov     edx, edi

        vptest ymm1, [rcx]
        setc dl

        test    edx, edx
        je      .L5
        mov     rax, QWORD PTR [rax+16]
        lea     rax, [rax+rax*2]
        lea     rax, [r8+rax*8]
        test    rax, rax
        je      .L6
.L2:
        mov     rcx, QWORD PTR [rax+8]
        test    rcx, rcx
        jne     .L4
.L6:
        xor     eax, eax
        ret
.L5:
        mov     eax, 1

        vzeroupper

        ret