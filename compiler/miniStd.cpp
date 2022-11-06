#include <iostream>
#include "header.h"
#include "AnalisadorLexico.cpp"

int pos = 0;
TabelaPred tabelaAtual;
std::vector<Token> erros;

std::vector<Token> inicialState(std::vector<Token> tokensEntrada){
    //Começa percorrer a bnf
    program(pos, tokensEntrada);

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
        std::cout << "Char encontrado: " << character << std::endl;
        //std::cout << "Posição no vector: " << pos << std::endl;
        //addToTable(tokensEntrada.at(pos));
        pos++;
        return true;
    }
    else{
        erros.push_back(tokensEntrada.at(pos));
        return false;
    }
}

//VERIFICAR TODOS OS TERMINAIS DE LETRAS
bool matchLetter(std::vector<Token> tokensEntrada){
    char letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char character = tokensEntrada.at(pos).rotulo[0];

    if(ChecaValidos(letters, character, sizeof(letters)/ sizeof(letters[0]))){
        std::string conChar(1, character);
        match(conChar, tokensEntrada);
        return true;
    }
    else{
        std::cout << "Função erro MacthLetter" << std::endl;
        return false;
    }
}

//VERIFICAR TODOS OS TERMINAIS DE DIGITOS
bool matchDigit(std::vector<Token> tokensEntrada){
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char character = tokensEntrada.at(pos).rotulo[0];
    std::cout << "Digito: " << character << std::endl;

    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        std::string conChar(1, character);
        match(conChar, tokensEntrada);
        return true;
    }
    else{
        return false;
    }
}

// Função para adicionar símbolo na tabela de precedência
void addToTable(Token current){
// Funcionamento: Procurar o rotulo do token em uma das listas de escopo global ou local e adicionar seu valor inicial
}

bool program(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: program" << std::endl;
    return (block(pos, tokensEntrada) || compoundStatement(pos, tokensEntrada));
}

bool block(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: block" << std::endl;
    return (unlabelledBlock(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && block(pos, tokensEntrada)));
}

bool unlabelledBlock(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledBlock" << std::endl;
    return (blockHead(pos, tokensEntrada) && match(";", tokensEntrada) && compoundTail(pos, tokensEntrada));
}

bool blockHead(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: blockHead" << std::endl;
    return ((match("begin", tokensEntrada) && declaration(pos, tokensEntrada) && blockAux(pos, tokensEntrada)));
}

bool blockAux(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: blockAux" << std::endl;
    return ((match(";", tokensEntrada) && declaration(pos, tokensEntrada) && blockAux(pos, tokensEntrada)) || true);
}

bool compoundStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: compoundStatement" << std::endl;
    return (unlabelledCompound(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && compoundStatement(pos, tokensEntrada)));
}

bool unlabelledCompound(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledCompound" << std::endl;
    return (match("begin", tokensEntrada) && compoundTail(pos, tokensEntrada));
}

bool compoundTail(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: compoundTail" << std::endl;
    return ((statement(pos, tokensEntrada) && match("end", tokensEntrada))  || (statement(pos, tokensEntrada) && match(";", tokensEntrada) && compoundTail(pos, tokensEntrada)));
}

bool declaration(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: declaration" << std::endl;
    return(typedeclaration(pos, tokensEntrada) || arrayDeclaration(pos, tokensEntrada) || procedureDeclaration(pos, tokensEntrada));
}

bool typedeclaration(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: typeDeclaration" << std::endl;
    return(localOrOwnType(pos, tokensEntrada) && typeList(pos, tokensEntrada));
}

bool localOrOwnType(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: localOrOwnType" << std::endl;
    return (type(pos, tokensEntrada) || (match("own", tokensEntrada) && type(pos, tokensEntrada)));
}

bool type(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: type" << std::endl;
    return (match("integer", tokensEntrada));
}

bool typeList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: typeList" << std::endl;
    return (simpleVariable(pos, tokensEntrada) || (simpleVariable(pos, tokensEntrada) && (match(",", tokensEntrada) && typeList(pos, tokensEntrada))));
}

