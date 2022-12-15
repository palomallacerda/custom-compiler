#include <iostream>
#include "header.h"
#include "AnalisadorLexico.cpp"

int pos = 0;
TabelaPred tabelaAtual;
std::vector<Token> erros;

std::vector<Token> inicialState(std::vector<Token> tokensEntrada){
    //Começa percorrer a bnf
    procedureDeclaration(tokensEntrada);

    if(pos == tokensEntrada.size() - 1){
        if(!erros.empty()){
            std::cout << "Foram encontrados os seguintes erros:" << std::endl;
            for (auto i: erros)
            {
                std::cout << i.tipo << " - " << i.rotulo << std::endl;
            }
        }
    }
    else{
        std::cout << "Erro na análise sintática" << std::endl;
        std::cout << "PILHA NO SINTATICO" << std::endl;
        int it = pos;
        for (it; it < tokensEntrada.size(); it++){
            std::cout << tokensEntrada[it].rotulo << " - " << tokensEntrada[it].tipo << std::endl;
        }
    }
    
    return tokensEntrada;
}

bool match(std::string character, std::vector<Token> tokensEntrada){
    
    if(tokensEntrada.at(pos).rotulo == character){
        std::cout << "Posição encontrada" << pos << std::endl;
        std::cout << "Token: " << tokensEntrada.at(pos).rotulo << std::endl;
        
        std::cout << "Char encontrado: " << character << std::endl;
        //std::cout << "Posição no vector: " << pos << std::endl;
        //addToTable(tokensEntrada.at(pos));
        pos++;
        return true;
    }
    else{
        std::cout << "Posição ERRADA encontrada " << pos << std::endl;
        std::cout << "Token ERRADO: " << tokensEntrada.at(pos).rotulo << std::endl;
        std::cout << "Char comparado ERRADO: " << character << std::endl;
        
        return false;
    }
}

//VERIFICAR TODOS OS TERMINAIS DE LETRAS
bool matchLetter(std::vector<Token> tokensEntrada){
    char letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char character = tokensEntrada.at(pos).rotulo[0];

    if(ChecaValidos(letters, character, sizeof(letters)/ sizeof(letters[0]))){
        std::string conChar(1, character);
        if (match(tokensEntrada.at(pos).rotulo, tokensEntrada)){
            return true;
        }
    }
    else{
        std::cout << "Função erro MacthLetter" << std::endl;
        return false;
    }
    //return false;
}

//VERIFICAR TODOS OS TERMINAIS DE DIGITOS
bool matchDigit(std::vector<Token> tokensEntrada){
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char character = tokensEntrada.at(pos).rotulo[0];
    std::cout << "Digito: " << character << std::endl;

    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        std::string conChar(1, character);
        if (match(conChar, tokensEntrada)){
            return true;
        }
    }
    else{
        return false;
    }
    //return false;
}

// Função para adicionar símbolo na tabela de precedência
void addToTable(Token current){
// Funcionamento: Procurar o rotulo do token em uma das listas de escopo global ou local e adicionar seu valor inicial
}

bool program(std::vector<Token> tokensEntrada){
    std::cout << "Função: program" << std::endl;
    return (block(tokensEntrada) || compoundStatement(tokensEntrada));
}

bool block(std::vector<Token> tokensEntrada){
    std::cout << "Função: block" << std::endl;
    int auxPos = pos;
    if (!unlabelledBlock(tokensEntrada)){
        pos = auxPos;
        
        if (!(label(tokensEntrada) && match(":", tokensEntrada) && block(tokensEntrada))){
            pos = auxPos;
            return false;
        }
    }
    return (true);
}

bool unlabelledBlock(std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledBlock" << std::endl;
    return (blockHead(tokensEntrada) && match(";", tokensEntrada) && compoundTail(tokensEntrada));
}

bool blockHead(std::vector<Token> tokensEntrada){
    std::cout << "Função: blockHead" << std::endl;
    return ((match("begin", tokensEntrada) && declaration(tokensEntrada) && blockAux(tokensEntrada)));
}

bool blockAux(std::vector<Token> tokensEntrada){
    std::cout << "Função: blockAux" << std::endl;
    int auxPos = pos;
    if(match(";", tokensEntrada) ){
        if(declaration(tokensEntrada) ){
            blockAux(tokensEntrada);
        }
        else {
            pos = auxPos;
        }
    }
    return true;
}

