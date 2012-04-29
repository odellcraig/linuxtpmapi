//============================================================================
// Name        : APIExample.cp
// Author      : Craig Odell
// Version     :
// Copyright   : 
// Description : Demonstrate TPM Example
//============================================================================

#include "tpm_sealdata.h"
#include "tpm_unsealdata.h"
#include <stdio.h>


int main(int argc, char **argv)
{
	printf("Hello API!\n");

	if(strcmp(argv[1], "-s") == 0) {
		printf("Sealing Password File: %s -> %s\n", argv[2], argv[3]);
		sealData(argv[2],argv[3],0,0);
	}

	if(strcmp(argv[1], "-s") == 0) {
			printf("Unsealing Password File: %s -> %s\n", argv[2], argv[3]);
			unsealData(argv[2],argv[3],0);
	}

	return 0;
}
