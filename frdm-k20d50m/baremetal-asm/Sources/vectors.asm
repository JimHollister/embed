	.data
	.section .vectortable
	
	.extern __SP_INIT
	.extern main
	.extern isr_default
	
	.long __SP_INIT			; Initial SP value
	.long main				; 1, Reset
	.long isr_default		; 2, NMI
	.long isr_default		; 3, Hard fault
	.long isr_default		; 4, Memory management fault
	.long isr_default		; 5, Bus fault
	.long isr_default		; 6, Usage fault
	.long isr_default		; 7, Reserved
	.long isr_default		; 8, Reserved
	.long isr_default		; 9, Reserved
	.long isr_default		; 10, Reserved
	.long isr_default		; 11, SV call
	.long isr_default		; 12, Debug monitor
	.long isr_default		; 13, Reserved
	.long isr_default		; 14, Pendable request for system service
	.long isr_default		; 15, System tick timer
	
	.end
