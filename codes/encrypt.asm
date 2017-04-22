;
;     Input string and output encrypted string
%include "io.mac"

.DATA
    prompt_for_data     db   "Input data : ",0
    output_message      db   "The Encrypted string is:",0
    prompt_again        db   "Do you want to encrypt again(y/n)?: ",0

.UDATA 
    strVar      resd 80
    newStr      resd 80
    strlen      resd 1

.CODE
      .STARTUP
      input:
      PutStr  prompt_for_data   ; request first number 
      GetStr  strVar             
      
      mov EAX,0
      cal_len:
            mov DL, [strVar+EAX] 
            INC EAX
            CMP DL,0
            JNE cal_len

      mov [strlen], EAX
      mov EBX,0
      convert:
        mov DL,[strVar,EBX]
        mov [newStr,EBX],DL
        CMP DL,'0'
        JE ch0
        CMP DL,'1'
        JE ch1
        CMP DL,'2'
        JE ch2
        CMP DL,'3'
        JE ch3
        CMP DL,'4'
        JE ch4
        CMP DL,'5'
        JE ch5
        CMP DL,'6'
        JE ch6
        CMP DL,'7'
        JE ch7
        CMP DL,'8'
        JE ch8
        CMP DL,'9'
        JE ch9
        INC EBX
        CMP [strlen], EBX
        JE print_result
        JMP convert     
      ch0: 
        mov byte [newStr+EBX],'4'
        INC EBX
        JMP convert
      ch1: 
        mov byte [newStr+EBX],'6'
        INC EBX
        JMP convert
      ch2: 
        mov byte [newStr+EBX],'9'
        INC EBX
        JMP convert
      ch3: 
        mov byte [newStr+EBX],'5'
        INC EBX
        JMP convert
      ch4:
        mov byte [newStr+EBX],'0'
        INC EBX
        JMP convert
      ch5:
        mov byte [newStr+EBX],'3'
        INC EBX
        JMP convert
      ch6:
        mov byte [newStr+EBX],'1'
        INC EBX
        JMP convert
      ch7:
        mov byte [newStr+EBX],'8'
        INC EBX
        JMP convert
      ch8:
        mov byte [newStr+EBX],'7'
        INC EBX
        JMP convert
      ch9:
        mov byte [newStr+EBX],'2'
        INC EBX
        JMP convert

      print_result:
          PutStr  newStr
          nwln 

      re_prompt:
          PutStr  prompt_again
          GetCh   AL
          CMP AL, 'y'
          JE input
          CMP AL, 'Y'
          JE input
done:
      .EXIT
