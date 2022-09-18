<<<<<<< HEAD
#include <algorithm>
#include "header.h"

bool ChecaValidos(char *validos, char character, int size_arr)
=======
#include <cctype>
// #include <iostream>
#include <algorithm>
#include "header.h"

bool CheackUpperCase(char character)
>>>>>>> main
{
    for (int i = 0; i < size_arr; i++)
    {
<<<<<<< HEAD
        if (validos[i] == character)
        {
            return true;
        }
    }
    return false;
=======
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
>>>>>>> main
}