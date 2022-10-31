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

    if(block(&aux, tokensEntrada)){
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
        }
    }
    else{
        //add na lista de erros;
        return tokensEntrada;
    }
    std::cout << "PILHA NO SINTATICO" << std::endl;
    for (auto i : tokensEntrada){
        std::cout << i.rotulo << " - " << i.tipo << std::endl;
    }
    return tokensEntrada;
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
    if (blockHead(aux, tokensEntrada)){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;

        if (tokensEntrada.front().rotulo == ";")
        {
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if (compoundTail(aux, tokensEntrada)){
                return true;
            }
        }
    }
    return false;
}

bool blockHead(Token* aux, std::list<Token> tokensEntrada){
    if(aux->rotulo == "begin"){
        std::cout << "AQUI O BEGIN DO BLOCKHEAD" << std::endl;
        tokensEntrada.pop_front();

        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(declaration(aux, tokensEntrada)){
            return true;
        }
        else {
            return false;
        }
    }
    else{
        if(blockaux(aux, tokensEntrada)){
            return true;
        }
        else{
            //Colocar uma opção para ir add a lista de erro
            return false;
        }
    }
}

bool blockaux(Token* aux, std::list<Token> tokensEntrada){
    if (!declaration(aux, tokensEntrada)){
        return true;
    }
    else {
        blockaux(aux, tokensEntrada);
    }
    return false;
}

