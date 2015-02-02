#include <stdio.h>

#define Z ;if(!strncmp(c,

T[]={13,7,8,9,20,8,7,13}; // Board setup data.

S, B[128];

main(i) {
	char c[99999];
  for(;;fflush(stdout)) { // Loop and ensure any data reaches the GUI.
  	strtok(gets(c), " ") // Wait for a command.
  	Z"uci",4)) puts("id name i\nid author DJW\nuciok") // Reply to 'uci'.
  	Z"i",1)) puts("readyok") // Reply to 'isready'.
  	Z"q",1)) break; // Quit command, exit.
  	Z"p",1)) { // Parse 'position' command.
    	for(i=0;i<8;++i) { // Reset board to start position.
      	B[i+16]=34;B[i+96]=2;B[i]=(B[i+112]=T[i])|(S=32); // Pieces.
      	B[i+S]=B[i+48]=B[i+64]=B[i+80]=0; // Empty rows.
      }
		}
  }
}
