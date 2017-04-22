;
;       Objective: find the sum of two numbers 
;       Input: Requests two  integers  from the user.
;       Output: Outputs the input number.

%include "io.mac"

.DATA
prompt_msg1  db   "Please input the first number : ",0
prompt_msg2  db   "Please input the second  number : ",0
output_msg  db   "The sum is :",0
.UDATA 
number1   resd   1 
number2   resd   1

.CODE
      .STARTUP
      PutStr  prompt_msg1   ; request first number 
      GetInt CX             ; CX= first number  

      PutStr  prompt_msg2   ; request second number 
      GetInt DX             ; DX= second number  
 
      mov AX, CX
      add AX, DX      
      PutStr  output_msg   
      PutInt   AX
  nwln 
done:
      .EXIT