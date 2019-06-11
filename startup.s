;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	AREA USER_STACK,NOINIT,READWRITE
MSP_SIZE EQU 0x00004000
MSP_STACK
	SPACE MSP_SIZE
MSP_TOP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	AREA CACHE,NOINIT,READWRITE
CACHE_SIZE EQU 0x00000040
CACHE_START
	SPACE CACHE_SIZE
CACHE_END

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	EXPORT __Vectors_End
	EXPORT __Vectors_Size
__Vectors
	DCD MSP_TOP;0
	DCD Reset_Handler;1
	DCD Reset_Handler;2
	DCD Reset_Handler;3
	DCD Reset_Handler;4
	DCD Reset_Handler;5
	DCD Reset_Handler;6
	DCD Reset_Handler;7
	DCD Reset_Handler;8
	DCD Reset_Handler;9
	DCD Reset_Handler;a
	DCD SYS_HANDLER;b
	DCD Reset_Handler;c
	DCD Reset_Handler;d
	DCD Reset_Handler;e
	DCD SYS_HANDLER;f
__Vectors_End
__Vectors_Size EQU __Vectors_End-__Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	PRESERVE8
	AREA |.TEXT|,CODE,READONLY
	EXPORT Reset_Handler [WEAK]
	IMPORT main
	IMPORT task_list
	IMPORT taskpid;
	IMPORT current
	IMPORT task1
	IMPORT task2
	IMPORT task3
	IMPORT value1
	IMPORT value2

Reset_Handler PROC
	LDR R0,=__Vectors
	LDR R1,=__Vectors_End
	LDR R2,=MSP_STACK
	LDR R3,=CACHE_START
	LDR R4,=task_list
	LDR R5,=taskpid;
	LDR R6,=current
	LDR R7,=task1
	LDR R8,=task2
	LDR R9,=task3
	LDR R10,=value2

	LDR R4,=main
	BLX R4
	B .
	ENDP

SYS_HANDLER PROC
	MRS R0,PSP
	STMDB R0!,{R4-R11}
	LDR R1,=current
	LDR R2,[R1]
	STR R0,[R2]
	LDR R0,[R2,#0x04]
	STR R0,[R1]
	LDR R0,[R0]
	LDMIA R0!,{R4-R11}
	MSR PSP,R0
 	BX LR
	ENDP

	END