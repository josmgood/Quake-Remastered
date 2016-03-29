#include "..\Include\string_aux.h"

QBool chricmp(char one, char two)
{
	return one == two || one == two - 32 || one == two + 32;
}

QBool chrcmp(char one, char two)
{
	return one == two;
}