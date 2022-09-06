
#include "header.h"

// Verifica se é uma letra
std::list<std::string> SeekLetters(int i, char *Letters, int Size, char character, std::list<std::string> TokensClasses){
    if(i == Size){
        return TokensClasses;
    }else{
        if(character == Letters[i]){ //Faz parte do alfabeto
            std::string Classe = "\nLetra - ";
            Classe+=character;

            TokensClasses.push_back(Classe);
        }
        return SeekLetters(i+1, Letters, Size, character, TokensClasses);
    }
}

// Verifica se é um separador simples
std::list<std::string> SeekSeparators(char *separators, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == separators[i]){ //Faz parte dos separadores simples
            std::string Classe = "\nseparador - ";
            Classe+=character;

            TokensClasses.push_back(Classe);
            // std::cout << "separador " << separators[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

// Verifica se é um operador aritmetico simples
std::list<std::string> SeekArithmetic(char *opArithmetic, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opArithmetic[i]){ //Faz parte dos operadores aritmeticos simples
            std::string Classe = "\nop aritmetico - ";
            Classe+=character;

            TokensClasses.push_back(Classe);
            // std::cout << "operadore aritmetico " << opArithmetic[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

// Verifica se é um operador relacional simples
std::list<std::string> SeekRelational(char *opRelational, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opRelational[i]){ //Faz parte dos operadores relacionais simples
            std::string Classe = "\nop relacional - ";
            Classe+=character;

            TokensClasses.push_back(Classe);
            //std::cout << "operador relacional " << opRelational[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

std::list<std::string> SeekDigits(char *Digits, int Size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < Size; i++){
        if(character == Digits[i]){
            std::string Classe = "\ndigito - ";
            Classe += character;
            TokensClasses.push_back(Classe);
        }
    }
    return TokensClasses;
}