bool compoundStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: compoundStatement" << std::endl;
    int auxPos = pos;
    if (not unlabelledCompound(tokensEntrada)){
        pos = auxPos;
        if (not ((label(tokensEntrada) && match(":", tokensEntrada) && compoundStatement(tokensEntrada)))){
            pos = auxPos;
            return false;
        }
    }
    return true;
}

bool unlabelledCompound(std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledCompound" << std::endl;
    return (match("begin", tokensEntrada) && compoundTail(tokensEntrada));
}

bool compoundTail(std::vector<Token> tokensEntrada){
    std::cout << "Função: compoundTail" << std::endl;
    // return ((statement(tokensEntrada) && match("end", tokensEntrada))  || (statement(tokensEntrada) && match(";", tokensEntrada) && compoundTail(tokensEntrada)));
    int auxPos = pos;
    if (!(statement(tokensEntrada) && match("end", tokensEntrada))){
        pos = auxPos;
        if (!(statement(tokensEntrada) && match(";", tokensEntrada) && compoundTail(tokensEntrada))){
            pos = auxPos;
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

bool declaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: declaration" << std::endl;
    return(typedeclaration(tokensEntrada) || arrayDeclaration(tokensEntrada) || procedureDeclaration(tokensEntrada));
}

bool typedeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: typeDeclaration" << std::endl;
    return(localOrOwnType(tokensEntrada) && typeList(tokensEntrada));
}

bool localOrOwnType(std::vector<Token> tokensEntrada){
    std::cout << "Função: localOrOwnType" << std::endl;
    return (type(tokensEntrada) || (match("own", tokensEntrada) && type(tokensEntrada)));
}

bool type(std::vector<Token> tokensEntrada){
    std::cout << "Função: type" << std::endl;
    return (match("integer", tokensEntrada));
}

bool typeList(std::vector<Token> tokensEntrada){
    std::cout << "Função: typeList" << std::endl;
    int auxPos = pos;
    if (not (simpleVariable(tokensEntrada) && (match(",", tokensEntrada) && typeList(tokensEntrada)))){
        pos = auxPos;
        if (not (simpleVariable(tokensEntrada))){
            pos = auxPos;
            return false;
        }
    }
    return (true);
}

bool arrayDeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayDeclaration" << std::endl;
    return ((match("array", tokensEntrada) && arrayList(tokensEntrada)) || (localOrOwnType(tokensEntrada) && match("array", tokensEntrada) && arrayList(tokensEntrada)));
}

bool arrayList(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayList" << std::endl;
    return (arraySegment(tokensEntrada) && auxArrayList(tokensEntrada));
}

bool auxArrayList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxArrayList" << std::endl;
    return ((match(",", tokensEntrada) && arraySegment(tokensEntrada) && auxArrayList(tokensEntrada)) || true);
}

bool arraySegment(std::vector<Token> tokensEntrada){
    std::cout << "Função: arraySegment" << std::endl;
    return ((arrayIdentifier(tokensEntrada) && (match("[", tokensEntrada) && boundPairList(tokensEntrada) && match("]", tokensEntrada))) || (arrayIdentifier(tokensEntrada) && match(",", tokensEntrada) && arraySegment(tokensEntrada))); 
}

bool arrayIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayIdentifier" << std::endl;
    return identifier(tokensEntrada);
}

bool boundPairList(std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPairList" << std::endl;
    return (boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada));
}

bool auxBoundPairList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxBoundPairList" << std::endl;
    return((match(",", tokensEntrada) && boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada)) || true);
}

bool boundPair(std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPair" << std::endl;
    return(lowerBound(tokensEntrada) && match(":", tokensEntrada) && lowerBound(tokensEntrada));
}

bool lowerBound(std::vector<Token> tokensEntrada){
    std::cout << "Função: lowerBound" << std::endl;
    return arithmeticExpression(tokensEntrada);
}

bool procedureDeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureDeclaration" << std::endl;
    return ((match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada)) || (type(tokensEntrada) && match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada)));
}

bool procedureHeading(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureHeading" << std::endl;
    return (procedureIdentifier(tokensEntrada) && formalParameterPart(tokensEntrada) && match(";", tokensEntrada) && valuePart(tokensEntrada) && specificationPart(tokensEntrada));
}

