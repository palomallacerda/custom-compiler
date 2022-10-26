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
        if(!erros.empty()){
            std::cout << "Foram encontrados os seguintes erros:" << std::endl;
            for (auto i: erros)
            {
                std::cout << i.tipo << " - " << i.rotulo << std::endl;
            }
        }
        return tokensEntrada;
    }
}

bool block(Token aux, std::list<Token> tokensEntrada){
    UnlabelledBlock(aux, tokensEntrada);
    // label(aux, tokensEntrada);
    // if (tokensEntrada.front().rotulo == ":")
    // {
    //      tokensEntrada.pop_front();
    // }
    // block(aux, tokensEntrada);
}

bool UnlabelledBlock(Token aux, std::list<Token> tokensEntrada){
    blockHead(aux, tokensEntrada);
    if (tokensEntrada.front().rotulo == ";")
    {
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
    }
    compoundTail(aux, tokensEntrada);
}

bool blockHead(Token aux, std::list<Token> tokensEntrada){
    if(aux.rotulo == "begin"){
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
        declaration(aux, tokensEntrada);
    }
    else{
        blockaux(aux, tokensEntrada);
    }
}

bool blockaux(Token aux, std::list<Token> tokensEntrada){
    if (!declaration(aux, tokensEntrada)){
        return true;   
    }
    else {
        blockaux(aux, tokensEntrada);
    }
}

bool declaration(Token aux, std::list <Token> TokensEntrada){
   return typedeclaration(aux, TokensEntrada) ? true : false;
}
bool typedeclaration(Token aux, std::list<Token> TokensEntrada){
    return Local_or_Own_type(aux, TokensEntrada) ? true : false;
}

bool Local_or_Own_type(Token aux, std::list<Token> TokensEntrada){
    if(aux.rotulo == "integer"){
        TokensEntrada.pop_front();
        aux = TokensEntrada.front();
        return true;
    }
    else if(aux.rotulo == "own"){
        TokensEntrada.pop_front();
        if(aux.rotulo == "integer"){
            TokensEntrada.pop_front();
        }
        aux = TokensEntrada.front();
        return true;
    }
    return false;
}

bool compoundTail(Token aux, std::list <Token> tokensEntrada){
    if(statement(aux, tokensEntrada)){
        if(aux.rotulo == "end"){
            tokensEntrada.pop_front();
            aux = tokensEntrada.front();
            return true;
        }
        else if(aux.rotulo == ";"){
            tokensEntrada.pop_front();
            aux = tokensEntrada.front();
            compoundTail(aux, tokensEntrada);
        }
    }
    
}
bool statement(Token aux, std::list <Token> tokensEntrada){
    if(!uncoditionalStatement(aux, tokensEntrada)){
        if(!conditionalStatement(aux, tokensEntrada)){
            if(forStatement(aux, tokensEntrada)){
                return true;
            }
            else return false;
        }
    }
    return true;
}
bool uncoditionalStatement(Token aux, std::list <Token> tokensEntrada){

}
bool conditionalStatement(Token aux, std::list <Token> tokensEntrada){
    
}
bool forStatement(Token aux, std::list <Token> tokensEntrada){
    
}