bool compoundStatement(Token* aux, std::list <Token> tokensEntrada){
    if(!unlabelledCompound(aux, tokensEntrada)){
        if(label(aux, tokensEntrada)){
            if(aux->rotulo == ":"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                compoundStatement(aux, tokensEntrada);
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
        return compoundTail(aux, tokensEntrada) ? true : false;
    }else return false;
}

bool declaration(Token* aux, std::list <Token> TokensEntrada){
    std::cout <<"Depois do primeiro POP " << TokensEntrada.front().rotulo << std::endl;

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
    if(aux->rotulo == "array"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(arrayList(aux, tokensEntrada)){
            return true;
        }
    }
    else if(Local_or_Own_type(aux, tokensEntrada)){
        if(aux->rotulo=="array"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        
            if(arrayList(aux, tokensEntrada)){
                return true;
            }
        }
    }
    return false;
}

bool arrayList(Token* aux, std::list <Token> tokensEntrada){
    if(arraySegment(aux, tokensEntrada)){
        if(auxArrayList(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}
bool auxArrayList(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        
        if(arraySegment(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool arraySegment(Token* aux, std::list <Token> tokensEntrada){
    if(arrayIdentifier(aux, tokensEntrada)){
        if(aux->rotulo == "["){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        
            if(boundPairList(aux, tokensEntrada)){
                if(aux->rotulo == "]"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
        
                return true;
                }
            }
        }
        else if(aux->rotulo == ","){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        
            if(arraySegment(aux, tokensEntrada)){
                return true;
            }
        }
    }

    return false;
}

bool boundPairList(Token* aux, std::list <Token> tokensEntrada){
    if(boundPair(aux, tokensEntrada)){
       if(auxBoundPair(aux,tokensEntrada)){
            return true;
       }
    }
    return false;
}

bool auxBoundPair(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        
        if(boundPair(aux, tokensEntrada)){
            auxBoundPair(aux, tokensEntrada);
        }
        else return false;
    }
    return true;
}

bool boundPair(Token* aux, std::list <Token> tokensEntrada){
    if(lowerBound(aux, tokensEntrada)){
        if(aux->rotulo == ":"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        
            if(lowerBound(aux,tokensEntrada)){
                return true;
            }
        }
    }
    return false;
}

bool lowerBound(Token* aux, std::list <Token> tokensEntrada){
    return arithmeticExpression(aux, tokensEntrada) ? true : false;
}

bool procedureDeclaration(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "procedure"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(procedureHeading(aux, tokensEntrada)){
            if(procedureBody(aux, tokensEntrada)){
                return true;
            }
        }
    }
    else if(type(aux, tokensEntrada)){
        if(aux->rotulo == "procedure"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        
            if(procedureHeading(aux, tokensEntrada)){
                if(procedureBody(aux, tokensEntrada)){
                    return true;
                }
            }
        }
    }

    return false;
}

bool type(Token* aux, std::list <Token> tokensEntrada){
    if(integer(aux, tokensEntrada)){
        return true;
    }
    else return false;
}

bool procedureHeading(Token* aux, std::list <Token> tokensEntrada){
    if(procedureIdentifier(aux, tokensEntrada)){
        if(formalParameterPart(aux, tokensEntrada)){
            if(aux->rotulo == ";"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                if(valuePart(aux, tokensEntrada)){
                    if(specificationPart(aux, tokensEntrada)){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool specificationPart(Token* aux, std::list <Token> tokensEntrada){
     if(auxSpecificationPart(aux, tokensEntrada)){
        return true;
     }
     else if(specifier(aux, tokensEntrada)){
        if(identifierList(aux, tokensEntrada)){
            if(aux->rotulo == ";"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                
                if(auxSpecificationPart(aux, tokensEntrada)){
                    return true;
                }
            }
        }
     }
     return false;
}

bool auxSpecificationPart(Token* aux, std::list <Token> tokensEntrada){
     if((specifier(aux, tokensEntrada))){
        if(identifierList(aux, tokensEntrada)){
            auxSpecificationPart(aux, tokensEntrada);
        }
        else return false;
     }
     return true;
}

bool identifierList(Token* aux, std::list <Token> tokensEntrada){
    if(identifier(aux, tokensEntrada)){
        if(auxIdentifierList(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool auxIdentifierList(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(identifier(aux, tokensEntrada)){
            auxIdentifierList(aux,tokensEntrada);
        }else return false;
    }
    return true;
}

bool specifier(Token* aux, std::list <Token> tokensEntrada){
     if(aux->rotulo == "array"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
     }
     else if(aux->rotulo == "label"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
     }
     else if(aux->rotulo == "procedure"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
     }
     else{
        if(type(aux, tokensEntrada)){
            if(aux->rotulo == "procedure"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                return true;
            }
        }
        return false;
     }
}

bool valuePart(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "value"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(identifierList(aux, tokensEntrada)){
            if(aux->rotulo==";")
            {
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
            }
        }
        else return false;
    }

    return true;
}

bool formalParameterPart(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "("){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(formalParameterList(aux, tokensEntrada)){
            if(aux->rotulo == ")"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
            }
            else return false;
        }
    }
    return true;
}

bool formalParameterList(Token* aux, std::list <Token> tokensEntrada){
    if(formalParameter(aux, tokensEntrada)){
        if(auxFormalParameterList(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool auxFormalParameterList(Token* aux, std::list <Token> tokensEntrada){
    if(parameterDelimiter(aux, tokensEntrada)){
        if(formalParameter(aux, tokensEntrada)){
            auxFormalParameterList(aux, tokensEntrada);
        }
        else return false;
    }
    
    return true;
}

bool parameterDelimiter(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool formalParameter(Token* aux, std::list <Token> tokensEntrada){
    return identifier(aux, tokensEntrada) ? true : false;
}

bool procedureBody(Token* aux, std::list <Token> tokensEntrada){
    return statement(aux, tokensEntrada) ? true : false;
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
        else return true;
    }
    return false;
}

bool simpleVariable(Token* aux, std::list <Token> tokensEntrada){
    return variableIdenfier(aux, tokensEntrada) ? true : false;
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
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(aux->rotulo == "integer"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        }
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
    }
    return false;
}

bool unsignedInteger(Token* aux, std::list <Token> tokensEntrada){
    int i = 0;
    char character = aux->rotulo[0];
    int tam = aux->rotulo.size();
    
    if(digit(aux, tokensEntrada, character)){
        return true;
    }
    else{
        unsignedIntegerAux(aux, tokensEntrada, character, i, tam);
    }
    return false;
}

bool unsignedIntegerAux(Token* aux, std::list <Token> tokensEntrada, char character, int i, int tam){
    i++;
    if(i == tam-1){
        return true;
    }
    else{
        if(digit(aux, tokensEntrada, character)){
            character = aux->rotulo[i];
            unsignedIntegerAux(aux, tokensEntrada, character, i, tam);
        }
        return false;
    }
}

bool conditionalStatement(Token* aux, std::list <Token> tokensEntrada){
     if(ifStatement(aux, tokensEntrada)){
        if(aux->rotulo == "else"){ //entre no segundo ou
            if(statement(aux, tokensEntrada)){
                return true;
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
    if(arithmeticExpression(aux, tokensEntrada)){
        return true;
    }
    else if (leftPart(aux, tokensEntrada)){
        return true;
    }
    return false;
}

bool leftPart(Token* aux, std::list <Token> tokensEntrada){
    if(variable(aux, tokensEntrada)){
        if(aux->rotulo == ":="){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            
            return true;
        }
    }
    else if(procedureIdentifier(aux, tokensEntrada)){
        if(aux->rotulo == ":="){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            
            return true;
        }
    }

    return false;
}
bool forClause(Token *aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "for"){
        if(variable(aux, tokensEntrada)){
            if(forList(aux, tokensEntrada)){
                if(aux->rotulo == "do"){
                    return true;
                }
            }
        }
    }
    return false;
}

bool forList(Token* aux, std::list <Token> tokensEntrada){
    if(forListElement(aux, tokensEntrada)){
        if(forListAux(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool forListAux(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(forListElement(aux, tokensEntrada)){
            forListAux(aux, tokensEntrada);
        }
        else return false;
    }
    return true;
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
                    arithmeticExpression(aux, tokensEntrada);
                }
            }
            else return false;
        }
        else return false;
    }
    return true;
}

bool simpleArithmeticExpression(Token* aux, std::list <Token> tokensEntrada){ //recursiviade a esquerda
    if(term(aux, tokensEntrada)){
        return true;
    }else if(addingOperator(aux, tokensEntrada)){
        return true;
    }
    else if(auxSimpleArithmeticExpression(aux, tokensEntrada)){
        return true;
    }
    else return false;
}
bool auxSimpleArithmeticExpression(Token* aux, std::list <Token> tokensEntrada){ //recursiviade a esquerda
    if(addingOperator(aux, tokensEntrada)){
        if(term(aux,tokensEntrada)){
            auxSimpleArithmeticExpression(aux,tokensEntrada);
        }
        else return false;
    }
    return true;
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
    if(factor(aux, tokensEntrada)){
        if(auxTerm(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool auxTerm(Token* aux, std::list <Token> tokensEntrada){
     if(multiplyingOperator(aux, tokensEntrada)){
        if(factor(aux, tokensEntrada)){
            auxTerm(aux, tokensEntrada);
        }
        else return false;
     }

    return true;
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

bool factor(Token *aux, std::list <Token> tokensEntrada){
    if(!primary(aux, tokensEntrada)){
        factor(aux, tokensEntrada);
    }

    return true;
}

bool primary(Token* aux, std::list <Token> tokensEntrada){
        if(!(variable(aux, tokensEntrada))){
            if(!functionDesignator(aux, tokensEntrada)){
                if(!arithmeticExpression(aux, tokensEntrada)){
                    return false;
                }
            }
        }
    return true;
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

bool functionDesignator(Token* aux, std::list <Token> tokensEntrada){
    if(procedureIdentifier(aux, tokensEntrada)){
        if(actualParameterPart(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool procedureIdentifier(Token* aux, std::list <Token> tokensEntrada){
    return identifier(aux, tokensEntrada) ? true : false;
}

bool actualParameterPart(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "("){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if (actualParameterList(aux, tokensEntrada)){
            if ( aux->rotulo == ")"){
                tokensEntrada.pop_front();
                Token aux1 = tokensEntrada.front();
                aux = &aux1;
                return true;
            }
        }
        return false;
    }
    else {
        return true;
    }
}

bool actualParameterList(Token* aux, std::list <Token> tokensEntrada){
    if(actualParameter(aux, tokensEntrada)){
        if(actualParameterListAux(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool actualParameterListAux(Token* aux, std::list <Token> tokensEntrada){
    if(parameterDelimiter(aux, tokensEntrada)){
        if(actualParameter(aux, tokensEntrada)){
            actualParameterListAux(aux, tokensEntrada);
        }
        else return false;
    }
    return true;
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
    return true;
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

                    designationalExpression(aux, tokensEntrada);
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

bool basicSymbol(Token* aux, std::list <Token> tokensEntrada, char character){
    if(!letter(aux, tokensEntrada, character)){
        if(!digit(aux, tokensEntrada, character)){
            if(!logicalValue(aux, tokensEntrada)){
                if(!delimiterFunction(aux, tokensEntrada)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool delimiterFunction(Token* aux, std::list <Token> tokensEntrada){
    if(!operatorFunction(aux, tokensEntrada)){
        if(!separator(aux, tokensEntrada)){
            if(!bracket(aux, tokensEntrada)){
                if(!declator(aux, tokensEntrada)){
                    if(!specificator(aux, tokensEntrada)){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


bool separator(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == ","){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == ":"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == ";"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == ":="){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == "_"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == "step"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == "until"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;

    }
    else if(aux->rotulo == "while"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "comment"){
        while(aux->rotulo != ";"){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
        }
        return true;
    }
    else return false;
}

bool operatorFunction(Token* aux, std::list <Token> tokensEntrada){
    if(!arithmeticOperator(aux, tokensEntrada)){
        if(!relationalOperator(aux, tokensEntrada)){
            if(!logicalOperator(aux, tokensEntrada)){
                if(!sequentialOperator(aux, tokensEntrada)){
                    return false;
                }
            }
        }
    }
    return true;
}
bool bracket(Token* aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "("){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            return true;
    }
    else if(aux->rotulo == ")"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "["){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "]"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "begin"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "end"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;

}

bool declator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "own"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if (aux->rotulo == "integer"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if (aux->rotulo == "array"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if (aux->rotulo == "procedure"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool specificator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "label" || aux->rotulo == "value"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    return false;
}

bool arithmeticOperator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "+" || aux->rotulo == "-" || aux->rotulo == "*" || aux->rotulo == "/"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool relationalOperator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "<" || aux->rotulo == "<=" || aux->rotulo == "=" || aux->rotulo == "!=" || aux->rotulo == ">" || aux->rotulo == ">="){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool logicalOperator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "==" || aux->rotulo == "||" || aux->rotulo == "&&" || aux->rotulo == "!"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool sequentialOperator(Token* aux, std::list <Token> tokensEntrada){
    if (aux->rotulo == "goto" || aux->rotulo == "if" || aux->rotulo == "then" || aux->rotulo == "else" || aux->rotulo == "for" || aux->rotulo == "do"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
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
        else if(digit(aux, tokensEntrada, character)){
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
    return true;
}

bool simpleBoolean(Token * aux, std::list <Token> tokensEntrada){
    if(implication(aux, tokensEntrada)){
       if(auxSimpleBoolean(aux, tokensEntrada)){
            return true;
       } 
    }
    return false;
}
bool auxSimpleBoolean(Token *aux, std::list<Token> tokensEntrada){
    if(aux->rotulo == "="){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(aux->rotulo == "="){
            tokensEntrada.pop_front();
            Token aux1 = tokensEntrada.front();
            aux = &aux1;
            if(implication(aux, tokensEntrada)){
                auxSimpleBoolean(aux, tokensEntrada);
            }
        }
        else return false;
    }
    return true;
}

bool implication(Token * aux, std::list <Token> tokensEntrada){
    if(booleanTerm(aux, tokensEntrada)){
        return true;
    }
    else return false;
}

bool booleanTerm(Token * aux, std::list <Token> tokensEntrada){
    if(booleanFactor(aux, tokensEntrada)){
        if(auxBooleanTerm(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool auxBooleanTerm(Token * aux, std::list <Token> tokensEntrada){
     if(aux->rotulo == "||"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(booleanFactor(aux, tokensEntrada)){
            auxBooleanTerm(aux, tokensEntrada);
        }
        else return false;
    }

    return true;
}
bool booleanFactor(Token * aux, std::list <Token> tokensEntrada){
    if(booleanSecondary(aux, tokensEntrada)){
        if(auxBooleanFactor(aux, tokensEntrada)){
            return true;
        }
    }
    return false;
}

bool auxBooleanFactor(Token * aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "&&"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        if(booleanSecondary(aux, tokensEntrada)){
            auxBooleanFactor(aux, tokensEntrada);
        }
        else return false;
    }

    return true;
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
    if(!logicalValue(aux, tokensEntrada)){
        if(!variable(aux, tokensEntrada)){
            if(!functionDesignator(aux, tokensEntrada)){
                if(!relation(aux, tokensEntrada)){
                    if(aux->rotulo == "("){
                        tokensEntrada.pop_front();
                        Token aux1 = tokensEntrada.front();
                        aux = &aux1;
                        if(booleanExpression(aux,tokensEntrada)){
                            if(aux->rotulo == ")"){
                                tokensEntrada.pop_front();
                                Token aux1 = tokensEntrada.front();
                                aux = &aux1;
                                return true;
                            }
                        }
                    }
                    else return false;
                }
            }
        }
    }

    return true;
}


bool logicalValue(Token * aux, std::list <Token> tokensEntrada){
    if(aux->rotulo == "true"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else if(aux->rotulo == "false"){
        tokensEntrada.pop_front();
        Token aux1 = tokensEntrada.front();
        aux = &aux1;
        return true;
    }
    else return false;
}

bool relation(Token * aux, std::list <Token> tokensEntrada){
    if(simpleArithmeticExpression(aux, tokensEntrada)){
        if(relationalOperator(aux, tokensEntrada)){
            if(simpleArithmeticExpression(aux, tokensEntrada)){
                return true;
            }
        }
    }
    return false;
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

bool variableIdenfier(Token* aux, std::list <Token> tokensEntrada){
    return identifier(aux, tokensEntrada) ? true : false;
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
    return identifier(aux, tokensEntrada) ? true : false;
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
    return arithmeticExpression(aux, tokensEntrada) ? true : false;
}

bool letter(Token* aux, std::list <Token> tokensEntrada, char character){
    //VERIFICAR TODOS OS TERMINAIS DE LETRAS
    char letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    if(ChecaValidos(letters, character, sizeof(letters)/ sizeof(letters[0]))){
        return true;
    } else return false;
}

bool digit(Token* aux, std::list <Token> tokensEntrada, char character){
    //terminais digitos
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        return true;
    }
    else return false;
}