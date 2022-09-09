#include <cctype>
#include <iostream>
#include <algorithm>
#include "header.h"

bool ChecaMaiusculas(char character)
{
    if (isupper(character))
    {
        return false;
    }
    return true;
}

bool ChecaSeparadores(char *separators, char character)
{
    for (int i = 0; i < sizeof(separators)/sizeof(separators[0]); i++)
    {
        if (separators[i] == character)
        {
            return true;
        }
    }

    return false;
}

bool ChecaOpAritmeticos(char *opArithmetic, char character)
{
    for (int i = 0; i < sizeof(opArithmetic)/sizeof(opArithmetic[0]); i++)
    {
        if (opArithmetic[i] == character)
        {
            return true;
        }
    }

    return false;
}

bool ChecaOpRelacional(char *opRelational, char character)
{
    for (int i = 0; i < sizeof(opRelational)/sizeof(opRelational[0]); i++)
    {
        if (opRelational[i] == character)
        {
            return true;
        }
    }

    return false;
}

bool ChecaLetra(char *Letters, char character)
{
    for (int i = 0; i < sizeof(Letters)/sizeof(Letters[0]); i++)
    {
        if (Letters[i] == character)
        {
            return true;
        }
    }

    return false;
}

bool ChecaDigitos(char *Digits, char character)
{
    for (int i = 0; i < sizeof(Digits)/sizeof(Digits[0]); i++)
    {
        if (Digits[i] == character)
        {
            return true;
        }
    }

    return false;
}

bool ChecaBracket(char character)
{
    
}

int main()
{
    char test = '{';
    
    std::string BracketComp[]{"begin", "end"};

    /*bool check = ChecaBracket(BracketComp, test);
    if (check == false)
    {
        std::cout << "Erro no codigo\n";
    }
    */
}