bool arrayDeclaration(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayDeclaration" << std::endl;
    return ((match("array", tokensEntrada) && arrayList(pos, tokensEntrada)) || (localOrOwnType(pos, tokensEntrada) && match("array", tokensEntrada) && arrayList(pos, tokensEntrada)));
}

bool arrayList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayList" << std::endl;
    return (arraySegment(pos, tokensEntrada) && auxArrayList(pos, tokensEntrada));
}

bool auxArrayList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxArrayList" << std::endl;
    return ((match(",", tokensEntrada) && arraySegment(pos, tokensEntrada) && auxArrayList(pos, tokensEntrada)) || true);
}

bool arraySegment(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: arraySegment" << std::endl;
    return ((arrayIdentifier(pos, tokensEntrada) && (match("[", tokensEntrada) && boundPairList(pos, tokensEntrada) && match("]", tokensEntrada))) || (arrayIdentifier(pos, tokensEntrada) && match(",", tokensEntrada) && arraySegment(pos, tokensEntrada))); 
}

bool arrayIdentifier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayIdentifier" << std::endl;
    return identifier(pos, tokensEntrada);
}

bool boundPairList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPairList" << std::endl;
    return (boundPair(pos, tokensEntrada) && auxBoundPairList(pos, tokensEntrada));
}

bool auxBoundPairList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxBoundPairList" << std::endl;
    return((match(",", tokensEntrada) && boundPair(pos, tokensEntrada) && auxBoundPairList(pos, tokensEntrada)) || true);
}

bool boundPair(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPair" << std::endl;
    return(lowerBound(pos, tokensEntrada) && match(":", tokensEntrada) && lowerBound(pos, tokensEntrada));
}

bool lowerBound(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: lowerBound" << std::endl;
    return arithmeticExpression(pos, tokensEntrada);
}

bool procedureDeclaration(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureDeclaration" << std::endl;
    return ((match("procedure", tokensEntrada) && procedureHeading(pos, tokensEntrada) && procedureBody(pos, tokensEntrada)) || (type(pos, tokensEntrada) && match("procedure", tokensEntrada) && procedureHeading(pos, tokensEntrada) && procedureBody(pos, tokensEntrada)));
}

bool procedureHeading(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureHeading" << std::endl;
    return (procedureIdentifier(pos, tokensEntrada) && formalParameterPart(pos, tokensEntrada) && match(";", tokensEntrada) && valuePart(pos, tokensEntrada) && specificationPart(pos, tokensEntrada));
}

bool procedureIdentifier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureIdentifier" << std::endl;
    return identifier(pos, tokensEntrada);
}

bool formalParameterPart(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterPart" << std::endl;
    return ((match("(", tokensEntrada) && formalParameterList(pos, tokensEntrada) && match(")", tokensEntrada)) || true);
}

bool formalParameterList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterList" << std::endl;
    return(formalParameter(pos, tokensEntrada) && auxFormalParameterList(pos, tokensEntrada));
}

bool auxFormalParameterList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxFormalParameterList" << std::endl;
    return ((parameterDelimiter(pos, tokensEntrada) && formalParameter(pos, tokensEntrada) && auxFormalParameterList(pos, tokensEntrada) || true));
}

bool formalParameter(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameter" << std::endl;
    return identifier(pos, tokensEntrada);
}

bool valuePart(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: valuePart" << std::endl;
    return ((match("value", tokensEntrada) && identifierList(pos, tokensEntrada) && match(";", tokensEntrada)) || true);
}

bool specificationPart(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: specificationPart" << std::endl;
    return (((specifier(pos, tokensEntrada) && identifierList(pos, tokensEntrada) && match(";", tokensEntrada) && auxSpecificationPart(pos, tokensEntrada))));
}

bool auxSpecificationPart(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxSpecificationPart" << std::endl;
    return ((specifier(pos, tokensEntrada) && identifierList(pos, tokensEntrada) && auxSpecificationPart(pos, tokensEntrada)) || true);
}

bool specifier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: specifier" << std::endl;
    return (type(pos, tokensEntrada) || match("array", tokensEntrada) || (type(pos, tokensEntrada) && match("array", tokensEntrada)) || match("label", tokensEntrada) || match("procedure", tokensEntrada) || (type(pos, tokensEntrada) && match("procedure", tokensEntrada)));
}

