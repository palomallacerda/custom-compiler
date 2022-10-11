#include <fstream>
#include <regex>
#include "FuncoesCompostas.cpp"
#include "header.h"

// Função para identificar palavras reservadas ou identificadores 
std::list<Token> seekReserved(int start, int end, std::fstream& File, std::list<Token> TokensClasses, std::string* BracketComp, std::string* opCompRelational,
std::string* compSeparators,  std::string* declarator, std::string* opSequential, char *Digits){
    int validBegin{-1};
    int validEnd{-1};
    int validAssigment{-1};
    int validStep{-1};
    int validUntil{-1};
    int validWhile{-1};
    int validComment{-1};
    int validMenorIgual{-1};
    int validDiferente{-1};
    int validMaiorIgual{-1};
    int validOwn{-1};
    int validInt{-1};
    int validArray{-1};
    int validProcedure{-1};
    int validGoto{-1};
    int validIf{-1};
    int validThen{-1};
    int validElse{-1};
    int validFor{-1};
    int validDo{-1};

    bool found = false;
    std::string id;

    File.seekg(start);

    while(!File.eof()){
        if (File.tellg() == end - 1){
            break;
        }
        char character;
        File.get(character);
        
         id += character;

        if(character=='<' || validMenorIgual>=0){
            TokensClasses=SeekMenorIgual(validMenorIgual, opCompRelational, character, TokensClasses);
            if(validMenorIgual == 1) {
                found = true;
            }
        }
        if(character=='!' || validDiferente>=0){
            TokensClasses=SeekDiferente(validDiferente, opCompRelational, character, TokensClasses);
            if(validDiferente == 1) {
                found = true;
            }
        }
        if(character=='>' || validMaiorIgual>=0){
            TokensClasses=SeekMaiorIgual(validMaiorIgual, opCompRelational, character, TokensClasses);
            if(validMaiorIgual == 1) {
                found = true;
            }
        }
        if(character == 'b' || validBegin >=0){
            TokensClasses=SeekBegin(validBegin, BracketComp,character, TokensClasses);
            if(validBegin == 4) {
                found = true;
            }
        }
        if(character == 'e' || validEnd >=0){
            TokensClasses=SeekEnd(validEnd, BracketComp, character, TokensClasses);
            if(validEnd == 2) {
                found = true;
            }
        }
        if(character == ':' || validAssigment >= 0){
            TokensClasses=SeekAssigment(validAssigment, compSeparators, character, TokensClasses);
            if(validAssigment == 1) {
                found = true;
            }
        }
        if(character == 's' || validStep >= 0){
            TokensClasses=SeekStep(validStep, compSeparators, character, TokensClasses);
            if(validStep == 3) {
                found = true;
            }
        }
        if(character == 'u' || validUntil >=0){
            TokensClasses=Seekuntil(validUntil, compSeparators, character, TokensClasses);
            if(validUntil == 4) {
                found = true;
            }
        }
        if(character=='w' || validWhile>=0){
            TokensClasses=SeekWhile(validWhile,compSeparators, character, TokensClasses);
            if(validWhile == 4) {
                found = true;
            }
        }
        if(character=='c' || validComment>=0){
            TokensClasses=SeekComment(validComment, compSeparators, character, TokensClasses);
            if(validComment == 6) {
                found = true;
            }
        }
        
        if(character=='o' || validOwn>=0){
            TokensClasses=SeekOwn(validOwn, declarator, character, TokensClasses);
            if(validOwn == 1) {
                found = true;
            }
        }
        if(character=='i' || validInt >=0){
            TokensClasses=SeekInteger(validInt, declarator, character, TokensClasses);
            if(validInt == 6) {
                found = true;
            }
        }
        if(character=='a' || validArray >=0){
            TokensClasses=SeekArray(validArray, declarator, character, TokensClasses);
            if(validArray == 4) {
                found = true;
            }
        }
        if(character=='p' || validProcedure >=0){
            TokensClasses=SeekProcedure(validProcedure, declarator, character, TokensClasses);
            if(validProcedure == 8) {
                found = true;
            }
        }
        if(character=='g' || validGoto >=0){
            TokensClasses=SeekGoto(validGoto, opSequential, character, TokensClasses);
            if(validGoto == 3) {
                found = true;
            }
        }
        if(character=='i' || validIf >=0){
            TokensClasses=SeekIf(validIf, opSequential, character, TokensClasses);
            if(validIf == 1) {
                found = true;
            }
        }
        if(character=='t' || validThen >=0){
            TokensClasses=SeekThen(validThen, opSequential, character, TokensClasses);
            if(validThen == 3) {
                found = true;
            }
        }
        if(character=='e' || validElse >=0){
            TokensClasses=SeekElse(validElse, opSequential, character, TokensClasses);
            if(validElse == 3) {
                found = true;
            }
        }
        if(character=='f' || validFor >=0){
            TokensClasses=SeekFor(validFor, opSequential, character, TokensClasses);
            if(validFor == 2) {
                found = true;
            }
        }
        if(character=='d' || validDo >=0){
            TokensClasses=SeekDo(validDo, opSequential, character, TokensClasses);
            if(validDo == 1) {
                found = true;
            }
        }
        if(SeekDigits(Digits, (sizeof(Digits)/sizeof(Digits[0])), character, TokensClasses)){
            Token Classe;
            Classe.tipo = "Digito";
            Classe.rotulo = character;
            TokensClasses.push_back(Classe);
            found = true;
        }
    }

    // se a palavra não for reservada é salva como identificador (aqui podemos colocar a verificação de número)
    if(!found){
        if(!id.empty()){
            std::regex r("\\s+");
            id = std::regex_replace(id, r, "");

            Token Classe;
            Classe.tipo = "Identificador";
            Classe.rotulo = id;
            TokensClasses.push_back(Classe);
        }
    }

    return TokensClasses;
}

