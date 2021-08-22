#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
+ A poor mans calculator in C

+ BODMAS is not here
*/

#define RUN 1


void
quickmafs()
{
    const char operators[4][2] = {
        "*",
        "+",
        "-",
        "/"
    };

	char expression[20];
	char * savepoint;

	int res;
	int left_operand;
	int right_operand;
	char *operator;


	char *token;
	while (1) {
        printf("<<< ");
		fgets(expression, 20, stdin);
        expression[strlen(expression) - 1] = '\0';
        savepoint = strdup(expression);

		for(int opchar = 0; opchar <= 3; opchar++)
		{

			token = strtok(expression, operators[opchar]);

			if (strlen(token) == strlen(savepoint))
				continue;		
		
			operator = strdup(operators[opchar]);
			left_operand = atoi(token);
			break;
		}

		token = strtok(NULL, operator);
		right_operand = atoi(token);

		switch(operator[0])
		{
	        case '*':
	            res = left_operand * right_operand;
	            break;
	        case '+':
	            res = left_operand + right_operand;
	            break;
	        case '-':
	           	res = left_operand - right_operand;
	            break;
	        case '/':
	    	    res = left_operand / right_operand;
	            break;
	        default:
	            printf("Computer says 'no' \n");
	            res = 0;
	            break;
		}

		printf(">>> %d\n", res);
	}
}


void
main(void)
{
    quickmafs();
}