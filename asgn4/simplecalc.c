/*
 Program to implement a simple calculator
 ***************************************************************
 * Author           Dept.           Date           Notes
 ***************************************************************
 * Feng X           Comp.Science. Feb 17 2020     Initial version
*/
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]){
	/* if user does not pass in 3 inputs */
	if (argc != 4){
		puts("Error: usage is simplecalc <x> <op> <y>");
		return 1;
	}
	/* assigning input arguments */
	int x = atoi(argv[1]);
	char op = *argv[2];
	int y = atoi(argv[3]);

	/* perform simple arithmetic operations on the input as indicated by the operator and display output */
	switch(op){
		case '+': printf("%d\n",x+y);break;
		case '-': printf("%d\n",x-y);break;
		case '*': printf("%d\n",x*y);break;
		case '/': printf("%d\n",x/y);break;
		/* if the user enters one of the operators not listed */
		default:
			  printf("%c is not a valid operator\n", op);
			  return 2;
	}
	/* successful execution will return 0 */
	return 0;
}
