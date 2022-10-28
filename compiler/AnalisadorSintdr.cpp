#include <iostream>
#include "header.h"
#include "AnalisadorLexico.cpp"

// Erros: 
//     aux(ponteiro) não pode receber tokensEntrada.front()(não é ponteiro)
 
std::list<Token> InicialState(std::list<Token> tokensEntrada){
    int tam = tokensEntrada.size();
    Token aux = tokensEntrada.front();
    
    std::list<Token> erros;

    block(&aux, tokensEntrada);

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

bool block(Token* aux, std::list<Token> tokensEntrada){
    if(!UnlabelledBlock(aux, tokensEntrada)){
        if(label(aux, tokensEntrada)){

            if (aux->rotulo == ":")
            {
                tokensEntrada.pop_front();
                aux = tokensEntrada.front();
                block(aux, tokensEntrada);
            }
            
        }
    }
    return true;
}

bool UnlabelledBlock(Token* aux, std::list<Token> tokensEntrada){
    blockHead(aux, tokensEntrada);
    if (tokensEntrada.front().rotulo == ";")
    {
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
    }
    compoundTail(aux, tokensEntrada);
}

bool blockHead(Token* aux, std::list<Token> tokensEntrada){
    if(aux->rotulo == "begin"){
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
        declaration(aux, tokensEntrada);
    }
    else{
        blockaux(aux, tokensEntrada);
    }
}

bool blockaux(Token* aux, std::list<Token> tokensEntrada){
    if (!declaration(aux, tokensEntrada)){
        return true;
    }
    else {
        blockaux(aux, tokensEntrada);
    }
}
bool compoundStatement(Token* aux, std::list <Token> tokensEntrada){
    if(!unlabelledCompound(aux, tokensEntrada)){
        if(label(aux, tokensEntrada)){
            if(aux->rotulo == ";"){
                tokensEntrada.pop_front();
                aux = tokensEntrada.front();
                if(compoundTail(aux, tokensEntrada)){
                    return true;
                }
            }
        }
        return false;
    }
    else return true;
}
bool unlabelledCompound(Token* aux, std::list <Token> TokensEntrada){
    if(aux->rotulo == "begin"){
        TokensEntrada.pop_front();
        aux = TokensEntrada.front();
        return compoundStatement(aux, TokensEntrada) ? true : false;
    }else return false;
}
bool declaration(Token* aux, std::list <Token> TokensEntrada){
   return typedeclaration(aux, TokensEntrada) ? true : false;
}
bool typedeclaration(Token* aux, std::list<Token> TokensEntrada){
    return Local_or_Own_type(aux, TokensEntrada) ? true : false;
}

bool Local_or_Own_type(Token* aux, std::list<Token> TokensEntrada){
    if(aux->rotulo == "integer"){
        TokensEntrada.pop_front();
        aux = TokensEntrada.front();
        return true;
    }
    else if(aux->rotulo == "own"){
        TokensEntrada.pop_front();
        if(aux->rotulo == "integer"){
            TokensEntrada.pop_front();
        }
        aux = TokensEntrada.front();
        return true;    
    }
    return false;
}

bool compoundTail(Token* aux, std::list <Token> tokensEntrada){
    if(statement(aux, tokensEntrada)){
        if(aux->rotulo == "end"){
            tokensEntrada.pop_front();
            aux = tokensEntrada.front();
            return true;
        }
        else if(aux->rotulo == ";"){
            tokensEntrada.pop_front();
            aux = tokensEntrada.front();
            return compoundTail(aux, tokensEntrada) ? true : false;
        }
    }
    return false;
}
bool statement(Token* aux, std::list <Token> tokensEntrada){
    if(!uncoditionalStatement(aux, tokensEntrada)){
        if(!conditionalStatement(aux, tokensEntrada)){
            return forStatement(aux, tokensEntrada) ? true : false;
        }
    }
    return true;
}
bool uncoditionalStatement(Token* aux, std::list <Token> tokensEntrada){
    if(!basicStatement(aux,tokensEntrada)){
        if(!compoundStatement(aux, tokensEntrada)){
            return block(aux, tokensEntrada) ? true : false;
        }
    }
    return true;
}
bool basicStatement(Token* aux, std::list <Token> tokensEntrada){
    if(!UnlabelledbasicStatement(aux, tokensEntrada)){
        if(label(aux, tokensEntrada)){
            if(aux->rotulo == ":"){
                tokensEntrada.pop_front();
                aux = tokensEntrada.front();
                if(basicStatement(aux, tokensEntrada)){
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}
bool label(Token* aux, std::list <Token> tokensEntrada){
    if(!identifier(aux, tokensEntrada)){
        if(!unsignedInteger(aux, tokensEntrada)){
            return false;
        }
    }
    return true;
}

bool UnlabelledbasicStatement(Token* aux, std::list <Token> tokensEntrada){
    if(!assignmentStatement(aux, tokensEntrada)){
        if(!goToStatement(aux, tokensEntrada)){
            if(!dummyStatement(aux, tokensEntrada)){
                return procedureStatement(aux, tokensEntrada) ? true : false;
            }
        }
    }
    return true;
}


bool unsignedInteger(Token* aux, std::list <Token> tokensEntrada){
    if(!digitFunction(aux, tokensEntrada)){
        //recursividade
        unsignedInteger(aux, tokensEntrada);
    }

    return true;
}
bool conditionalStatement(Token* aux, std::list <Token> tokensEntrada){

}
bool forStatement(Token* aux, std::list <Token> tokensEntrada){
    
}

bool assignmentStatement(Token* aux, std::list <Token> tokensEntrada){

}

bool goToStatement(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "goto"){
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
        return designationalExpression(aux, tokensEntrada) ? true : false;
    }
    else return false;
}
bool dummyStatement(Token* aux, std::list <Token> tokensEntrada){
    
}
bool procedureStatement(Token* aux, std::list <Token> tokensEntrada){
    
}
bool designationalExpression(Token* aux, std::list <Token> tokensEntrada){
    if(!simplesDesignationalExpression(aux, tokensEntrada)){
        if(ifClause(aux, tokensEntrada)){
            if(simplesDesignationalExpression(aux, tokensEntrada)){
                if(aux->rotulo == "else"){
                    if(designationalExpression(aux, tokensEntrada)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    return true;
}

bool ifClause(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "if"){
        tokensEntrada.pop_front();
        aux = tokensEntrada.front();
        if(booleanExpression(aux, tokensEntrada)){
            if(aux->rotulo == "then"){
                tokensEntrada.pop_front();
                aux = tokensEntrada.front();
                return true;
            }
        }
    }
    return false;
}
bool simplesDesignationalExpression(Token* aux, std::list <Token> tokensEntrada){
    
}
bool identifier(Token* aux, std::list <Token> tokensEntrada){
    char character;
    character = aux->rotulo[0];
    int tam = aux->rotulo.size();
    if(letter(aux, tokensEntrada, character)){
        if(auxIdentifier(aux, tokensEntrada, character, 0, tam))
        {
            tokensEntrada.pop_front();
            aux = tokensEntrada.front();
            return true;
        }
    }

    return false;
}

bool auxIdentifier(Token* aux, std::list <Token> tokensEntrada, char character, int i, int tam){
    i++;
    if(i == tam-1){
        return true;
    }
    else{
        if(letter(aux, tokensEntrada, character)){
            character = aux->rotulo[i];
            auxIdentifier(aux, tokensEntrada, character, i, tam);
        }
        else if(digitFunction(aux, tokensEntrada, character)){
            auxIdentifier(aux, tokensEntrada, character, i, tam);
        }
        
        return false;
    }
}

bool booleanExpression(Token* aux, std::list <Token> tokensEntrada){
    
}

bool letter(Token* aux, std::list <Token> tokensEntrada, char character){
    //VERIFICAR TODOS OS TERMINAIS DE LETRAS
    char letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    if(ChecaValidos(letters, character, sizeof(letters)/ sizeof(letters[0]))){
        return true;
    }
}

bool digitFunction(Token* aux, std::list <Token> tokensEntrada, char character){
    //terminais digitos
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        return true;
    }
}