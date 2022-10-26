#include <iostream>
#include "header.h"

std::list<Token> InicialState(std::list<Token> tokensEntrada){
    int tam = tokensEntrada.size();
    Token aux = tokensEntrada.front();
    std::list<Token> erros;
    
    block(aux, tokensEntrada);
    
    //Começa percorrer a bnf
    if(tokensEntrada.front().rotulo == "$"){
        tokensEntrada.pop_front(); //retirando ultimo elemento da lista
        return tokensEntrada;
    }
    else{
        return erros;
    }

}

void block(Token aux, std::list<Token> tokensEntrada){
    UnlabelledBlock(aux, tokensEntrada);
    // label(aux, tokensEntrada);
    // if (tokensEntrada.front().rotulo == ":")
    // {
    //      tokensEntrada.pop_front();
    // }
    // block(aux, tokensEntrada);
}

void UnlabelledBlock(Token aux, std::list<Token> tokensEntrada){
    blockHead(aux, tokensEntrada);
    if (tokensEntrada.front().rotulo == ";")
    {
        tokensEntrada.pop_front();
    }
    //compoundTail(aux, tokensEntrada);
}

void blockHead(Token aux, std::list<Token> tokensEntrada){
    if(aux.rotulo == "begin"){
        tokensEntrada.pop_front();
        declaration(aux, tokensEntrada);
    }
    blockaux(aux, tokensEntrada);
}

void blockaux(Token aux, std::list<Token> tokensEntrada){
    declaration(aux, tokensEntrada);
    //Como retornar com a cadeia vazia?
}

void declaration(Token aux, std::list <Token> TokensEntrada){
    typedeclaration(aux, TokensEntrada);
}
void typedeclaration(Token aux, std::list<Token> TokensEntrada){
    Local_or_Own_type(aux, TokensEntrada);
}

void Local_or_Own_type(Token aux, std::list<Token> TokensEntrada){
    if(aux.rotulo == "integer"){
        TokensEntrada.pop_front();
    }
    else if(aux.rotulo == "own"){
        TokensEntrada.pop_front();
        aux = TokensEntrada.front();
        if(aux.rotulo == "integer"){
            TokensEntrada.pop_front();
        }
    }
}
