.model small
.stack
print macro p
            lea dx,p
            mov ah,09h
            int 21h
endm
.data
            m1 db 0ah,0dh,"Enter the String: $"
            m2 db 0ah,0dh,"String is palindrome$"
            m3 db 0ah,0dh,"String is not palindrome$"
            a db 20h dup("$");
            k dw 0
            f dw 0
.code
            mov ax,@data
            mov ds,ax
            mov es,ax
            mov si,0000h
            print m1

loop1:  mov ah,01h
            int  21h
            mov a[si],al
            inc si
            inc k
            cmp al,0dh
            jne loop1
           
            mov cx,k
            mov di,0000h
            dec si
            dec si
            mov di,0000h
            dec cx

loop3:  mov bh,a[si]
            mov bl,a[di]
            dec si
            inc di
            cmp bh,bl
            jne l3
            cmp di,cx
            jne loop3

            print m2
            jmp l5

l3:        print m3
l5:        mov ah,4ch
            int 21h
end