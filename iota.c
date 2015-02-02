#include <stdio.h>

main() {
	char c[99999];
  for(;;fflush(stdout)) { // Loop and ensure any data reaches the GUI.
  	strtok(gets(c), " "); // Wait for a command.
  	if(!strncmp(c,"uci",4)) puts("id name i\nid author DJW\nuciok"); // Reply to 'uci'.
  	if(!strncmp(c,"i",1)) puts("readyok"); // Reply to 'isready'.
  	if(!strncmp(c,"q",1)) break; // Quit command, exit.
}}
