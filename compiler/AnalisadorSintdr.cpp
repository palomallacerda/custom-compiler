#include <iostream>
#include "header.h"
#include "AnalisadorLexico.cpp"

// Erros:
//     aux(ponteiro) não pode receber tokensEntrada.front()(não é ponteiro) 
//     Remover recursividade a esquerda de algumas funções na bnf
//      

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
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
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
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
    }
    compoundTail(aux, tokensEntrada);
}

bool blockHead(Token* aux, std::list<Token> tokensEntrada){
    if(aux->rotulo == "begin"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
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
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                if(compoundTail(aux, tokensEntrada)){
                    return true;
                }
            }
        }
        return false;
    }
    else return true;
}
bool unlabelledCompound(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "begin"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return compoundStatement(aux, tokensEntrada) ? true : false;
    }else return false;
}
bool declaration(Token* aux, std::list <Token> TokensEntrada){
   if(!typedeclaration(aux, TokensEntrada)){
        if(!arrayDeclaration(aux, TokensEntrada)){
            if(!procedureDeclaration(aux, TokensEntrada)){
                return false;
            }
        }
   }
   return true;
}
bool arrayDeclaration(Token* aux, std::list <Token> tokensEntrada){

}
bool procedureDeclaration(Token* aux, std::list <Token> tokensEntrada){
    
}

bool typedeclaration(Token* aux, std::list<Token> TokensEntrada){
    if(Local_or_Own_type(aux, TokensEntrada)){
        if(typeList(aux, TokensEntrada)){
            return true;
        }
    }
    return false;
}

bool typeList(Token* aux, std::list <Token> tokensEntrada){
    if(simpleVariable(aux, tokensEntrada)){
        if(aux->rotulo == ","){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(typeList(aux, tokensEntrada)){
                return true;
            }
        }
        else return false;
    }
    return true;
}

bool simpleVariable(Token* aux, std::list <Token> tokensEntrada){
    
}

