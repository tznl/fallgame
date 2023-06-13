#include "include/codepoints.h"
#include <string.h>
#include <stdlib.h>
int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount)
{
	int codepointsNoDupsCount = codepointCount;
	int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
	memcpy(codepointsNoDups, codepoints, codepointCount*sizeof(int));

/* Remove duplicates */
	int i;
	for (i = 0; i < codepointsNoDupsCount; i++)
	{
		int j;
		for (j = i + 1; j < codepointsNoDupsCount; j++)
		{
			if (codepointsNoDups[i] == codepointsNoDups[j])
			{
				int k;
				for (k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

				codepointsNoDupsCount--;
				j--;
			}
		}
	}   

/* NOTE: The size of codepointsNoDups is the same as original array but
only required positions are filled (codepointsNoDupsCount) */

	*codepointsResultCount = codepointsNoDupsCount;
	return codepointsNoDups;
}
