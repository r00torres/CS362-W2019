#include "assertTests.h"
#include <stdio.h>
#include <stdlib.h>

int isEqual(int testValue, int compValue, char * message){

	printf("%s:", message);

	if(testValue == compValue){
		printf("PASS");
		return 1;
	}

	else{
		printf("FAIL");
		return 0;
	}
}
