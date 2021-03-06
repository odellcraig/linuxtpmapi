/*
 * The Initial Developer of the Original Code is International
 * Business Machines Corporation. Portions created by IBM
 * Corporation are Copyright (C) 2009 International Business
 * Machines Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Common Public License as published by
 * IBM Corporation; either version 1 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with this program; if not, a copy can be viewed at
 * http://www.opensource.org/licenses/cpl1.0.php.
 */

#include "tpm_unsealdata.h"
#include <limits.h>
#include "tpm_tspi.h"
#include "tpm_utils.h"
#include "tpm_unseal.h"



int unsealData(char in_filename[PATH_MAX], char out_filename[PATH_MAX], BOOL srkWellKnown)
{
	FILE *fp;
	int rc=0, tss_size=0, i;
	unsigned char* tss_data = NULL;

		
	rc = tpmUnsealFile(in_filename, &tss_data, &tss_size, srkWellKnown);
	
	if (rc != TSS_SUCCESS) {
		printf("%s \n", tpmUnsealStrerror(rc));
		//goto out;
	}

	if (strlen(out_filename) == 0) {
		for (i=0; i < tss_size; i++)
			printf("%c", tss_data[i]);
		goto out;
	} else if ((fp = fopen(out_filename, "w")) == NULL) {
			logError(_("Unable to open output file"));
			goto out;
	}

	if (fwrite(tss_data, tss_size, 1, fp) != 1) {
		logError(_("Unable to write output file"));
		goto out;
	}
	fclose(fp);
out:
	free(tss_data);
	return rc;
}
