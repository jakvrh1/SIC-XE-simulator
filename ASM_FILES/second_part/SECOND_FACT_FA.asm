STARTT 	START 	0
		. C
		. int fact(int n) {
		. 	if(n == 1) return 1;
		.	return n * fact(n - 1);
		. }
		
		JSUB stackinit
		
SOLVE	CLEAR A
		RD FADEV
		COMP =40
		JGT PART1
		
		. carrige + new line ZATO DRUGIČ V PRAZNO PREBEREM
		RD FADEV
		
		. ŠTEVILO IZ PREJŠNE VRSTICE ZAPIŠEM V A
		RMO T, A

		. REŠI FACTORIAL
		JSUB FACT
		
		. NAŠA REŠITEV T-JA
		JSUB stackpop
		LDA @stackptr
		
		. IZPIS REŠITVE V TERMINAL, Z NEWLINE
		JSUB ECHONUM
		LDCH NEWLINE
		WD STDOUT
		
		CLEAR T
		CLEAR A
		
		. PREBEREM NASLEDNJI ZNAK, ČE JE TA 0 VEMO, DA SMO NA KONCU
		RD FADEV
		SUB =48
		COMP =0
		JEQ HALT
		
		. TKO KOT BITE PREBEREM TAKO JIH ZAPISUJEM
		SHIFTL T, 1
		ADDR A, T
		J SOLVE
		
		. TKO KOT BITE PREBEREM TAKO JIH ZAPISUJEM
PART1	SUB =48
		SHIFTL T, 1
		ADDR A, T
		J SOLVE
		
HALT	J 		HALT

ECHONUM	
		STA TEMP_A
		STS TEMP_S
		STT TEMP_T
		
		CLEAR S
		CLEAR T
		
		LDS #DEC
		STS DEC_I
		RMO A, S
		
LOOP1	RMO S, A
		RMO S, T
		
		. A Z ZADNJO DEC
		DIV =10
		RMO A, S
		MUL =10
		SUBR T, A
		. A VEDNO MANJŠI OD T, ZATO DOBIMO ŠTEVKO, KI JE NEGATIVNA, POMNOŽIMO Z -1
		MUL NEG
		
		. ZAPIS
		STA @DEC_I
		. POGLEDAMO CE JE ŠE KAKSNA ŠTEVKA
		RMO S, A
		COMP =0
		
		. POVEČAMO ŠTEVEC
		LDA DEC_I
		ADD =3
		STA DEC_I
		
		JGT LOOP1
		
		. PO IZSTOPU JE INDEKS ZA EN ELEMENT NAPREJ, ZATO SUB
		SUB =3
		STA DEC_I
		
LOOP2 	. VSAKI ŠTEVKI RABIMO DODATI 48
		LDA @DEC_I
		ADD =48
		
		. ZAPIS ASCII KODE ŠTEVKE
		STCH CHAR
		
		. A SMO ŽE NA PRVEM NASLOVU (GREŠ OD VZADI NAPREJ, KOT NPR --DEC_I)?
		LDA DEC_I
		COMP #DEC
		
		. IZPIS ŠTEVKE
		LDCH CHAR
		WD STDOUT
		
		. ZMANJŠAMO ŠTEVEC
		LDA DEC_I
		SUB =3
		STA DEC_I

		JGT LOOP2
		
		. REGISTRE OBNOVIMO TAKO, KOT SO BILI PRED FUNKCIJO
		LDA TEMP_A
		LDS TEMP_S
		LDT TEMP_T
		
		RSUB
		

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
NEG			WORD -1
NEWLINE 	BYTE 10
CHAR 		BYTE 0

DEC_I		WORD 0
DEC			RESW 10

stackptr	WORD 0
stack		RESW 100

FADEV		BYTE X'FA'
STDOUT		BYTE X'01'

TEMP_A		WORD 0
TEMP_S		WORD 0
TEMP_T		WORD 0