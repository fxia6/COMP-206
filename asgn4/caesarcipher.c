/* 
 Program to implement a basic version of Caesar's cipher
 *******************************************************************
 * Author           Dept.            Date            Notes
 *******************************************************************
 * Feng X           Comp. Science.  Feb 18 2020    Initial version
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	
	/* if the user does not pass one argument */
	if ( argc != 2 ){
		puts("Error: usage is caesarcipher <offset>");
		return 1;
	}
	
	/* assign user input */
	int shift = atoi(argv[1]);
	char sentence[200];
	char c;

	while (1 == scanf("%[^\n]%*c",sentence)) {
	/* shifting process */
	for (int i=0; i<strlen(sentence); i++){
		c = sentence[i];
		/* if the character is a lower case letter */
		if (c>=97 && c<=122) {
			
			/* if the letter needs to wrap around towards the end of alphabet */
			if ((c+shift)>122){
				c = 96 + (c+shift-122);
			/* else if the letter needs to wrap around towards the beginning of alphabet */
			} else if ((c+shift)<97){
				c = 123 - (97-(c+shift));
			} else {
				c += shift;
			}
		}
		sentence[i]=c;
	}
	/* display result */
	printf ("%s\n", sentence);
	}

	/* successful execution return 0 */
	return 0;

}
