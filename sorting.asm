data segment
    msg1 db 10,13,'Enter number of elements in array: $'
    msg2 db 10,13,'Enter element: $'
    msg3 db 10,13,'Sorted array: $'
    array db 20 dup(?)
    n db ?
data ends

code segment
start:
    mov ax, data
    mov ds, ax

    lea dx, msg1
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    sub al, 30h
    mov n, al

    lea si, array
    mov cl, n
read_loop:
    lea dx, msg2
    mov ah, 09h
    int 21h
    mov ah, 01h
    int 21h
    sub al, 30h
    mov [si], al
    inc si
    dec cl
    jnz read_loop

    mov ch, n
outer_loop:
    dec ch
    jz done_sorting
    lea si, array
    mov cl, n
    dec cl
inner_loop:
    mov al, [si]
    mov bl, [si+1]
    cmp al, bl
    jbe no_swap
    mov [si], bl
    mov [si+1], al
no_swap:
    inc si
    dec cl
    jnz inner_loop
    jmp outer_loop

done_sorting:
    lea dx, msg3
    mov ah, 09h
    int 21h

    lea si, array
    mov cl, n
print_loop:
    mov dl, [si]
    add dl, 30h
    mov ah, 02h
    int 21h
    mov dl, ' '
    mov ah, 02h
    int 21h
    inc si
    dec cl
    jnz print_loop

    mov ah, 4Ch
    int 21h

code ends
end start
