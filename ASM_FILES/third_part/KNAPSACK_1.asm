STARTT 	START 	0
		. knapsack rešitev za https://atcoder.jp/contests/dp/tasks/dp_d
		. vrednosti morajo biti dokaj male drgače rip
		JSUB stackinit
		
		LDA #WI
		STA WI_IND
		LDA #V
		STA V_IND
		
		JSUB RDDECNUM
		STA N
		JSUB RDDECNUM
		STA W
		
READ_W_V	LDA N
			MUL =3
			RMO A, T
			LDA #WI
			ADDR A, T
			
			LDA WI_IND
			COMPR A, T
			JEQ DONE

			JSUB RDDECNUM
			STA @WI_IND
			JSUB RDDECNUM
			STA @V_IND
			
			LDA WI_IND
			ADD =3
			STA WI_IND
			
			LDA V_IND
			ADD =3
			STA V_IND
			
			J READ_W_V	
			
			
DONE		CLEAR A
			CLEAR T
			. knapsack(0, 0)
			JSUB KNAPSACK
			
			JSUB stackpop
			LDA @stackptr
			
			JSUB ECHONUM
			LDCH NEWLINE
			
		
HALT	J 		HALT

KNAPSACK	STL @stackptr
			JSUB stackpush
			
			STA @stackptr
			JSUB stackpush
			
			STT @stackptr
			JSUB stackpush
			
K_IF1		. IF A == N
			COMP N
			JLT K_IF2
			
			JSUB stackpop
			LDT @stackptr
			
			JSUB stackpop
			LDA @stackptr
		
			JSUB stackpop
			LDL @stackptr
			
			RMO L, S
			
			CLEAR A
			STA @stackptr
			JSUB stackpush
			RMO S, L
			RSUB
			
			. IF T == W
K_IF2		LDS W
			COMPR T, S
			
			JGT K_IF3
			JLT K_IF3
			
			JSUB stackpop
			LDT @stackptr
			
			JSUB stackpop
			LDA @stackptr
		
			JSUB stackpop
			LDL @stackptr
			
			RMO L, S
			
			CLEAR A
			STA @stackptr
			JSUB stackpush
			RMO S, L
			RSUB
			
K_IF3		RMO A, S
			JSUB DPIND
			LDA @DP_MEM
			COMP =0
			RMO S, A
			JEQ K1
			
			JSUB stackpop
			LDT @stackptr
			
			JSUB stackpop
			LDA @stackptr
		
			JSUB stackpop
			LDL @stackptr
			
			RMO L, S
			
			LDA @DP_MEM
			STA @stackptr
			JSUB stackpush
			
			RMO S, L
			RSUB
			
K1			ADD =1
			JSUB KNAPSACK
			
			JSUB stackpop
			LDX @stackptr 
			
			JSUB stackpop
			LDT @stackptr 
			JSUB stackpop
			LDA @stackptr
			
			JSUB DPIND
			STX @DP_MEM
			
			STA @stackptr
			JSUB stackpush
			STT @stackptr
			JSUB stackpush
			
			.IF(T + WI[A] <= W)
K2			RMO A, S
			LDA #WI
			ADDR S, A
			ADDR S, A
			ADDR S, A
			STA WI_IND
			LDA @WI_IND
			ADDR T, A
			. A = T + WI[A]
			COMP W
			JGT K3
			
			RMO A, T
			RMO S, A
			
			ADD =1
			JSUB KNAPSACK
			
			JSUB stackpop
			LDX @stackptr
			
			JSUB stackpop
			LDT @stackptr 
			JSUB stackpop
			LDA @stackptr
			
			STA @stackptr
			JSUB stackpush
			STT @stackptr
			JSUB stackpush
			
			JSUB DPIND
			LDT @DP_MEM
			
			RMO A, S
			
			LDA #V
			ADDR S, A
			ADDR S, A
			ADDR S, A
			STA V_IND
			LDA @V_IND
			
			ADDR X, A
			COMPR T, A
			
			JEQ K3
			JGT K3
			
			RMO A, X
			
			JSUB stackpop
			LDT @stackptr 
			JSUB stackpop
			LDA @stackptr
			
			STX @DP_MEM
			J K4

K3			JSUB stackpop
			LDT @stackptr 
			JSUB stackpop
			LDA @stackptr
			JSUB DPIND

K4			JSUB stackpop
			LDX @stackptr 

			LDA @DP_MEM
			STA @stackptr
			JSUB stackpush
			
			RMO X, L
			RSUB
			

. IZRAČUNA LOKACIJO MEMO TABELE
DPIND		STA TEMP_A
			MUL W
			ADDR T, A
			MUL =3
			
			ADD #DP
			STA DP_MEM
			LDA TEMP_A

			RSUB

RDDECNUM	CLEAR T
			CLEAR S
			
LOOPRD		CLEAR A
			RD AADEV
			
			COMP =57
			JGT RDDECEND
			COMP =48
			JLT RDDECEND
			
			SUB =48
			RMO A, S
			RMO T, A
			MUL =10
			ADDR S, A
			
			RMO A, T
			J LOOPRD
			
RDDECEND	RD AADEV
			RMO T, A
			RSUB

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

	
	
. KANPASCK DATA
DP			RESW 350
DP_MEM		WORD 0

WI_IND		WORD 0
WI			RESW 20

V_IND		WORD 0
V			RESW 20

N			WORD 0
W			WORD 0
	
. DATA
NEG			WORD -1
NEWLINE 	BYTE 10
CHAR 		BYTE 0

DEC_I		WORD 0
DEC			RESW 10

stackptr	WORD 0
stack		RESW 400

AADEV		BYTE X'A3'
STDOUT		BYTE X'01'

TEMP_A		WORD 0
TEMP_S		WORD 0
TEMP_T		WORD 0