bool Local_or_Own_type(Token* aux, std::list<Token> tokensEntrada){
    if(aux->rotulo == "integer"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "own"){
        tokensEntrada.pop_front();
        if(aux->rotulo == "integer"){
            tokensEntrada.pop_front();
        }
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    return false;
}

bool compoundTail(Token* aux, std::list <Token> tokensEntrada){
    if(statement(aux, tokensEntrada)){
        if(aux->rotulo == "end"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
        }
        else if(aux->rotulo == ";"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
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
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
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

bool unsignedInteger(Token* aux, std::list <Token> tokensEntrada){
    if(!digitFunction(aux, tokensEntrada)){
        //recursividade
    }
    return true;
}

bool conditionalStatement(Token* aux, std::list <Token> tokensEntrada){
     if(ifStatement(aux, tokensEntrada)){
        if(aux->rotulo == "else"){ //entre no segundo ou
            if(statement(aux, tokensEntrada)){
                return true
            }
        }
        return false;
     }
     else if(ifClause(aux, tokensEntrada)){
        if(forStatement(aux, tokensEntrada)){
            return true;
        }
     }
     else if(label(aux, tokensEntrada)){
        if(aux->rotulo == ":"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            conditionalStatement(aux, tokensEntrada);
        }
    }
    return false;
}

bool forStatement(Token* aux, std::list <Token> tokensEntrada){
    if(forClause(aux, tokensEntrada)){
        if(statement(aux, tokensEntrada)){
            return true;
        }
    }
    else if(label(aux, tokensEntrada)){
        if(aux->rotulo == ":"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(forStatement(aux, tokensEntrada)){
                return true;
            }
        }
    }

    return false;
}

bool assignmentStatement(Token* aux, std::list <Token> tokensEntrada){

}

bool forClause(Token *aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "for"){
        if(variable(aux, tokensEntrada)){
            if(forlist(aux, tokensEntrada)){
                if(aux->rotulo == "do"){
                    return true;
                }
            }
        }
    }
    return false;
}
bool forlist(Token* aux, std::list <Token> tokensEntrada){
    if(!forListElement(aux, tokensEntrada)){
        //tem recursividade esquerda;
    }
}

bool forListElement(Token* aux, std::list <Token> tokensEntrada){
    if(arithmeticExpression(aux, tokensEntrada)){
        if(aux->rotulo == "step"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(arithmeticExpression(aux, tokensEntrada)){
                if(aux->rotulo == "until"){
                    tokensEntrada.pop_front();
                    Token aux1 = tokensEntrada.front();
                    aux = &aux1;
                    if(arithmeticExpression(aux, tokensEntrada)){
                        return true;
                    }
                }
            }
        }
        else if(aux->rotulo == "while"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(booleanExpression(aux, tokensEntrada)){
                return true;
            }
        }
    }
    return false;
}


bool expression(Token* aux, std::list <Token> tokensEntrada){
    if(!arithmeticExpression(aux, tokensEntrada)){
        if(!booleanExpression(aux, tokensEntrada)){
            if(!designationalExpression(aux, tokensEntrada)){
                return false;
            }
        }
    }
    return true;
}


bool arithmeticExpression(Token* aux, std::list <Token> tokensEntrada){
    if(!simpleArithmeticExpression(aux, tokensEntrada)){
        if(ifClause(aux, tokensEntrada)){
            if(simpleArithmeticExpression(aux, tokensEntrada)){
                if(aux->rotulo == "else"){
                    tokensEntrada.pop_front();
                    Token aux1 = tokensEntrada.front();
                    aux = &aux1;
                    arithmeticExpression(aux, tokensEntrada)
                }
            }
            else return false;
        }
        else return false;
    }
    return true;
}


bool simpleArithmeticExpression(Token* aux, std::list <Token> tokensEntrada){ //recursiviade a esquerda
    if(!term(aux, tokensEntrada)){
        if(addingOperator(aux, tokensEntrada)){
            if(term(aux, tokensEntrada)){
                return true;
            }
        }
        simpleArithmeticExpression(aux, tokensEntrada);
    }
}

bool addingOperator(Token *aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "+"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "-"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool term(Token* aux, std::list <Token> tokensEntrada){
    if(!factor(aux, tokensEntrada)){

    }
}

bool multiplyingOperator(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "*"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

//Recursividade a direita
bool factor(Token *aux, std::list <Token> tokensEntrada){
    if(!primary(aux, tokensEntrada)){
        factor(aux, tokensEntrada);
    }
    else return true;
}

bool primary(Token* aux, std::list <Token> tokensEntrada){
    if(!unsignedNumber(aux, tokensEntrada)){
        if(!(variable(aux, tokensEntrada)){
            if(!functionDesignator(aux, tokensEntrada)){
                if(!arithmeticExpression(aux, tokensEntrada)){
                    return false;
                }
            }
        }
    }

    return true;
}

//Revisar essa função
bool unsignedNumber(Token* aux, std::list <Token> tokensEntrada){
    if(decimalNumber(aux, tokensEntrada)){
        if(exponentialPart(aux, tokensEntrada)){
            if(decimalNumber(aux,tokensEntrada)){
                if(unsignedInteger(aux, tokensEntrada)){
                    return true;
                }
            }
        }
        return false;
    }
    else if(decimalFraction(aux, tokenEntrada)){
        return true;
    }
    else if(unsignedInteger(aux, tokensEntrada)){
        if(decimalFraction(aux, tokensEntrada)){
            return true;
        }
        else return false;
    }

    if(decimalNumber(aux, tokensEntrada){
        return true;
    }
    else return false;
}

bool exponentialPart(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "^"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(integer(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}
bool integer(Token* aux, std::list <Token> tokensEntrada){
    if(!unsignedInteger(aux, tokensEntrada)){
        if(aux->rotulo == "+"){
            if(unsignedInteger(aux, tokensEntrada)){
                return true;
            }
        }
        else if(aux->rotulo == "-"){
            if(unsignedInteger(aux, tokensEntrada)){
                return true;
            }
        }
        else return true;
    }
    return false;
}
bool decimalFraction(Token* aux, std::list <Token> tokensEntrada){
    
}
bool decimalNumber(Token* aux, std::list <Token> tokensEntrada){
    
}
bool functionDesignator(Token* aux, std::list <Token> tokensEntrada){
    if(procedureIdentifier(aux, tokensEntrada)){
        if(actualParameterPart(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool procedureIdentifier(Token* aux, std::list <Token> tokensEntrada){
    if(identifier(aux, tokensEntrada)){
        return true;
    }
    else return false;
}

bool actualParameterPart(Token* aux, std::list <Token> tokensEntrada){
    if(actualParameterList(aux, tokensEntrada)){
        return true;
    }
    return true;
    //qualquer empty vai ser considerado true, logo sempre que entrar nessa função o retorno sempre será true
}
bool actualParameterList(Token* aux, std::list <Token> tokensEntrada){
    if(actualParameter(aux, tokensEntrada)){
        //recursividade a esquerda para tirar da bnf
    }
}
bool actualParameter(Token* aux, std::list <Token> tokensEntrada){
    if(!expression(aux, tokensEntrada)){
        if(!arrayIdentifier(aux, tokensEntrada)){
            if(!procedureIdentifier(aux, tokensEntrada)){
                return false;
            }
        }
    }
    return true;
}
bool goToStatement(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "goto"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return designationalExpression(aux, tokensEntrada) ? true : false;
    }
    else return false;
}

bool dummyStatement(Token* aux, std::list <Token> tokensEntrada){
    return false;
    //retorna empty??
}

bool procedureStatement(Token* aux, std::list <Token> tokensEntrada){
    if(procedureIdentifier(aux, tokensEntrada)){
        if(actualParameterPart(aux, tokensEntrada)){
            return true;
        }
    }

    return false;
}


bool designationalExpression(Token* aux, std::list <Token> tokensEntrada){
    if(!simplesDesignationalExpression(aux, tokensEntrada)){
        if(ifClause(aux, tokensEntrada)){
            if(simplesDesignationalExpression(aux, tokensEntrada)){
                if(aux->rotulo == "else"){
                    tokensEntrada.pop_front();
                    Token aux1 = tokensEntrada.front();
                    aux = &aux1;

                    designationalExpression(aux, tokensEntrada)
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
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(booleanExpression(aux, tokensEntrada)){
            if(aux->rotulo == "then"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                return true;
            }
        }
    }
    return false;
}
bool simplesDesignationalExpression(Token* aux, std::list <Token> tokensEntrada){
    if(!label(aux, tokensEntrada)){
        if(!designationalExpression(aux, tokensEntrada)){
            return false;
        }
    }
    return true;
}
bool identifier(Token* aux, std::list <Token> tokensEntrada){
    char character;
    character = aux->rotulo[0];
    int tam = aux->rotulo.size();
    if(letter(aux, tokensEntrada, character)){
        if(auxIdentifier(aux, tokensEntrada, character, 0, tam))
        {
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
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
    if(!simpleBoolean(aux, tokensEntrada)){
        if(ifClause(aux, tokensEntrada)){
            if(simpleBoolean(aux, tokensEntrada)){
                if(aux->rotulo == "else"){
                    tokensEntrada.pop_front();
                    Token aux1 = tokensEntrada.front();
                    aux = &aux1;
                    booleanExpression(aux, tokensEntrada);
                }
                else return false;
            }
            else return false;
        }
        else return false;
    }
    else return true;
}

bool simpleBoolean(Token * aux, std::list <Token> tokensEntrada){
    if(!implication(aux, tokensEntrada)){
         //recursividade a esquerda
    }
}
bool implication(Token * aux, std::list <Token> tokensEntrada){
    if(booleanTerm(aux, tokensEntrada)){
        return true;
    }
    else return false;
}

bool booleanTerm(Token * aux, std::list <Token> tokensEntrada){
    //recursividade esquerda
}
bool booleanFactor(Token * aux, std::list <Token> tokensEntrada){
    //recursividade esquerda
}

bool booleanSecondary(Token * aux, std::list <Token> tokensEntrada){
    if(!booleanPrimary(aux, tokensEntrada)){
        if(aux->rotulo == "!"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(booleanPrimary(aux, tokensEntrada)){
                return true;
            }
        }
        return false;
    }
    else return true;
}

bool booleanPrimary(Token * aux, std::list <Token> tokensEntrada){

}

bool ifStatement(Token * aux, std::list <Token> tokensEntrada){
    if(ifClause(aux, tokensEntrada)){
        if(uncoditionalStatement(aux, tokensEntrada)){
            return true;
        }
    }

    return false;
}

bool variable(Token* aux, std::list <Token> tokensEntrada){
    if(!simpleVariable(aux, tokensEntrada)){
        if(!subscriptedVariable(aux, tokensEntrada)){
            return false;
        }
    }
    return true;
}

bool simpleVariable(Token* aux, std::list <Token> tokensEntrada){
    if(variableIdenfier(aux, tokensEntrada)){
        return true;
    }
    else return false;
}
bool subscriptedVariable(Token* aux, std::list <Token> tokensEntrada){
    if(arrayIdentifier(aux, tokensEntrada)){
        if(aux->rotulo == "["){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(subscriptList(aux, tokensEntrada)){
                if(aux->rotulo == "]"){
                    tokensEntrada.pop_front();
                    Token aux1 = tokensEntrada.front();
                    aux = &aux1;
                    return true;
                }
            }
        }
    }
    return false;
}
bool arrayIdentifier(Token * aux, std::list <Token> tokensEntrada){
    if(identifier(aux, tokensEntrada)){
        return true;
    }
    else return false;
}
bool subscriptList(Token * aux, std::list <Token> tokensEntrada){
    if(!subscriptExpression(aux, tokensEntrada)){
        if(subscriptList(aux, tokensEntrada)){ //recursividade a esquerda [retirar]
            if(aux->rotulo == ","){
                if(subscriptExpression(aux, tokensEntrada)){
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

bool subscriptExpression(Token * aux, std::list <Token> tokensEntrada){
    if(arithmeticExpression(aux, tokensEntrada)){
        return true;
    }
    else return false;
}

bool letter(Token* aux, std::list <Token> tokensEntrada, char character){
    //VERIFICAR TODOS OS TERMINAIS DE LETRAS
    char letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    if(ChecaValidos(letters, character, sizeof(letters)/ sizeof(letters[0]))){
        return true;
    }
    else return false;
}

bool digitFunction(Token* aux, std::list <Token> tokensEntrada, char character){
    //terminais digitos
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        return true;
    }
    else return false;
}