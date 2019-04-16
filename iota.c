#define F ;for(
#define H 99999
#define I ;if(
#define K )break;
#define R return
#define Z ;if(!strncmp(c,

char c[H], *C,
     *T="#5)-57234#15BD#24#24$3#EKFA\\FKE/.2##$"; // Piece move steps, board setup data and promotion XORs (subtract '#'=35).

B[H], E, S, X, Y, i;

D(x, y, p, e) {
	int f=0,t, j, d, m, v, b
	F ;f<H;++f) { // Loop over squares looking for pieces.
		F j=T[(m=B[f])&7]-35,d=0;d<0 || (d=T[j++]-35);d=-d) { // Loop over move steps for this piece.
			F t=f;m&S;) { // Loop over destination squares in this direction.
				// Illegal square or friendly capture?
				I (t+=d)&(b=136) | (v=B[t])&S K

				// Special pawn logic.
				I m%8==2)	{
					I d>0 ^ S==32 | // Bad direction?
					   (!v & d%2 & t!=e) | // Diagonal without capture?
					   !(d%2 | !v) // Straight with capture?
						K

					I t==e) b=t^16; // Is this an en-passent capture?
				}

				// Other side left in check?
				I x==8 && v&16)
					R 0;

				// Make move.
				B[t]=m%128;
				B[f]=B[b]=0 // If en-passent capture, remove victim pawn.
				I m%8==2 & (t<8 | t>103))
					B[t]^=T[p%7+31]-35; // Promotion.
				S^=96
				I m&16 && t-f-d)
					B[f+t>>1]=B[i=t+(d*3-1)/2],B[i]=0 // If castling also move rook.

				// Looking to make a move? (if our own move, make sure does not leave us in check)
				I t==y & f==x | (x==H && D(8,0,0,H))) {
					X=f,Y=t;
					E= m%8==2&t!=f+d ? f+t>>1 : 9; // Set ep-target square if double pawn move.
					R B[t]-m&7; // Indicate if promotion has occured.
				}

				// Undo move.
				B[b]=10|S; // If en-passent capture, replace victim pawn.
				S^=96;
				B[f]=m;
				B[t]=v

				// Hit a piece or non-slider?
				// Also check for special cases of double initial pawn move or castling.
				I (v | m&8) && (~m&16 | f-x | t+d-y) && (~m&128 | t-f-d | d%2) K
			}
		}
	}
	R 1;
}

main() {
	F ;strtok(gets(c)," ");fflush(i=0)) { // Loop, grabbing input and flushing output.
		Z"uci",4)) puts("id name i\nid author D\nuciok") // Reply to 'uci'.
		Z"i",1)) puts("readyok") // Reply to 'isready'.
		Z"g",1)) // Go command. Make a move and print it.
			i=D(H, 0, 0, E),
			printf("bestmove %c%i%c%i%c\n", X%16+97, X/16+1, Y%16+97, Y/16+1, i?98:32)
		Z"p",1)) { // Parse 'position' command.
			F S=32;i<8;B[i+++96]=202) // Reset board to start position.
				B[i]=(B[i+112]=T[i+23])-S, // Pieces.
				B[i+S]=B[i+48]=B[i+64]=B[i+80]=0, // Empty rows.
				B[i+16]=E=170 // White pawns.
			F ;C=strtok(0," ");)
				D(*C+C[1]*16-881, C[2]+C[3]*16-881, C[4], E);
		}
		Z"q",1)) return 0; // Reaction to 'quit' command.
	}
}
