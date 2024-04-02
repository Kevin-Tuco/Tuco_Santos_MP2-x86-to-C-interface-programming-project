section .data
z times 134217728 dq 0
msg1 db 10,"Resulting array OutAsm:",10,0
msg2 db "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",10,0

section .text
bits 64
default rel

global daxpyAsm
extern printf

daxpyAsm:
	lea rsi, z	; store address of z into rsi
	lea r10, [r8]	; store address of 3rd parameter (1st array) into r10
	lea r11, [r9]	; store address of 4th parameter (2nd array) into r11
	mov rbx, 0

	; loop based on rcx (1st parameter)
	l1: movsd xmm2, xmm1
	movsd xmm3, [r10+rbx*8]
	movsd xmm4, [r11+rbx*8]

	mulsd xmm2, xmm3
	addsd xmm2, xmm4

	movsd [rsi+rbx*8], xmm2
	
	inc rbx
	
	loop l1
	mov rax, rsi

Print:
	;Print First Message
	sub rsp, 8*5; needed if assembly is the caller
	lea rcx, [msg1] ; 1st parameter
	call printf
	add rsp, 8*5

	;Print Second Message
	sub rsp, 8*11
	mov rax, [z+72]
	mov [rsp+80],rax	; 11th parameter
	mov rax, [z+64]
	mov [rsp+72],rax	; 10th parameter
	mov rax, [z+56]
	mov [rsp+64],rax	; 9th parameter
	mov rax, [z+48]
	mov [rsp+56],rax	; 8th parameter
	mov rax, [z+40]
	mov [rsp+48],rax	; 7th parameter
	mov rax, [z+32]
	mov [rsp+40],rax	; 6th parameter
	mov rax, [z+24]
	mov [rsp+32],rax	; 5th parameter
	mov r9, [z+16]		; 4th parameter
	mov r8, [z+8]		; 3rd parameter
	mov rdx, [z]		; 2nd parameter
	mov rcx, msg2		; 1st parameter
	call printf
	add rsp, 8*11
	ret