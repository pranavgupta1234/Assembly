;
; Objective: Check whether a string is palindrome or not 
; Input: Takes a string 
; Output: Yes or No

%include "io.mac"

.DATA
prompt_msg1   db   "Please input the string you want to check : ",0
output_msg_1  db   "Yes ",0
output_msg_2  db   "No ",0

.UDATA 
number1   resd   1 
number2   resd   1

.CODE
      .STARTUP
      PutStr  prompt_msg1    ; request first number 
      GetStr  CX             ; CX= first number  

      PutStr  prompt_msg2    ; request second number 
      GetInt  DX             ; DX= second number  
 
      mov AX, CX
      add AX, DX      
      PutStr  output_msg   
      PutInt   AX
  nwln 
done:
      .EXIT