bool identifierList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: identifierList" << std::endl;
    return (identifier(pos, tokensEntrada) && auxIdentifierList(pos, tokensEntrada));
}

bool auxIdentifierList(int pos, std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && identifier(pos, tokensEntrada) && auxIdentifierList(pos, tokensEntrada)) || true);
}

bool procedureBody(int pos, std::vector<Token> tokensEntrada){
    return (statement(pos, tokensEntrada) || true); //tem um <code> aqui na bnf
}

bool statement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: statement" << std::endl;
    return (unconditionalStatement(pos, tokensEntrada) || conditionalStatement(pos, tokensEntrada) || forStatement(pos, tokensEntrada));
}

bool unconditionalStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função unconditionalStatement" << std::endl;
    return (basicStatement(pos, tokensEntrada) || compoundStatement(pos, tokensEntrada) || block(pos, tokensEntrada));
}

bool basicStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: basicStatement" << std::endl;
    return (unlabelledBasicStatement(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && basicStatement(pos, tokensEntrada)));
}

bool label(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: label" << std::endl;
    return (identifier(pos, tokensEntrada) || unsignedInteger(pos, tokensEntrada));
}

bool unlabelledBasicStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledBasicStatement" << std::endl;
    return (assignmentStatement(pos, tokensEntrada) || goToStatement(pos, tokensEntrada) || procedureStatement(pos, tokensEntrada));
}

bool assignmentStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: assignmentStatement" << std::endl;
    return ((leftPartList(pos, tokensEntrada) && arithmeticExpression(pos, tokensEntrada)) || (leftPartList(pos, tokensEntrada) && booleanExpression(pos, tokensEntrada)));
}

bool leftPartList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPartList" << std::endl;
    return (leftPart(pos, tokensEntrada) && auxLeftPartList(pos, tokensEntrada));
}

bool auxLeftPartList(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxLeftPartList" << std::endl;
    return ((leftPart(pos, tokensEntrada) && auxLeftPartList(pos, tokensEntrada)) || true);
}

bool leftPart(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPart" << std::endl;
    return ((variable(pos, tokensEntrada) && match(":=", tokensEntrada)) || (procedureIdentifier(pos, tokensEntrada) && match(":=", tokensEntrada)));
}

bool goToStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: goToStatement" << std::endl;
    return (match("goto", tokensEntrada) && designationalExpression(pos, tokensEntrada));
}

bool designationalExpression(int pos, std::vector<Token> tokensEntrada){
    return (simpleDesignationalExpression(pos, tokensEntrada) || (ifClause(pos, tokensEntrada) && simpleDesignationalExpression(pos, tokensEntrada) && match("else", tokensEntrada) && designationalExpression(pos, tokensEntrada) ) );
}

