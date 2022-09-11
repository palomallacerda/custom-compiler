#include <cctype>
// #include <iostream>
#include <algorithm>
#include "header.h"

bool CheackUpperCase(char character)
{
    if (isupper(character))
    {
    return false;
    }
    return true;
}

bool ChecaValidos(char *validos, char character)
{
    for (int i = 0; i < sizeof(validos)/sizeof(validos[0]); i++)
    {
        if (validos[i] == character)
        {
            return true;
        }
    }
    return false;
}