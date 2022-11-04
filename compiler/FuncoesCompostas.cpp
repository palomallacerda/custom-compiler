#include "header.h"
#include <vector>

//Verificar se a palavra reservada Begin
std::vector<Token> SeekBegin(int &validBegin, std::string* Bracket,char character, std::vector<Token> TokensClasses){
    std::string Begin = Bracket[0];

    if(character == Begin[validBegin+1]){
        validBegin +=1;
    }
    else{
        validBegin = -1;
    }

    if(validBegin == 4) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = Begin;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada end
std::vector<Token> SeekEnd(int &validEnd, std::string* Bracket,char character, std::vector<Token> TokensClasses){
    std::string end = Bracket[1];

    if(character == end[validEnd+1]){
        validEnd +=1;
    }
    else{
        validEnd = -1;
    }

    if(validEnd == 2) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = end;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada Comment
std::vector<Token> SeekAssigment(int &validAssigment, std::string* compSeparators,char character, std::vector<Token> TokensClasses){
    std::string assigment = compSeparators[0];

    if(character == assigment[validAssigment+1]){
        validAssigment +=1;
    }
    else{
        validAssigment = -1;
    }

    if(validAssigment == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = assigment;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada step
std::vector<Token> SeekStep(int &validStep, std::string* compSeparators,char character, std::vector<Token> TokensClasses){
    std::string step = compSeparators[1];

    if(character == step[validStep+1]){
        validStep +=1;
    }
    else{
        validStep = -1;
    }

    if(validStep == 3) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = step;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada until
std::vector<Token> Seekuntil(int &validUntil, std::string* compSeparators,char character, std::vector<Token> TokensClasses){
    std::string until = compSeparators[2];

    if(character == until[validUntil+1]){
        validUntil +=1;
    }
    else{
        validUntil = -1;
    }

    if(validUntil == 4) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = until;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada while
std::vector<Token> SeekWhile(int &validWhile, std::string* compSeparators,char character, std::vector<Token> TokensClasses){
    std::string While = compSeparators[3];

    if(character == While[validWhile+1]){
        validWhile +=1;
    }
    else{
        validWhile = -1;
    }

    if(validWhile == 4) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = While;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada Comment
std::vector<Token> SeekComment(int &validComment, std::string* compSeparators,char character, std::vector<Token> TokensClasses){
    std::string comment = compSeparators[4];

    if(character == comment[validComment+1]){
        validComment +=1;
    }
    else{
        validComment = -1;
    }
    return TokensClasses;
}

//Verificar se a palavra reservada menorIgual
std::vector<Token> SeekMenorIgual(int &validMenorIgual, std::string* opCompRelational,char character, std::vector<Token> TokensClasses){
    std::string menorIgual = opCompRelational[0];

    if(character == menorIgual[validMenorIgual+1]){
        validMenorIgual +=1;
    }
    else{
        validMenorIgual = -1;
    }

    if(validMenorIgual == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = menorIgual;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada é operador diferente
std::vector<Token> SeekDiferente(int &validDiferente, std::string* opCompRelational, char character, std::vector<Token> TokensClasses){
    std::string diferente = opCompRelational[1];

    if(character == diferente[validDiferente+1]){
        validDiferente +=1;
    }
    else{
        validDiferente = -1;
    }

    if(validDiferente == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = diferente;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada >=
std::vector<Token> SeekMaiorIgual(int &validMaiorigual, std::string* opCompRelational,char character, std::vector<Token> TokensClasses){
    std::string maiorIgual = opCompRelational[2];

    if(character == maiorIgual[validMaiorigual+1]){
        validMaiorigual +=1;
    }
    else{
        validMaiorigual = -1;
    }

    if(validMaiorigual == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = maiorIgual;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palavra reservada Own
std::vector<Token> SeekOwn(int &validOwn, std::string* declarador,char character, std::vector<Token> TokensClasses){
    std::string own = declarador[0];

    if(character == own[validOwn+1]){
        validOwn +=1;
    }
    else{
        validOwn = -1;
    }

    if(validOwn == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = own;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palabra reservada integer
std::vector<Token> SeekInteger(int &validInt, std::string* declarador, char character, std::vector<Token> TokensClasses){
    std::string integer = declarador[1];

    if(character == integer[validInt+1]){
        validInt +=1;
    }
    else{
        validInt = -1;
    }

    if(validInt == 6) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = integer;
        TokensClasses.push_back(Classe);  
    }
    return TokensClasses;
}

//Verificar se a palabra reservada array
std::vector<Token> SeekArray(int &validArray, std::string* declarador, char character, std::vector<Token> TokensClasses){
    std::string array = declarador[2];

    if(character == array[validArray+1]){
        validArray +=1;
    }
    else{
        validArray = -1;
    }

    if(validArray == 4) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = array;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificar se a palabra reservada array
std::vector<Token> SeekProcedure(int &validProcedure, std::string* declarador, char character, std::vector<Token> TokensClasses){
    std::string procedure = declarador[3];

    if(character == procedure[validProcedure+1]){
        validProcedure +=1;
    }
    else{
        validProcedure = -1;
    }

    if(validProcedure == 8) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = procedure;
        TokensClasses.push_back(Classe);  
    }
    return TokensClasses;
}

//Verificando se o operador é valido (GOTO)
std::vector<Token> SeekGoto(int &validGoto, std::string* opSequential, char character, std::vector<Token> TokensClasses){
    std::string goTo = opSequential[0];

    if(character == goTo[validGoto+1]){
        validGoto +=1;
    }
    else{
        validGoto = -1;
    }

    if(validGoto == 3) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = goTo;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificando se é a condicional IF
std::vector<Token> SeekIf(int &validIf, std::string* opSequential, char character, std::vector<Token> TokensClasses){ 
    std::string IF = opSequential[1];

    if(character == IF[validIf+1]){
        validIf +=1;
    }
    else{
        validIf = -1;
    }

    if(validIf == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = IF;
        TokensClasses.push_back(Classe);  
    }
    return TokensClasses;
}

//Verificando se é a condicional THEN
std::vector<Token> SeekThen(int &validThen, std::string* opSequential, char character, std::vector<Token> TokensClasses){ 
    std::string Then = opSequential[2];

    if(character == Then[validThen+1]){
        validThen +=1;
    }
    else{
        validThen = -1;
    }

    if(validThen == 3) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = Then;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificando se é a condicional ELSE
std::vector<Token> SeekElse(int &validElse, std::string* opSequential, char character, std::vector<Token> TokensClasses){ 
    std::string Else = opSequential[3];

    if(character == Else[validElse+1]){
        validElse +=1;
    }
    else{
        validElse = -1;
    }

    if(validElse == 3) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = Else;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificando se é a condicional FOR
std::vector<Token> SeekFor(int &validFor, std::string* opSequential, char character, std::vector<Token> TokensClasses){ 
    std::string FOR = opSequential[4];

    if(character == FOR[validFor+1]){
        validFor += 1;
    }
    else{
        validFor = -1;
    }

    if(validFor == 2) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = FOR;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}

//Verificando se é a condicional FOR
std::vector<Token> SeekDo(int &validDo, std::string* opSequential, char character, std::vector<Token> TokensClasses){ 
    std::string Do = opSequential[5];

    if(character == Do[validDo+1]){
        validDo +=1;
    }
    else{
        validDo = -1;
    }

    if(validDo == 1) {
        Token Classe;
        Classe.tipo = "Idenficador Reservado";
        Classe.rotulo = Do;
        TokensClasses.push_back(Classe);
    }
    return TokensClasses;
}