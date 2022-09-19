#include <algorithm>
#include "header.h"

bool ChecaValidos(char *validos, char character, int size_arr)
{
    for (int i = 0; i < size_arr; i++)
    {
        if (validos[i] == character)
        {
            return true;
        }
    }
    return false;
}