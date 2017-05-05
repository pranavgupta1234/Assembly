%include "io.mac"


%macro printij 2

	PutStr obrac
	PutInt %1
	PutStr cbrac
	PutStr obrac
	PutInt %2
	PutStr cbrac
	PutStr colon

%endmacro

.DATA
	rowPrompt	db	"Enter the number of rows in the matrix (max. 10) : ", 0
	colPrompt	db	"Enter the number of columns in the matrix (max. 10): ", 0
	valPrompt	db	"Enter the elements ", 0

	colon	db 	": ",0
	obrac 	db 	"[",0
	cbrac 	db 	"]",0
	tab	  	db 	9, 0


	mat1Msg		db	"First matrix : ", 0
	mat2Msg		db	"Second matrix : ", 0
	fMatMsg		db	"Final matrix : ", 0
  
.UDATA
	val		resd	1 ;For storing a number, to be read of printed....
	nod		resd 	1 ;For storing the number of digits....
	temp: 	resb 2
	
	mat1 	resd 	100
	mat2 	resd 	100
	fMat 	resd 	100
	
	m: resd 1
	n: resd 1
	i: resd 1
	j: resd 1


.CODE

	.STARTUP

		.main:

			PutStr rowPrompt
			GetInt word[m]

			cmp word[m],10
			jnl done

			PutStr colPrompt
			GetInt word[n]

			cmp word[n],10
			jnl done
  
  			PutStr mat1Msg
  			nwln
  			mov ebx, mat1
  			call read_matrix
  			nwln

			PutStr mat2Msg
  			nwln
  			mov ebx, mat2
  			call read_matrix
  			nwln

  			call matrix_add

  			mov ebx, mat1
  			PutStr mat1Msg
  			nwln
  			call display
  			nwln

  			mov ebx, mat2
  			PutStr mat2Msg
  			nwln
  			call display

  			mov ebx, fMat
  			PutStr fMatMsg
  			nwln
  			call display
  			nwln

  		done:
  			.EXIT

  		read_matrix:

  			push ebx
  			mov eax, 0

  			mov word[i], 0
  			mov word[j], 0
  
  			rl_mat:
    			mov word[j], 0

    			cl_mat:

 				printij word[i], word[j]
 				
		 		GetInt word[val]
		 		mov dx, word[val]
		 		mov  word[ebx + 2 * eax], dx
		 		
		 		inc eax
		     
		 		inc word[j]
		 		mov cx, word[j]
		 		cmp cx, word[n]
		 		jb cl_mat
		 
    		inc word[i]
    		mov cx, word[i]
    		cmp cx, word[m]
    		jb rl_mat

    		pop ebx

    		ret

    	matrix_add:

    		mov eax, 0
    		mov ebx, fMat
    		mov esi, mat1
    		mov edi, mat2

  			mov word[i], 0
  			mov word[j], 0
  
  			rl_fMat:
    			mov word[j], 0
    			cl_fMat:
 
 				mov dx, word[esi + 2 * eax]
		 		mov  word[ebx + 2 * eax], dx
		 		mov dx, word[edi + 2 * eax]
		 		add  word[ebx + 2 * eax], dx
		 		
		 		inc eax

		 		inc word[j]
		 		mov cx, word[j]
		 		cmp cx, word[n]
		 		jb cl_fMat
		 
    		inc word[i]
    		mov cx, word[i]
    		cmp cx, word[m]
    		jb rl_fMat    

    		ret

    	display:

    		push ebx
  			mov eax, 0

  			mov word[i], 0
  			mov word[j], 0
  
  			rl_pmat:
    			mov word[j], 0
    			cl_pmat:

		 		mov dx, word[ebx + 2 * eax]
		 		PutInt dx
		 		
		 		inc eax
		     	
		     	PutStr tab

		 		inc word[j]
		 		mov cx, word[j]
		 		cmp cx, word[n]
		 		jb cl_pmat

		 	nwln
		 
    		inc word[i]
    		mov cx, word[i]
    		cmp cx, word[m]
    		jb rl_pmat

    		pop ebx

    		ret




  		

