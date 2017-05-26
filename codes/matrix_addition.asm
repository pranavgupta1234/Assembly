%include "io.mac"				; including the header library

;;-----------macro definition in assembly ---------------------
%macro  printij 2  											; printij is name of macro and 2 is number of arguments it receives			
    PutStr 	osqBr											; using PutStr macro defined in io.mac 
    PutInt 	%1 												; calling the first argument passed to this macro
    PutStr  csqBr
    PutStr 	osqBr
    PutInt  %2
    PutStr 	csqBr
    PutStr 	colon
%endmacro
;;-------------------------------------------------------------



.DATA

	msg1	db		"Enter number of rows : ",0					; number of rows
	msg2 	db 		"Enter number of columns : ",0				; number of columns
	
	msg3  	db 		"Enter the first matrix :",0				; Enter first matrix message
	msg4 	db 		"Enter the second matrix :",0				; Enter second matrix message
	msg5    db 		"The addition matrix is : ",0				; to show addition matrix
	msg6    db  	"First matrix is :: ",0						; show first matrix
	msg7 	db 		"Second matrix is :: ",0					; show second matrix

	osqBr   db      "[",0										; square brackets to print efficiently
	csqBr   db      "]",0  										; square brackets to print efficiently	
	space	db      " ",0										; space to print
	colon 	db 		":",0										; to print colon
	tab		db 		9,0											; this is initialization by ascii value (tab has ascii value 9)

.UDATA

	val 		resd 		1 									; to read a number from user
	
	rows		resd		1									; number of rows
	cols 		resd 		1									; number of columns
	matrix1 	resd		100									; first matrix 
	matrix2		resd		100 								; second matrix
	matrix3     resd        100  								; third matrix (1st + 2nd)

	n 			resd 		1 									; no of rows
	m 			resd 		1 									; no of columns 
	i 			resd 		1 									; iterator for row
	j 			resd		1 									; iterator for column


.CODE 															; macro for main code

	.STARTUP													; linker starts executing from here (code segment in memory)

	; ------ remember to use registers as to hold temporary values and once you shift some value in register and then use it immediately and ;--------------------------------  be careful to use it next time    -------------------------------------------------------------

	main :

		PutStr msg1												; prompt 1st message	
		GetInt word[n]											; as n lies in main memory and we have to explicitly tell the  												  			; size by typecasting as word
		cmp word[n],10											; compare the user input 
		jnl done												; close program if not less than 100

		PutStr msg2
		GetInt word[m] 											; store number of columns in m
		
		cmp word[m],10 											; compare and jump if not less 
		jnl done
		
  		PutStr msg3												; ask for first matrix
  		nwln													; newline macro
  		mov ecx, matrix1										; move address of matrix1 to ecx
  		call read_matrix
  		nwln

  		PutStr msg4 											;
  		nwln
  		mov ecx,matrix2
  		call read_matrix
  		nwln

  		call matrix_add

  		PutStr msg6
  		nwln
  		mov ecx,matrix1
  		call display_matrix
  		nwln

  		PutStr msg7
  		nwln
  		mov ecx,matrix2
  		call display_matrix
  		nwln

  		PutStr msg5
  		nwln
  		mov ecx,matrix3
  		call display_matrix
  		nwln

  	done:

		.EXIT

	read_matrix :

		push ecx 												; we push certain value that may be of use later(as we pop) so 
		mov eax,0												; now we can use this ecx register for some other use here it
																; doen't matter
		mov word[i],0											; initialise values of i and j as 0
		mov word[j],0										

		row_iterator:

			mov word[j],0

			col_iterator:

				printij word[i], word[j]

				GetInt word[val] 
				mov dx,word[val]
				mov word[ecx + 2*eax],dx

				inc eax

				inc word[j]
				mov bx,word[j]
				cmp bx,word[m]
				jb col_iterator

			inc word[i]
			mov bx,word[i]
			cmp bx,word[n]
			jb row_iterator

		pop ecx

		ret

	matrix_add:

		mov eax,0
		mov edx,matrix3
		mov esi,matrix1
		mov edi,matrix2

		mov word[i],0											; initialise values of i and j as 0
		mov word[j],0										

		row_iterator_add :

			mov word[j],0

			col_iterator_add :
 
				mov cx,word[esi + 2*eax]
				mov word[edx + 2*eax],cx
				mov cx,word[edi + 2*eax]
				add word[edx + 2*eax],cx

				inc eax

				inc word[j]
				mov cx,word[j]
				cmp cx,word[m]
				jb col_iterator_add

			inc word[i]
			mov cx,word[i]
			cmp cx,word[n]
			jb row_iterator_add

		ret

	display_matrix :

		push ecx
		mov eax,0

		mov word[i],0											; initialise values of i and j as 0
		mov word[j],0										

		row_iterator_display :

			mov word[j],0

			col_iterator_display :

				mov dx,word[ecx + 2*eax]

				PutInt dx

				inc eax
				PutStr tab

				inc word[j]
				mov bx,word[j]
				cmp bx,word[m]
				jb col_iterator_display

			nwln
			inc word[i]
			mov bx,word[i]
			cmp bx,word[n]
			jb row_iterator_display

		pop ecx

		ret

