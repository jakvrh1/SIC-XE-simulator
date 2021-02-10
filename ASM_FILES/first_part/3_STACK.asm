STARTT 	START 	0
		LDA =43
		
		JSUB stackinit
		
		STA @stackptr
		JSUB stackpush
		
		LDA =567
		
		STA @stackptr
		JSUB stackpush
		
		JSUB stackpop
		LDA @stackptr
		
		
		JSUB stackpop
		LDA @stackptr
		
		
		
		
HALT	J 		HALT


stackpush	
			STA TEMP_A
			LDA stackptr
			ADD =3
			STA stackptr
			LDA TEMP_A
			RSUB
			
stackpop	
			STA TEMP_A
			LDA stackptr
			SUB =3
			STA stackptr
			LDA TEMP_A
			RSUB
			
stackinit
			STA TEMP_A
			LDA #stack
			STA stackptr
			LDA TEMP_A
			RSUB

	
. DATA
stackptr	WORD 0
stack		RESW 50

STDIN	BYTE X'00'
STDOUT	BYTE X'01'

TEMP_A	WORD 0
TEMP_S	WORD 0
TEMP_T	WORD 0