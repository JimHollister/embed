	.text
	.section .text
	
	.global main
	
	.extern wdog_unlock
	.extern wdog_disable

main:
	cpsid i				; Disable interrupts while handling watchdog
	bl wdog_unlock		; Call routine to unlock watchdog
	bl wdog_disable		; Call routine to disable watchdog
	cpsie i				; Re-enable interrupts
	
countup:
	mov	r0, #0			; Zero the counter
incr:
	add r0, r0, #1		; Increment the counter
	b incr				; Repeat
	
	.end
