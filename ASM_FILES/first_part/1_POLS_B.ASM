STARTT 	START 	0
		CLEAR A
		CLEAR T
		CLEAR S
		
		LDA #LEN
		ADDR A, T
		LDA #IN
		ADDR A, T
		
		LDA #IN
		STA NEXT
		
LOOP	. KLIC FUNKCIJE
		LDA @NEXT
		CLEAR S
		ADDR A, S
		JSUB FUN
		
		. VREDNOST ZAPISEM KAR V INPUT SEZNAM
		LDA SUM
		STA @NEXT
		
		LDA NEXT
		ADD =3
		COMPR A, T
		STA NEXT
		JLT LOOP
HALT	J 		HALT
		
FUN		. SHRANI REGISTRE
		STA TEMP_A
		CLEAR A
		ADDR T, A
		STA TEMP_T
		CLEAR A
		ADDR S, A
		STA TEMP_S
		CLEAR A
		CLEAR T

		LDA S4
		ADDR A, T
		MULR S, T
		
		LDA S3
		ADDR A, T
		MULR S, T
		
		LDA S2
		ADDR A, T
		MULR S, T
		
		LDA S1
		ADDR A, T
		MULR S, T
		
		LDA S0
		ADDR A, T
		
		CLEAR A
		ADDR T, A
		STA SUM
		
		. OBNOVI PREJSNE REGISTRE
		LDA TEMP_T
		CLEAR T
		ADDR A, T
		LDA TEMP_S
		CLEAR S
		ADDR A, S
		LDA TEMP_A
		RSUB

TEMP_A	WORD 0
TEMP_T	WORD 0
TEMP_S	WORD 0

X		WORD 2
NEXT	WORD 0

IN		WORD 1
		WORD 2
		WORD 3
LASTIN EQU *
LEN EQU LASTIN-IN

SUM		WORD 0

S4	WORD 1
S3	WORD 2
S2 	WORD 3
S1 	WORD 4
S0 	WORD 5
