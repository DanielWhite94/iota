#include <stdio.h>
#include <string.h>

#define Q 99999
#define Z ;if(!strncmp(c,

T[]={0,19,10,11,19,21,16, // Piece move step offsets.
		 15,16,17,0,14,18,31,33,0,15,17,0,15,17,1,16,0, // Piece move steps.
		 5,11,6,1,28,6,11,5}; // Board setup data.
B[Q], S, W, X;

F(U, V, p) {
	int f=0,t, i, d, P, u;
	for(;f<128;f=f+9&~8) { // Loop over squares looking for pieces.
		for(i=T[(P=B[f])&7],d=0;d<0 || (d=T[i++]);d=-d) { // Loop over move steps for this piece.
			for(t=f+d;P&S;t+=d) { // Loop over destination squares in this direction.
				// Invalid square or friendly capture?
				if ((t&136) || ((u=B[t])&S))
					break;

				// Other side left in check?
				if (U==17 && (u&16))
					return 1;

				// Make move.
				B[t]=P;
				B[f]=0;
				S^=96;

				// Looking to make a move?
				if ((t==V && f==U) || U==Q)
					// Test for leaving self in check.
					if (!F(17, 0, 0)) {
						W=f,X=t;
						return 1;
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
	return 0; // Failed to do anything.
}

main(i) {
	char c[Q], *C;
	for(;strtok(gets(c)," ");fflush(stdout)) { // Loop, grabbing input and flushing output.
		Z"uci",4)) puts("id name i\nid author DJW\nuciok") // Reply to 'uci'.
		Z"i",1)) puts("readyok") // Reply to 'isready'.
		Z"q",1)) break; // Quit command, exit.
		Z"p",1)) { // Parse 'position' command.
			for(i=0;i<8;++i) // Reset board to start position.
				B[i+16]=42,B[i+96]=74, // Pawns.
				B[i+112]=(B[i]=T[i+24]+32)+(S=32), // Pieces.
				B[i+S]=B[i+48]=B[i+64]=B[i+80]=0; // Empty rows.
			for(;C=strtok(0," ");)
				F(*C+C[1]*16-881, C[2]+C[3]*16-881, C[4]);
		}
		Z"g",1)) // Go command. Make a move and print it.
			F(Q, 0, 0),
			printf("bestmove %c%i%c%i\n", W%16+97, W/16+1, X%16+97, X/16+1);
	}
}
