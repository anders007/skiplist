
#include <time.h>
#include "replace.h"
#include "mtrand.h"

int replace_random()
{
	static MTRand_int32* s_pRandGen = new MTRand_int32(time(0));
	if (s_pRandGen)
	{
		return (*s_pRandGen)();
	}
	return -1;
}