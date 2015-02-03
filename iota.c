#include <stdio.h>
#include <string.h>

#define Q 99999
#define Z ;if(!strncmp(c,

char c[Q], *C,
     *T="#6*.683234#15BD#24#24$3#(.)$?).("; // Piece move steps and board setup data (subtract '#'=35).
B[Q], S, W, X;

F(U, V, p) {
	int f=0,t, i, d, P, u;
	for(;f<128;f=f+9&~8) { // Loop over squares looking for pieces.
		for(i=T[(P=B[f])&7]-35,d=0;d<0 || (d=T[i++]-35);d=-d) { // Loop over move steps for this piece.
			for(t=f+d;P&S;t+=d) { // Loop over destination squares in this direction.
				// Invalid square or friendly capture?
				if ((t&136) || ((u=B[t])&S))
					break;

				// Check for correct pawn movement.
				if (P%8==2 && ((d^u)%2 || ((d>0)^(S==32))))
					break;

				// Other side left in check?
				if (U==17 && (u&16))
					return 0;

				// Make move.
				B[t]=P;
				B[f]=0;
				S^=96;

				// Looking to make a move? (if our own move, make sure does not leave us in check)
				if ((t==V && f==U) || (U==Q && F(17,0,0))) {
					W=f,X=t;
					return 0;
				}

				// Undo move.
				S^=96;
				B[f]=P;
				B[t]=u;

				// Hit a piece or non-slider?
				if (u || (P&8))
					break;
			}
		}
	}
	return 1; // Failed to do anything.
}

main(i) {
	for(;strtok(gets(c)," ");fflush(stdout)) { // Loop, grabbing input and flushing output.
		Z"uci",4)) puts("id name i\nid author DJW\nuciok") // Reply to 'uci'.
		Z"i",1)) puts("readyok") // Reply to 'isready'.
		Z"q",1)) break; // Quit command, exit.
		Z"p",1)) { // Parse 'position' command.
			for(i=0;i<8;++i) // Reset board to start position.
				B[i+16]=42,B[i+96]=74, // Pawns.
				B[i+112]=(B[i]=T[i+24]-3)+(S=32), // Pieces.
				B[i+S]=B[i+48]=B[i+64]=B[i+80]=0; // Empty rows.
			for(;C=strtok(0," ");)
				F(*C+C[1]*16-881, C[2]+C[3]*16-881, C[4]);
		}
		Z"g",1)) // Go command. Make a move and print it.
			F(Q, 0, 0),
			printf("bestmove %c%i%c%i\n", W%16+97, W/16+1, X%16+97, X/16+1);
	}
}