bool procedureIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureIdentifier" << std::endl;
    return identifier(tokensEntrada);
}

bool formalParameterPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterPart" << std::endl;
    return ((match("(", tokensEntrada) && formalParameterList(tokensEntrada) && match(")", tokensEntrada)) || true);
}

bool formalParameterList(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterList" << std::endl;
    return(formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada));
}

bool auxFormalParameterList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxFormalParameterList" << std::endl;
    return ((parameterDelimiter(tokensEntrada) && formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada) || true));
}

bool formalParameter(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameter" << std::endl;
    return identifier(tokensEntrada);
}

bool valuePart(std::vector<Token> tokensEntrada){
    std::cout << "Função: valuePart" << std::endl;
    return ((match("value", tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada)) || true);
}

bool specificationPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: specificationPart" << std::endl;
    return (((specifier(tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada) && auxSpecificationPart(tokensEntrada))) || true);
}

bool auxSpecificationPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxSpecificationPart" << std::endl;
    return ((specifier(tokensEntrada) && identifierList(tokensEntrada) && auxSpecificationPart(tokensEntrada)) || true);
}

bool specifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: specifier" << std::endl;
    return (type(tokensEntrada) || match("array", tokensEntrada) || (type(tokensEntrada) && match("array", tokensEntrada)) || match("label", tokensEntrada) || match("procedure", tokensEntrada) || (type(tokensEntrada) && match("procedure", tokensEntrada)));
}

bool identifierList(std::vector<Token> tokensEntrada){
    std::cout << "Função: identifierList" << std::endl;
    return (identifier(tokensEntrada) && auxIdentifierList(tokensEntrada));
}

bool auxIdentifierList(std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && identifier(tokensEntrada) && auxIdentifierList(tokensEntrada)) || true);
}

bool procedureBody(std::vector<Token> tokensEntrada){
    return (statement(tokensEntrada) || true); //tem um <code> aqui na bnf
}

bool statement(std::vector<Token> tokensEntrada){
    std::cout << "Função: statement" << std::endl;
    return (unconditionalStatement(tokensEntrada) || conditionalStatement(tokensEntrada) || forStatement(tokensEntrada));
}

bool unconditionalStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função unconditionalStatement" << std::endl;
    return (basicStatement(tokensEntrada) || compoundStatement(tokensEntrada) || block(tokensEntrada));
}

bool basicStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: basicStatement" << std::endl;
    return (unlabelledBasicStatement(tokensEntrada) || (label(tokensEntrada) && match(":", tokensEntrada) && basicStatement(tokensEntrada)));
}

bool label(std::vector<Token> tokensEntrada){
    std::cout << "Função: label" << std::endl;
    return (identifier(tokensEntrada) || unsignedInteger(tokensEntrada));
}

bool unlabelledBasicStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledBasicStatement" << std::endl;
    return (assignmentStatement(tokensEntrada) || goToStatement(tokensEntrada) || procedureStatement(tokensEntrada));
}

bool assignmentStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: assignmentStatement" << std::endl;
    return ((leftPartList(tokensEntrada) && arithmeticExpression(tokensEntrada)) || (leftPartList(tokensEntrada) && booleanExpression(tokensEntrada)));
}

bool leftPartList(std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPartList" << std::endl;
    return (leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada));
}

bool auxLeftPartList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxLeftPartList" << std::endl;
    return ((leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada)) || true);
}
//Correto
bool leftPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPart" << std::endl;
    return ((variable(tokensEntrada) && match(":=", tokensEntrada)) || (procedureIdentifier(tokensEntrada) && match(":=", tokensEntrada)));
}

bool goToStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: goToStatement" << std::endl;
    return (match("goto", tokensEntrada) && designationalExpression(tokensEntrada));
}

bool designationalExpression(std::vector<Token> tokensEntrada){
    return (simpleDesignationalExpression(tokensEntrada) || (ifClause(tokensEntrada) && simpleDesignationalExpression(tokensEntrada) && match("else", tokensEntrada) && designationalExpression(tokensEntrada) ) );
}

bool simpleDesignationalExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleDesignationalExpression" << std::endl;
    return (label(tokensEntrada) || (match("(", tokensEntrada) && designationalExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool procedureStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureStatement" << std::endl;
    return ((procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada)));
}

