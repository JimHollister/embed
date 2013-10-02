	.text
	.section .text
	
	.global wdog_unlock
	.global wdog_disable

wdog_unlock:
	push {r0,r1}
	
	movw r0,#0x200E
	movt r0,#0x4005
	movw r1,#0xC520
	strh r1,[r0,#0]
	movw r1,#0xD928
	strh r1,[r0,#0]
	
	pop {r0,r1}
	bx lr
	
wdog_disable:
	push {r0,r1}
	
	movw r0,#0x2000
	movt r0,#0x4005
	mov r1,#0xD2
	strh r1,[r0,#0]
	
	pop {r0,r1}
	bx lr
	
	.end
