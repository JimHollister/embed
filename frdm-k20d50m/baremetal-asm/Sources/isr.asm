	.text
	.section .text
	
	.global isr_default
	
isr_default:
	bx	lr		; Return from interrupt
	
	.end