bool actualParameterPart(std::vector<Token> tokensEntrada){
    return (true || (match("(", tokensEntrada) && actualParameterList(tokensEntrada) && match(")", tokensEntrada)));
}

bool actualParameterList(std::vector<Token> tokensEntrada){
    return (actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada));
}

bool auxActualParameterList(std::vector<Token> tokensEntrada){
    return ((parameterDelimiter(tokensEntrada) && actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada)) || true);
}

bool parameterDelimiter(std::vector<Token> tokensEntrada){
    return (match(",", tokensEntrada));
}

bool actualParameter(std::vector<Token> tokensEntrada){
    std::cout << "Função: actualParameter" << std::endl;
    return (expression(tokensEntrada) || arrayIdentifier(tokensEntrada) || procedureIdentifier(tokensEntrada));
}

bool conditionalStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: conditionalStatement" << std::endl;
    return ((ifStatement(tokensEntrada)) || (ifStatement(tokensEntrada) && match("else", tokensEntrada) && statement(tokensEntrada)) || 
    (ifClause(tokensEntrada) && forStatement(tokensEntrada)) || (label(tokensEntrada) && match(":", tokensEntrada) && conditionalStatement(tokensEntrada)));
}

bool ifStatement(std::vector<Token> tokensEntrada){
    return (ifClause(tokensEntrada) && unconditionalStatement(tokensEntrada));
}

bool ifClause(std::vector<Token> tokensEntrada){
    return ((match("if", tokensEntrada) && booleanExpression(tokensEntrada) && match("then", tokensEntrada)));
}

bool forStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: forStatement" << std::endl;
    return ((forClause(tokensEntrada) && statement(tokensEntrada)) || (label(tokensEntrada) && match(":", tokensEntrada) && forStatement(tokensEntrada)));
}

bool forClause(std::vector<Token> tokensEntrada){
    return (match("for", tokensEntrada) && variable(tokensEntrada) && match(":=", tokensEntrada) && forList(tokensEntrada) && match("do", tokensEntrada));
}

bool forList(std::vector<Token> tokensEntrada){
    return (forListElement(tokensEntrada) && auxForList(tokensEntrada));
}
bool auxForList(std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && forListElement(tokensEntrada) && auxForList(tokensEntrada)) || true);
}

bool forListElement(std::vector<Token> tokensEntrada){
    std::cout << "Função: forListElement" << std::endl;
    return ((arithmeticExpression(tokensEntrada)) || (arithmeticExpression(tokensEntrada) && match("step" , tokensEntrada) && arithmeticExpression(tokensEntrada) && match("until", tokensEntrada) && 
    arithmeticExpression(tokensEntrada)) || (arithmeticExpression(tokensEntrada) && match("while" , tokensEntrada) && booleanExpression(tokensEntrada)));
}

bool expression(std::vector<Token> tokensEntrada){
    std::cout << "Função: expression" << std::endl;
    return (arithmeticExpression(tokensEntrada) || booleanExpression(tokensEntrada) || designationalExpression(tokensEntrada));
}

bool arithmeticExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: arithmeticExpression" << std::endl;
    return (simpleArithmeticExpression(tokensEntrada) || ((ifClause(tokensEntrada) && simpleArithmeticExpression(tokensEntrada) &&
    match("else", tokensEntrada) && arithmeticExpression(tokensEntrada))));
}

bool simpleArithmeticExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleArithmeticExpression" << std::endl;
    return ((term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)) || (addingOperator(tokensEntrada) && term(tokensEntrada)
    && auxSimpleArithmeticExpression(tokensEntrada)));
}

bool auxSimpleArithmeticExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxSimpleArithmeticExpression" << std::endl;
    return ((addingOperator(tokensEntrada) && term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)) || true);
}

bool addingOperator(std::vector<Token> tokensEntrada){
    return (match("+", tokensEntrada) || match("-", tokensEntrada));
}

bool term(std::vector<Token> tokensEntrada){
    std::cout << "Função: term" << std::endl;
    return (factor(tokensEntrada) && auxTerm(tokensEntrada));
}

bool auxTerm(std::vector<Token> tokensEntrada){
    return ((multiplyingOperator(tokensEntrada) && factor(tokensEntrada) && auxTerm(tokensEntrada)) || true);
}

