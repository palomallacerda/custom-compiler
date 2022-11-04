#include "header.h"
#include <vector>

// Verifica se é uma letra
std::vector<Token> SeekLetters(int i, char *Letters, int Size, char character, std::vector<Token> TokensClasses){
    if(i == Size){
        return TokensClasses;
    }else{
        if(character == Letters[i]){ //Faz parte do alfabeto
            Token Classe;
            Classe.tipo = "Letra";
            Classe.rotulo = character;

            TokensClasses.push_back(Classe);
        }
        return SeekLetters(i+1, Letters, Size, character, TokensClasses);
    }
}

// Verifica se é um separador simples
bool SeekSeparators(char *separators, int size, char character,std::vector<Token> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == separators[i]){ //Faz parte dos separadores simples
            return true;
        }
    }
    return false;
}

// Verifica se é um operador aritmetico simples
bool SeekArithmetic(char *opArithmetic, int size, char character,std::vector<Token> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opArithmetic[i]){ //Faz parte dos operadores aritmeticos simples
            return true;
        }
    }
    return false;
}

// Verifica se é um operador relacional simples
bool SeekRelational(char *opRelational, int size, char character,std::vector<Token> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opRelational[i]){ //Faz parte dos operadores relacionais simples
            return true;
        }
    }
    return false;
}

bool SeekDigits(char *Digits, int Size, char character,std::vector<Token> TokensClasses){
    bool valid = false;
    for (int i = 0; i < Size; i++){
        if(character == Digits[i]){
            valid = true;
        }
    }
    return valid;
}

bool SeekIgnore(char *ignore, int Size, char character){
    bool valid = false;
    for (int i = 0; i < Size; i++){
        if(character == ignore[i]){
            valid = true;
        }
    }
    return valid;
}
