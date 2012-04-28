/*
 * The Initial Developer of the Original Code is International
 * Business Machines Corporation. Portions created by IBM
 * Corporation are Copyright (C) 2005, 2006 International Business
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
#include "tpm_sealdata.h"
#include "tpm_utils.h"
#include "tpm_seal.h"
#include "tpm_tspi.h"
#include <limits.h>
#include <openssl/evp.h>

static void help(const char *aCmd)
{
	logCmdHelp(aCmd);
	logCmdOption("-i, --infile FILE",
		     _
		     ("Filename containing key to seal. Default is STDIN."));
	logCmdOption("-o, --outfile FILE",
		     _
		     ("Filename to write sealed key to.  Default is STDOUT."));
	logCmdOption("-p, --pcr NUMBER",
		     _
		     ("PCR to seal data to.  Default is none.  This option can be specified multiple times to choose more than one PCR."));
	logCmdOption("-z, --well-known", _("Use TSS_WELL_KNOWN_SECRET as the SRK secret."));
	logCmdOption("-u, --unicode", _("Use TSS UNICODE encoding for the SRK password to comply with applications using TSS popup boxes"));

}

static char in_filename[PATH_MAX] = "", out_filename[PATH_MAX] = "";
static UINT32 selectedPcrs[24];
static UINT32 selectedPcrsLen = 0;
static BOOL passUnicode = FALSE;
static BOOL isWellKnown = FALSE;

static int parse(const int aOpt, const char *aArg)
{
	int rc = -1;

	switch (aOpt) {
	case 'i':
		if (aArg) {
			strncpy(in_filename, aArg, PATH_MAX);
			rc = 0;
		}
		break;
	case 'o':
		if (aArg) {
			strncpy(out_filename, aArg, PATH_MAX);
			rc = 0;
		}
		break;
	case 'p':
		if (aArg) {
			selectedPcrs[selectedPcrsLen++] = atoi(aArg);
			rc = 0;
		}
		break;
	case 'u':
		passUnicode = TRUE;
		rc = 0;
		break;
	case 'z':
		isWellKnown = TRUE;
		rc = 0;
		break;
	default:
		break;
	}
	return rc;

}

int main(int argc, char **argv)
{
	

	struct option opts[] =
	{ 
		{"infile", required_argument, NULL, 'i'},
		{"outfile", required_argument, NULL, 'o'},
		{"pcr", required_argument, NULL, 'p'},
		{"unicode", no_argument, NULL, 'u'},
		{"well-known", no_argument, NULL, 'z'}
	};

	if (genericOptHandler(argc, argv, "i:o:p:uz", opts,
			      sizeof(opts) / sizeof(struct option), parse,
			      help) != 0)
		return -1;
	
	
	return sealData(in_filename, out_filename, passUnicode, isWellKnown);
}