bool simpleDesignationalExpression(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleDesignationalExpression" << std::endl;
    return (label(pos, tokensEntrada) || (match("(", tokensEntrada) && designationalExpression(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool procedureStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureStatement" << std::endl;
    return ((procedureIdentifier(pos, tokensEntrada) && actualParameterPart(pos, tokensEntrada)));
}

bool actualParameterPart(int pos, std::vector<Token> tokensEntrada){
    return (true || (match("(", tokensEntrada) && actualParameterList(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool actualParameterList(int pos, std::vector<Token> tokensEntrada){
    return (actualParameter(pos, tokensEntrada) && auxActualParameterList(pos, tokensEntrada));
}

bool auxActualParameterList(int pos, std::vector<Token> tokensEntrada){
    return ((parameterDelimiter(pos, tokensEntrada) && actualParameter(pos, tokensEntrada) && auxActualParameterList(pos, tokensEntrada)) || true);
}

bool parameterDelimiter(int pos, std::vector<Token> tokensEntrada){
    return (match(",", tokensEntrada));
}

bool actualParameter(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: actualParameter" << std::endl;
    return (expression(pos, tokensEntrada) || arrayIdentifier(pos, tokensEntrada) || procedureIdentifier(pos, tokensEntrada));
}

bool conditionalStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: conditionalStatement" << std::endl;
    return ((ifStatement(pos, tokensEntrada)) || (ifStatement(pos, tokensEntrada) && match("else", tokensEntrada) && statement(pos, tokensEntrada)) || 
    (ifClause(pos, tokensEntrada) && forStatement(pos, tokensEntrada)) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && conditionalStatement(pos, tokensEntrada)));
}

bool ifStatement(int pos, std::vector<Token> tokensEntrada){
    return (ifClause(pos, tokensEntrada) && unconditionalStatement(pos, tokensEntrada));
}

bool ifClause(int pos, std::vector<Token> tokensEntrada){
    return ((match("if", tokensEntrada) && booleanExpression(pos, tokensEntrada) && match("then", tokensEntrada)));
}

bool forStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: forStatement" << std::endl;
    return ((forClause(pos, tokensEntrada) && statement(pos, tokensEntrada)) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && forStatement(pos, tokensEntrada)));
}

bool forClause(int pos, std::vector<Token> tokensEntrada){
    return (match("for", tokensEntrada) && variable(pos, tokensEntrada) && match(":=", tokensEntrada) && forList(pos, tokensEntrada) && match("do", tokensEntrada));
}

bool forList(int pos, std::vector<Token> tokensEntrada){
    return (forListElement(pos, tokensEntrada) && auxForList(pos, tokensEntrada));
}
bool auxForList(int pos, std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && forListElement(pos, tokensEntrada) && auxForList(pos, tokensEntrada)) || true);
}

bool forListElement(int pos, std::vector<Token> tokensEntrada){
    return ((arithmeticExpression(pos, tokensEntrada)) || (arithmeticExpression(pos, tokensEntrada) && match("step" , tokensEntrada) && arithmeticExpression(pos, tokensEntrada) && match("until", tokensEntrada) && 
    arithmeticExpression(pos, tokensEntrada)) || (arithmeticExpression(pos, tokensEntrada) && match("while" , tokensEntrada) && booleanExpression(pos, tokensEntrada)));
}

bool expression(int pos, std::vector<Token> tokensEntrada){
    return (arithmeticExpression(pos, tokensEntrada) || booleanExpression(pos, tokensEntrada) || designationalExpression(pos, tokensEntrada));
}

bool arithmeticExpression(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: arithmeticExpression" << std::endl;
    return (simpleArithmeticExpression(pos, tokensEntrada) || ((ifClause(pos, tokensEntrada) && simpleArithmeticExpression(pos, tokensEntrada) &&
    match("else", tokensEntrada) && arithmeticExpression(pos, tokensEntrada))));
}

bool simpleArithmeticExpression(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleArithmeticExpression" << std::endl;
    return ((term(pos, tokensEntrada) && auxSimpleArithmeticExpression(pos, tokensEntrada)) || (addingOperator(pos, tokensEntrada) && term(pos, tokensEntrada)
    && auxSimpleArithmeticExpression(pos, tokensEntrada)));
}

bool auxSimpleArithmeticExpression(int pos, std::vector<Token> tokensEntrada){
    return ((addingOperator(pos, tokensEntrada) && term(pos, tokensEntrada) && auxSimpleArithmeticExpression(pos, tokensEntrada)) || true);
}

bool addingOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("+", tokensEntrada) || match("-", tokensEntrada));
}

bool term(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: term" << std::endl;
    return (factor(pos, tokensEntrada) && auxTerm(pos, tokensEntrada));
}

bool auxTerm(int pos, std::vector<Token> tokensEntrada){
    return ((multiplyingOperator(pos, tokensEntrada) && factor(pos, tokensEntrada) && auxTerm(pos, tokensEntrada)) || true);
}

bool multiplyingOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("*", tokensEntrada));
}

bool factor(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: factor" << std::endl;
    return (primary(pos, tokensEntrada) || factor(pos, tokensEntrada));
}