bool multiplyingOperator(std::vector<Token> tokensEntrada){
    return (match("*", tokensEntrada));
}

bool factor(std::vector<Token> tokensEntrada){
    std::cout << "Função: factor" << std::endl;
    return (primary(tokensEntrada) || factor(tokensEntrada));
}

bool primary(std::vector<Token> tokensEntrada){
    std::cout <<"Função: primary"<<std::endl;
    return (unsignedNumber(tokensEntrada) || variable(tokensEntrada) || functionDesignator(tokensEntrada) || 
    (match("(", tokensEntrada) && arithmeticExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool unsignedNumber(std::vector<Token> tokensEntrada){
    std::cout <<"Função: unsignedNumber"<<std::endl;
    return (decimalNumber(tokensEntrada) || exponentialPart(tokensEntrada) || (decimalNumber(tokensEntrada) && exponentialPart(tokensEntrada)));
}

bool decimalNumber(std::vector<Token> tokensEntrada){
    std::cout <<"Função: decimalNumber"<<std::endl;
    return (unsignedInteger(tokensEntrada));
}

bool unsignedInteger(std::vector<Token> tokensEntrada){
    std::cout << "Função: unsignedInteger" << std::endl;
    return (digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada));
}

bool auxUnsignedInteger(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxUnsignedInteger" << std::endl;
    return ((digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada)) || true);
}

bool exponentialPart(std::vector<Token> tokensEntrada){
    return (match("^", tokensEntrada) && integer(tokensEntrada));
}

bool integer(std::vector<Token> tokensEntrada){
    std::cout <<"Função: Integer"<<std::endl;
    return ((unsignedInteger(tokensEntrada)) || (match("+", tokensEntrada) && unsignedInteger(tokensEntrada)) || 
    (match("-", tokensEntrada) && unsignedInteger(tokensEntrada)));
}

bool booleanExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: booleanExpression" << std::endl;
    return (simpleBoolean(tokensEntrada) || (ifClause(tokensEntrada) && simpleBoolean(tokensEntrada)
    && match("else", tokensEntrada) && booleanExpression(tokensEntrada)));
}

bool simpleBoolean(std::vector<Token> tokensEntrada){
    return (implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada));
}

bool auxSimpleBoolean(std::vector<Token> tokensEntrada){
    return ((match("==", tokensEntrada) && implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada)) || true);
}

bool implication(std::vector<Token> tokensEntrada){
    return booleanTerm(tokensEntrada);
}

bool booleanTerm(std::vector<Token> tokensEntrada){
    return (booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada));
}

bool auxBooleanTerm(std::vector<Token> tokensEntrada){
    return ((match("||", tokensEntrada) && booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada)) || true);
}

bool booleanFactor(std::vector<Token> tokensEntrada){
    return (booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada));
}

bool auxBooleanFactor(std::vector<Token> tokensEntrada){
    return ((match("&&", tokensEntrada) && booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada)) || true);
}

bool booleanSecondary(std::vector<Token> tokensEntrada){
    return (booleanPrimary(tokensEntrada) || (match("!", tokensEntrada) && booleanPrimary(tokensEntrada) ));
}

bool booleanPrimary(std::vector<Token> tokensEntrada){
    return (logicalValue(tokensEntrada) || variable(tokensEntrada) || funcionDesignator(tokensEntrada) || relation(tokensEntrada) || (match("(", tokensEntrada) && booleanExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool functionDesignator(std::vector<Token> tokensEntrada){
    return (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada));
}

bool relation(std::vector<Token> tokensEntrada){
    std::cout << "Função: relation" << std::endl;
    return (simpleArithmeticExpression(tokensEntrada) && relationalOperator(tokensEntrada) && simpleArithmeticExpression(tokensEntrada));
}

bool funcionDesignator(std::vector<Token> tokensEntrada){
    return (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada));
}

bool variable(std::vector<Token> tokensEntrada){
    std::cout << "Função: variable" << std::endl;
    return (simpleVariable(tokensEntrada) || subscriptedVariable(tokensEntrada));
}

bool simpleVariable(std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleVariable" << std::endl;
    return variableIdenfier(tokensEntrada);
}

bool variableIdenfier(std::vector<Token> tokensEntrada){
    std::cout << "Função: variableIdentifier" << std::endl;
    return identifier(tokensEntrada);
}

bool subscriptedVariable(std::vector<Token> tokensEntrada){
    std::cout << "Função: subscriptedVariable" << std::endl;
    return (arrayIdentifier(tokensEntrada) && match("[", tokensEntrada) && subscriptList(tokensEntrada) && match("]", tokensEntrada));
}

bool subscriptList(std::vector<Token> tokensEntrada){
    return (subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada));
}

