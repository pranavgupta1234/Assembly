;
;       Objective: find the sum of two numbers 
;       Input: Requests two  integers  from the user.
;       Output: Outputs the input number.
%include "io.mac"

.DATA
prompt_msg1  db   "Please input the first string : ",0
prompt_msg2  db   "Please input the second  string : ",0

output_msg2  db   "Palindrome",0
output_msg3  db   "Not A Palindrome",0

.UDATA 
var1   resd   80
var2   resd   80
var3   resd   1

.CODE
      .STARTUP
      PutStr  prompt_msg1   ; request first string 
      GetStr var1           ; get first string
      
      mov EAX,0
      len:
            mov DL, [var1+EAX] 
            INC EAX
            CMP DL,0
            JNE len

      mov [var3], EAX

      mov EBX,0
      sub EAX,2
      palin:
            mov DL,[var1,EBX]
            mov CL,[var1,EAX] 
            INC EBX
            DEC EAX

            CMP DL, CL
            JNE no_pal
            JE is_pal
            
      no_pal:
            mov ECX,1 
            JMP print
      is_pal:
            CMP [var3], EBX
            JE print
            mov ECX,0 
            JMP palin      

      print:   
            CMP ECX,1
            JE npal
            JNE pal
      npal:
            PutStr  output_msg3
            nwln
            JMP done
      pal:
            PutStr  output_msg2
            nwln
            JMP done
  nwln 
done:
      .EXIT