bool primary(int pos, std::vector<Token> tokensEntrada){
    std::cout <<"Função: primary"<<std::endl;
    return (unsignedNumber(pos, tokensEntrada) || variable(pos, tokensEntrada) || functionDesignator(pos, tokensEntrada) || 
    (match("(", tokensEntrada) && arithmeticExpression(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool unsignedNumber(int pos, std::vector<Token> tokensEntrada){
    std::cout <<"Função: unsignedNumber"<<std::endl;
    return (decimalNumber(pos, tokensEntrada) || exponentialPart(pos, tokensEntrada) || (decimalNumber(pos, tokensEntrada) && exponentialPart(pos, tokensEntrada)));
}

bool decimalNumber(int pos, std::vector<Token> tokensEntrada){
    std::cout <<"Função: decimalNumber"<<std::endl;
    return (unsignedInteger(pos, tokensEntrada));
}

bool unsignedInteger(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: unsignedInteger" << std::endl;
    return (digit(pos, tokensEntrada) && auxUnsignedInteger(pos, tokensEntrada));
}

bool auxUnsignedInteger(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxUnsignedInteger" << std::endl;
    return ((digit(pos, tokensEntrada) && auxUnsignedInteger(pos, tokensEntrada)) || true);
}

bool exponentialPart(int pos, std::vector<Token> tokensEntrada){
    return (match("^", tokensEntrada) && integer(pos, tokensEntrada));
}

bool integer(int pos, std::vector<Token> tokensEntrada){
    std::cout <<"Função: Integer"<<std::endl;
    return ((unsignedInteger(pos, tokensEntrada)) || (match("+", tokensEntrada) && unsignedInteger(pos, tokensEntrada)) || 
    (match("-", tokensEntrada) && unsignedInteger(pos, tokensEntrada)));
}

bool booleanExpression(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: booleanExpression" << std::endl;
    return (simpleBoolean(pos, tokensEntrada) || (ifClause(pos, tokensEntrada) && simpleBoolean(pos, tokensEntrada)
    && match("else", tokensEntrada) && booleanExpression(pos, tokensEntrada)));
}

bool simpleBoolean(int pos, std::vector<Token> tokensEntrada){
    return (implication(pos, tokensEntrada) && auxSimpleBoolean(pos, tokensEntrada));
}

bool auxSimpleBoolean(int pos, std::vector<Token> tokensEntrada){
    return ((match("==", tokensEntrada) && implication(pos, tokensEntrada) && auxSimpleBoolean(pos, tokensEntrada)) || true);
}

bool implication(int pos, std::vector<Token> tokensEntrada){
    return booleanTerm(pos, tokensEntrada);
}

bool booleanTerm(int pos, std::vector<Token> tokensEntrada){
    return (booleanFactor(pos, tokensEntrada) && auxBooleanTerm(pos, tokensEntrada));
}

bool auxBooleanTerm(int pos, std::vector<Token> tokensEntrada){
    return ((match("||", tokensEntrada) && booleanFactor(pos, tokensEntrada) && auxBooleanTerm(pos, tokensEntrada)) || true);
}

bool booleanFactor(int pos, std::vector<Token> tokensEntrada){
    return (booleanSecondary(pos, tokensEntrada) && auxBooleanFactor(pos, tokensEntrada));
}

bool auxBooleanFactor(int pos, std::vector<Token> tokensEntrada){
    return ((match("&&", tokensEntrada) && booleanSecondary(pos, tokensEntrada) && auxBooleanFactor(pos, tokensEntrada)) || true);
}

bool booleanSecondary(int pos, std::vector<Token> tokensEntrada){
    return (booleanPrimary(pos, tokensEntrada) || (match("!", tokensEntrada) && booleanPrimary(pos, tokensEntrada) ));
}

bool booleanPrimary(int pos, std::vector<Token> tokensEntrada){
    return (logicalValue(pos, tokensEntrada) || variable(pos, tokensEntrada) || funcionDesignator(pos, tokensEntrada) || relation(pos, tokensEntrada) || (match("(", tokensEntrada) && booleanExpression(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool functionDesignator(int pos, std::vector<Token> tokensEntrada){
    return (procedureIdentifier(pos, tokensEntrada) && actualParameterPart(pos, tokensEntrada));
}

bool relation(int pos, std::vector<Token> tokensEntrada){
    return (simpleArithmeticExpression(pos, tokensEntrada) && relationalOperator(pos, tokensEntrada) && simpleArithmeticExpression(pos, tokensEntrada));
}

bool funcionDesignator(int pos, std::vector<Token> tokensEntrada){
    return (procedureIdentifier(pos, tokensEntrada) && actualParameterPart(pos, tokensEntrada));
}

bool variable(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: variable" << std::endl;
    return (simpleVariable(pos, tokensEntrada) || subscriptedVariable(pos, tokensEntrada));
}

bool simpleVariable(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleVariable" << std::endl;
    return variableIdenfier(pos, tokensEntrada);
}

bool variableIdenfier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: variableIdentifier" << std::endl;
    return identifier(pos, tokensEntrada);
}

bool subscriptedVariable(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: subscriptedVariable" << std::endl;
    return (arrayIdentifier(pos, tokensEntrada) && match("[", tokensEntrada) && subscriptList(pos, tokensEntrada) && match("]", tokensEntrada));
}

bool subscriptList(int pos, std::vector<Token> tokensEntrada){
    return (subscriptExpression(pos, tokensEntrada) && auxSubscriptList(pos, tokensEntrada));
}

bool auxSubscriptList(int pos, std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && subscriptExpression(pos, tokensEntrada) && auxSubscriptList(pos, tokensEntrada)) || true);
}

bool subscriptExpression(int pos, std::vector<Token> tokensEntrada){
    return (arithmeticExpression(pos, tokensEntrada));
}

bool identifier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: identifier" << std::endl;
    return (letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada));
}

bool auxIdentifier(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: auxIdentifier" << std::endl;
    return ((letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || (digit(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || true);
}

bool basicSymbol(int pos, std::vector<Token> tokensEntrada){
    return(letter(pos, tokensEntrada) || digit(pos, tokensEntrada) || logicalValue(pos, tokensEntrada) || delimiter(pos, tokensEntrada));
}

bool letter(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: letter" << std::endl;
    return matchLetter(tokensEntrada);
}

bool digit(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: digit" << std::endl;
    return matchDigit(tokensEntrada);
}

bool logicalValue(int pos, std::vector<Token> tokensEntrada){
    return (match("true", tokensEntrada) || match("false", tokensEntrada));
}

bool delimiter(int pos, std::vector<Token> tokensEntrada){
    return (Operator(pos, tokensEntrada) || separator(pos, tokensEntrada) || bracket(pos, tokensEntrada) || declarator(pos, tokensEntrada) || specificator(pos, tokensEntrada));
}

bool Operator(int pos, std::vector<Token> tokensEntrada){
    return (arithmeticOperator(pos, tokensEntrada) || relationalOperator(pos, tokensEntrada) || logicalOperator(pos, tokensEntrada) || sequentialOperator(pos, tokensEntrada));
}

bool arithmeticOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("+", tokensEntrada) && match("-", tokensEntrada) && match("*", tokensEntrada) && match("/", tokensEntrada));
}

bool relationalOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("<", tokensEntrada) || match("<=", tokensEntrada) || match("=", tokensEntrada) || match("!=", tokensEntrada) || match(">", tokensEntrada) || match(">=", tokensEntrada)); 
}

bool logicalOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("==", tokensEntrada) || match("||", tokensEntrada) || match("&&", tokensEntrada) || match("!", tokensEntrada));
}

bool sequentialOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("goto", tokensEntrada) || match("if", tokensEntrada) || match("then", tokensEntrada) || match("else", tokensEntrada) || match("for", tokensEntrada) || match("do", tokensEntrada));
}

bool separator(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função separator" << std::endl;
    return (match(",", tokensEntrada) || match(":", tokensEntrada) || match(";", tokensEntrada) || match(":=", tokensEntrada) || match("_", tokensEntrada) || 
    match("step", tokensEntrada) || match("until", tokensEntrada) || match("while", tokensEntrada) || match("comment", tokensEntrada));
}

bool bracket(int pos, std::vector<Token> tokensEntrada){
    return (match("(", tokensEntrada) || match(")", tokensEntrada) || match("[", tokensEntrada) || 
    match("]", tokensEntrada) || match("begin", tokensEntrada) || match("end", tokensEntrada));
}

bool declarator(int pos, std::vector<Token> tokensEntrada){
    return (match("own", tokensEntrada) || match("integer", tokensEntrada) || match("array", tokensEntrada) || match("procedure", tokensEntrada));
}

bool specificator(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Função: specificator" << std::endl;
    return (match("label", tokensEntrada) || match("value", tokensEntrada));
}