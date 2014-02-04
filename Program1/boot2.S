.intel_syntax noprefix
.set ERROR_MSG_LEN, 25
.set first_arg, bp+4
.equ, second_arg, bp+8

.extern curProcess

.global writeScr ;write screen definition and declaration


writeScr: ; label 
    ;move ebp onto stack
    ;move esp to ebp


