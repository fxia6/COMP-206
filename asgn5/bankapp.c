/*
 Program to implement a simple banking application
 ***************************************************************
 * Author           Dept.           Date           Notes
 ***************************************************************
 * Feng X           Comp.Science. Mar 13 2020     Initial version
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int addAccount(char *acctnum, char *name){
	FILE *f = fopen("bankdata.csv", "rt");
	char array[1000];
	while(!feof(f)){
		fgets(array,999,f);
		// if the account number is found, return and exit right away
		if (strstr(array,acctnum)!=0){
			fprintf(stderr,"Error, account number %s already exists\n", acctnum);
		      	return 50;
		}
	}
	fclose(f);
	// append new account
	f = fopen("bankdata.csv", "at");
	fprintf(f,"AC,");
	fprintf(f,"%s,",acctnum);
	fprintf(f,"%s\n", name);
	fclose(f);
	return 0;
}

int deposit(char *acctnum, char *date, float amount){          
        FILE *f = fopen("bankdata.csv", "rt");
	char array[2000];
	// assume the account number does not exist
	int exist = 0;
        while((!feof(f)) && (exist==0)){
                fgets(array,1999,f);
		// if the account is found in the file
                if (strstr(array,acctnum)!=0){
			exist = 1;
		}
        }
	// if the account does not exist in the file
	if (exist==0){
		fprintf(stderr,"Error, account number %s does not exist\n", acctnum);
		return 50;
	}
	fclose(f);
	// append transaction
	f = fopen("bankdata.csv", "at");
	fprintf(f,"TX,%s,%s,%.2f\n", acctnum, date, amount);
	fclose(f);
	return 0;
}

int withdrawl(char *acctnum, char *date, float amount){
        FILE *f = fopen("bankdata.csv", "rt");
        char array[2000];
	// assume the account does not exist
	int exist = 0;
        while((!feof(f)) && (exist==0)){
                fgets(array,1999,f);
		// if the account number is found in the file, which means existence
                if (strstr(array,acctnum)!=0){
                    	exist = 1;
                }
        }
	// the account does not exist in the file
	if (exist==0){
                fprintf(stderr,"Error, account number %s does not exist\n", acctnum);
                return 50;
        }
	fclose(f);

	f = fopen("bankdata.csv", "rt");

	// calculate to see if the account has enough balance to withdraw
	float balance = 0.0;
	while(!feof(f)){
		char array2[100];
		fgets(array2,99,f);
		// if this line is a transaction
		if (array2[0] == 'T' && array2[1] == 'X'){
			char *s = array2;
			char *token = strtok(s,",");
			while (token) {
				// if this line matches with the input account number 
				if (strcmp(token,acctnum)==0){
					token = strtok(NULL,",");
					token = strtok(NULL,",");
					float temp = atof(token);
					balance += temp;
					break;
				}
				// if not matched, next token
				token = strtok(NULL,",");
			}
		}
	}
	fclose(f);
	
	// negate since it is withdrawl
	float negate = 0-amount;
	// allow appending later
	f = fopen("bankdata.csv", "at");

	// if the balance is not enough to withdraw from 
	if (balance < amount){
		fprintf(stderr, "Error, account number %s has only %.2f\n", acctnum, balance); 
		return 60;
	} else {
		// append transaction
	       	fprintf(f,"TX, %s, %s, %.2f\n", acctnum, date, negate);
                fclose(f);
        	return 0;
	}
	fclose(f);
}


int main(int argc, char *argv[]){
	
	// if user does not input any argument
	if (argc<2){
		fprintf(stderr,"%s","Error,incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
                        return 1;
	}

	// if the program cannot find the data file             
        FILE *f = fopen("bankdata.csv", "rt");
        if (f==NULL){
                fprintf(stderr,"%s","Error, unable to locate the data file bankdata.csv\n");
                exit (100);
        }
	fclose(f);

	// the operation the user enters
        char *operation = argv[1];
	// add an account
	if (!strcmp(operation,"-a")) {
		if (argc<4){
			fprintf(stderr,"%s","Error, incorrect usage!\n-a ACCTNUM NAME\n");
			return 1;
		} else {
			char *acctnum = argv[2];
			char *name = argv[3];	
			printf("%s",name);
			return addAccount(acctnum,name);
		}	
	// make a deposit	
	} else if (!strcmp(operation,"-d")){
		if (argc<5){
        	        fprintf(stderr,"%s","Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
			return 1;
		} else {
			char *acctnum = argv[2];
			char *date = argv[3];
			float amount = atof(argv[4]);
			return deposit(acctnum,date,amount);
		}

	// make a withdrawl
	} else if (!strcmp(operation,"-w")){
		if (argc<5){
 			fprintf(stderr,"%s","Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
			return 1;
		} else {
			char *acctnum = argv[2];
			char *date = argv[3];
			float amount = atof(argv[4]);
			return withdrawl(acctnum,date,amount);
                }
	} else{
	// any other invalid inputs
		fprintf(stderr,"%s","Error,incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		return 1;
	}
}

