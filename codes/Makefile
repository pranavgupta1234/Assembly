Program : matrix_addition.o matrix_addition_c.o

	ld -m elf_i386 -o matrix_addition matrix_addition.o io.o
	gcc -w -o matrix_addition_c matrix_addition_c.o -Wno-Deprecated 
	
matrix_addition.o : matrix_addition.asm
	
	nasm -f elf -o matrix_addition.o matrix_addition.asm	

matrix_addition.lst : matrix_addition.asm

	nasm -f elf -g -F stabs matrix_addition.asm -l matrix_addition.lst

matrix_addition_c.o : matrix_addition_c.c

	gcc -c -o matrix_addition_c.o matrix_addition_c.c -Wno-deprecated

clean :
	
	rm -f *.o