STARTT 	START 	0
.	VSOTA
		LDA	X
		ADD Y
		STA SUM
.	RAZLIKA
		LDA X
		SUB Y
		STA DIFF
.	PRODUKT
		LDA X
		MUL Y
		STA PROD
.	KVOCIENT
		LDA X
		DIV Y
		STA QUOT
.	MODUL
		LDA X
		DIV Y
		MUL Y
		STA MOD
		LDA X
		SUB MOD
		STA MOD
HALT	J 		HALT

X		WORD 13
Y		WORD 5
SUM		WORD 0
DIFF	WORD 0
PROD	WORD 0
QUOT	WORD 0
MOD		WORD 0