#include <stdio.h>
#include <string.h>

#define Q 99999
#define Z ;if(!strncmp(c,

char c[Q], *C,
     *T="#6*.683234#15BD#24#24$3#(.)$?).(/.2##$"; // Piece move steps, board setup data and promotion XORs (subtract '#'=35).
B[Q], R, S, W, X;

F(U, V, p, r) {
	int f=0,t, i, d, P, u, q;
	for(;f<128;f=f+9&~8) { // Loop over squares looking for pieces.
		for(i=T[(P=B[f])&7]-35,d=0;d<0 || (d=T[i++]-35);d=-d) { // Loop over move steps for this piece.
			for(t=f+d;P&S;t+=d) { // Loop over destination squares in this direction.
				// Invalid square or friendly capture?
				if ((t&(q=136)) || ((u=B[t])&S))
					break;

				// Special pawn logic.
				if (P%8==2)
				{
					if (((d>0)^(S==32)) || // Bad direction?
							(!u && d%2 && t!=r) || // Diagonal without capture?
							(!(d%2) && u>0)) // Straight with capture?
						break;

					if(t==r) q=16; // Is this an en-passent capture?
				}

				// Other side left in check?
				if (U==8 && u&16)
					return 0;

				// Make move.
				B[t]=P;
				B[f]=0;
				B[t^q]=0; // If en-passent capture, remove victim pawn.
				if (P%8==2 && (t<8 || t>103))
					B[t]^=T[p%7+32]-35; // Promotion.
				S^=96;
				if (P&16 && t!=f+d)
					B[f+t>>1]=B[t+(d>0?1:-2)],B[t+(d>0?1:-2)]=0; // If castling also move rook.

				// Looking to make a move? (if our own move, make sure does not leave us in check)
				if ((t==V && f==U) | (U==Q && F(8,0,0,Q))) {
					W=f,X=t;
					R=(P%8==2 && t!=f+d ? f+t>>1 : 9); // Set ep-target square if double pawn move.
					return B[t]==P; // Indicate if promotion has NOT occured.
				}

				// Undo move.
				B[t^q]=10|S; // If en-passent capture, replace victim pawn.
				S^=96;
				B[f]=P;
				B[t]=u;

				// If GUI has given us a castling move, loop one more time to do it.
				if (P&16 && f==U && t+d==V)
					continue;
				
				// Double pawn first move.
				if (P%8==2 && (f<32 || f>87) && t==f+d && !(d%2))
					continue;
				
				// Hit a piece or non-slider?
				if (u || (P&8))
					break;
			}
		}
	}
	return 1;
}

main(i, p) {
	for(;strtok(gets(c)," ");fflush(stdout)) { // Loop, grabbing input and flushing output.
		Z"uci",4)) puts("id name i\nid author DJW\nuciok") // Reply to 'uci'.
		Z"i",1)) puts("readyok") // Reply to 'isready'.
		Z"q",1)) break; // Quit command, exit.
		Z"p",1)) { // Parse 'position' command.
			for(i=0;i<8;++i) // Reset board to start position.
				B[i+16]=R=42,B[i+96]=74, // Pawns.
				B[i+112]=(B[i]=T[i+24]-3)+(S=32), // Pieces.
				B[i+S]=B[i+48]=B[i+64]=B[i+80]=0; // Empty rows.
			for(;C=strtok(0," ");)
				F(*C+C[1]*16-881, C[2]+C[3]*16-881, C[4], R);
		}
		Z"g",1)) // Go command. Make a move and print it.
			p=F(Q, 0, 0, R),
			printf("bestmove %c%i%c%i%c\n", W%16+97, W/16+1, X%16+97, X/16+1, p?32:98);
	}
}