bool auxSubscriptList(std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada)) || true);
}

bool subscriptExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: subscriptExpression" << std::endl;
    return (arithmeticExpression(tokensEntrada));
}

bool identifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: identifier" << std::endl;
    return (letter(tokensEntrada) && auxIdentifier(tokensEntrada));
}

bool auxIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxIdentifier" << std::endl;
    return ((digit(tokensEntrada) && auxIdentifier(tokensEntrada)) || (letter(tokensEntrada) && auxIdentifier(tokensEntrada)) || true);
}

bool basicSymbol(std::vector<Token> tokensEntrada){
    return(letter(tokensEntrada) || digit(tokensEntrada) || logicalValue(tokensEntrada) || delimiter(tokensEntrada));
}

bool letter(std::vector<Token> tokensEntrada){
    std::cout << "Função: letter" << std::endl;
    return matchLetter(tokensEntrada);
}

bool digit(std::vector<Token> tokensEntrada){
    std::cout << "Função: digit" << std::endl;
    return matchDigit(tokensEntrada);
}

bool logicalValue(std::vector<Token> tokensEntrada){
    return (match("true", tokensEntrada) || match("false", tokensEntrada));
}

bool delimiter(std::vector<Token> tokensEntrada){
    return (Operator(tokensEntrada) || separator(tokensEntrada) || bracket(tokensEntrada) || declarator(tokensEntrada) || specificator(tokensEntrada));
}

bool Operator(std::vector<Token> tokensEntrada){
    return (arithmeticOperator(tokensEntrada) || relationalOperator(tokensEntrada) || logicalOperator(tokensEntrada) || sequentialOperator(tokensEntrada));
}

bool arithmeticOperator(std::vector<Token> tokensEntrada){
    return (match("+", tokensEntrada) && match("-", tokensEntrada) && match("*", tokensEntrada) && match("/", tokensEntrada));
}

bool relationalOperator(std::vector<Token> tokensEntrada){
    return (match("<", tokensEntrada) || match("<=", tokensEntrada) || match("=", tokensEntrada) || match("!=", tokensEntrada) || match(">", tokensEntrada) || match(">=", tokensEntrada)); 
}

bool logicalOperator(std::vector<Token> tokensEntrada){
    return (match("==", tokensEntrada) || match("||", tokensEntrada) || match("&&", tokensEntrada) || match("!", tokensEntrada));
}

bool sequentialOperator(std::vector<Token> tokensEntrada){
    return (match("goto", tokensEntrada) || match("if", tokensEntrada) || match("then", tokensEntrada) || match("else", tokensEntrada) || match("for", tokensEntrada) || match("do", tokensEntrada));
}

bool separator(std::vector<Token> tokensEntrada){
    std::cout << "Função separator" << std::endl;
    return (match(",", tokensEntrada) || match(":", tokensEntrada) || match(";", tokensEntrada) || match(":=", tokensEntrada) || match("_", tokensEntrada) || 
    match("step", tokensEntrada) || match("until", tokensEntrada) || match("while", tokensEntrada) || match("comment", tokensEntrada));
}

bool bracket(std::vector<Token> tokensEntrada){
    return (match("(", tokensEntrada) || match(")", tokensEntrada) || match("[", tokensEntrada) || 
    match("]", tokensEntrada) || match("begin", tokensEntrada) || match("end", tokensEntrada));
}

bool declarator(std::vector<Token> tokensEntrada){
    return (match("own", tokensEntrada) || match("integer", tokensEntrada) || match("array", tokensEntrada) || match("procedure", tokensEntrada));
}

bool specificator(std::vector<Token> tokensEntrada){
    std::cout << "Função: specificator" << std::endl;
    return (match("label", tokensEntrada) || match("value", tokensEntrada));
}