STARTT 	START 	0
		. C
		. int fact(int n) {
		. 	if(n == 1) return 1;
		.	return n * fact(n - 1);
		. }

		JSUB stackinit
		
		LDA =5
		JSUB FACT
		
		. NAŠA REŠITEV
		JSUB stackpop
		LDA @stackptr
		
HALT	J 		HALT

FACT	STL @stackptr
		JSUB stackpush
		
		STA @stackptr
		JSUB stackpush
			
		. IF STAVEK C KODE
		COMP =1
IF		JGT ELSE

		JSUB stackpop
		LDA @stackptr
		
		JSUB stackpop
		LDL @stackptr
		
		. SHRANIMO RETURN NASLOV ZAČASNO NA S
		RMO L, S
		
		. NA STACK ODLOŽIMO RETURN FUKCIJE. {RETURN 1;}
		STA @stackptr
		JSUB stackpush
		
		. PRED VRNITVIJO NA NASLOV L ZAPIŠEMO S
		RMO S, L
		RSUB
		
ELSE	
		SUB =1
		JSUB FACT
		
		JSUB stackpop
		LDT @stackptr
		
		JSUB stackpop
		LDA @stackptr
		
		JSUB stackpop
		LDL @stackptr
		
		. SHRANIMO RETURN NASLOV
		RMO L, S
		
		. ZMNOŽIMO TRENUTNI A IN RETURN FUNKCIJE
		MULR T, A
		
		. NA STACK ODLOŽIMO RETURN FUKCIJE. {RETURN N * FACT(N - 1);}
		STA @stackptr
		JSUB stackpush
		
		. PRED VRNITVIJO NA NASLOV L ZAPIŠEMO S
		RMO S, L
		RSUB

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
stack		RESW 100

STDIN	BYTE X'00'
STDOUT	BYTE X'01'

TEMP_A	WORD 0
TEMP_S	WORD 0
TEMP_T	WORD 0