data segment
    msg1 db 10,13,'Enter number of elements: $'
    msg2 db 10,13,'Enter element: $'
    msg3 db 10,13,'Enter key: $'
    msg4 db 10,13,'Key FOUND! $'
    msg5 db 10,13,'Key NOT FOUND! $'
    array db 50 dup(?)
    key db ?
    n db ?
ends

code segment
start:
    mov ax, data
    mov ds, ax
    mov es, ax
    lea dx,msg1
    mov ah,09h
    int 21h
    mov ah,01h
    int 21h
    sub al,30h
    mov n,al
    mov cl,n
    lea si,array
enter_value:
    lea dx,msg2
    mov ah,09h
    int 21h
    mov ah,01h
    int 21h
    sub al,30h
    mov [si],al
    inc si
    dec cl
    jnz enter_value
    lea dx,msg3
    mov ah,09h
    int 21h
    mov ah,01h
    int 21h
    sub al,30h
    mov cl,n
    mov key,al
    lea si,array
    
search_loop:
    mov al,[si]
    cmp key,al
    je found
    inc si
    dec cl
    jnz search_loop
    jmp not_found

found:
    lea dx,msg4
    mov ah,09h
    int 21h
    jmp exit

not_found:
    lea dx,msg5
    mov ah,09h
    int 21h
exit:
    mov ah,4ch
    int 21h
     
ends

end start