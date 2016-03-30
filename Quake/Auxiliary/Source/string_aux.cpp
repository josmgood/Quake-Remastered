#include "..\Include\string_aux.h"

QBool hasTerminatingZero(const char* string)
{
	const char* ch = string;
	while (*ch)
	{
		if (*(ch + 1) == '\0')
		{
			return true;
		}
		ch++;
	}
	return false;
}

QBool chricmp(char one, char two)
{
	return one == two || one == two - 32 || one == two + 32;
}

QBool chrcmp(char one, char two)
{
	return one == two;
}

QBool filterMatch(bool result)
{
	return result == 0;
}

QBool filterNotMatch(bool result)
{
	return result != 0;
}

QBool exceptionApply(bool result)
{
	return result == 0;
}

QBool exceptionNotApply(bool result)
{
	return result != 0;
}