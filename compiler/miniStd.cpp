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
        std::cout << "Posição no vector: " << pos << std::endl;
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
        std::cout << "Char atual: " << character << std::endl;
        //addToTable(tokensEntrada.at(pos));
        pos = pos + 1;
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
        erros.push_back(tokensEntrada.at(pos));
        return false;
    }
}

//VERIFICAR TODOS OS TERMINAIS DE LETRAS
bool matchDigit(std::vector<Token> tokensEntrada){
    char digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char character = tokensEntrada.at(pos).rotulo[0];

    if(ChecaValidos(digits, character, sizeof(digits)/ sizeof(digits[0]))){
        std::string conChar(1, character);
        match(conChar, tokensEntrada);
        return true;
    }
    else{
        erros.push_back(tokensEntrada.at(pos));
        return false;
    }
}

// Função para adicionar símbolo na tabela de precedência
void addToTable(Token current){
// Funcionamento: Procurar o rotulo do token em uma das listas de escopo global ou local e adicionar seu valor inicial
}

bool program(int pos, std::vector<Token> tokensEntrada){
    return (block(pos, tokensEntrada) || compoundStatement(pos, tokensEntrada));
}

bool block(int pos, std::vector<Token> tokensEntrada){
    return (unlabelledBlock(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && block(pos, tokensEntrada)));
}

bool unlabelledBlock(int pos, std::vector<Token> tokensEntrada){
    return (blockHead(pos, tokensEntrada) && match(";", tokensEntrada) && compoundTail(pos, tokensEntrada));
}

bool blockHead(int pos, std::vector<Token> tokensEntrada){
    return ((match("begin", tokensEntrada) && declaration(pos, tokensEntrada)) || (blockAux(pos, tokensEntrada) && match(";", tokensEntrada)));
}

bool blockAux(int pos, std::vector<Token> tokensEntrada){
    return (declaration(pos, tokensEntrada) && blockAux(pos, tokensEntrada) || true);
}

bool compoundStatement(int pos, std::vector<Token> tokensEntrada){
    return (unlabelledCompound(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && compoundStatement(pos, tokensEntrada)));
}

bool unlabelledCompound(int pos, std::vector<Token> tokensEntrada){
    return (match("begin", tokensEntrada) && compoundTail(pos, tokensEntrada));
}

bool compoundTail(int pos, std::vector<Token> tokensEntrada){
    return (statement(pos, tokensEntrada) && (match("end", tokensEntrada) || (match(";", tokensEntrada) && compoundTail(pos, tokensEntrada))));
}

bool declaration(int pos, std::vector<Token> tokensEntrada){
   return(typedeclaration(pos, tokensEntrada) || arrayDeclaration(pos, tokensEntrada) || procedureDeclaration(pos, tokensEntrada)); 
}

bool typedeclaration(int pos, std::vector<Token> tokensEntrada){
    return(localOrOwnType(pos, tokensEntrada) && typeList(pos, tokensEntrada));
}

bool localOrOwnType(int pos, std::vector<Token> tokensEntrada){
    return (type(pos, tokensEntrada) || (match("own", tokensEntrada) && type(pos, tokensEntrada)));
}

bool type(int pos, std::vector<Token> tokensEntrada){
    return match("integer", tokensEntrada);
}

bool typeList(int pos, std::vector<Token> tokensEntrada){
    return (simpleVariable (pos, tokensEntrada) && (match(",", tokensEntrada) || typeList(pos, tokensEntrada)));
}

bool arrayDeclaration(int pos, std::vector<Token> tokensEntrada){
    return ((match("array", tokensEntrada) && arrayList(pos, tokensEntrada)) || (localOrOwnType(pos, tokensEntrada) && match("array", tokensEntrada) && arrayList(pos, tokensEntrada)));
}

bool arrayList(int pos, std::vector<Token> tokensEntrada){
    return (arraySegment(pos, tokensEntrada) && auxArrayList(pos, tokensEntrada));
}

bool auxArrayList(int pos, std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && arraySegment(pos, tokensEntrada) && auxArrayList(pos, tokensEntrada)) || true);
}

bool arraySegment(int pos, std::vector<Token> tokensEntrada){
    return (arrayIdentifier(pos, tokensEntrada) && ((match("[", tokensEntrada) && boundPairList(pos, tokensEntrada) && match("]", tokensEntrada)) || (match(",", tokensEntrada) && arraySegment(pos, tokensEntrada)))); 
}

bool arrayIdentifier(int pos, std::vector<Token> tokensEntrada){
    return identifier(pos, tokensEntrada);
}

bool boundPairList(int pos, std::vector<Token> tokensEntrada){
    return (boundPair(pos, tokensEntrada) && auxBoundPairList(pos, tokensEntrada));
}

bool auxBoundPairList(int pos, std::vector<Token> tokensEntrada){
    return((match(",", tokensEntrada) && boundPair(pos, tokensEntrada) && auxBoundPairList(pos, tokensEntrada)) || true);
}

bool boundPair(int pos, std::vector<Token> tokensEntrada){
    return(lowerBound(pos, tokensEntrada) && match(":", tokensEntrada) && lowerBound(pos, tokensEntrada));
}

bool lowerBound(int pos, std::vector<Token> tokensEntrada){
    return arithmeticExpression(pos, tokensEntrada);
}

bool procedureDeclaration(int pos, std::vector<Token> tokensEntrada){
    return ((match("procedure", tokensEntrada) && procedureHeading(pos, tokensEntrada) && procedureBody(pos, tokensEntrada)) || (type(pos, tokensEntrada) && match("procedure", tokensEntrada) && procedureHeading(pos, tokensEntrada) && procedureBody(pos, tokensEntrada)));
}

bool procedureHeading(int pos, std::vector<Token> tokensEntrada){
    return (procedureIdentifier(pos, tokensEntrada) && formalParameterPart(pos, tokensEntrada) && match(";", tokensEntrada) && valuePart(pos, tokensEntrada) && specificationPart(pos, tokensEntrada));
}

bool procedureIdentifier(int pos, std::vector<Token> tokensEntrada){
    return identifier(pos, tokensEntrada);
}

bool formalParameterPart(int pos, std::vector<Token> tokensEntrada){
    return ((match("(", tokensEntrada) && formalParameterList(pos, tokensEntrada) && match(")", tokensEntrada)) || true);
}

bool formalParameterList(int pos, std::vector<Token> tokensEntrada){
    return(formalParameter(pos, tokensEntrada) && auxFormalParameterList(pos, tokensEntrada));
}

bool auxFormalParameterList(int pos, std::vector<Token> tokensEntrada){
    return ((parameterDelimiter(pos, tokensEntrada) && formalParameter(pos, tokensEntrada) && auxFormalParameterList(pos, tokensEntrada) || true));
}

bool formalParameter(int pos, std::vector<Token> tokensEntrada){
    return identifier(pos, tokensEntrada);
}

bool valuePart(int pos, std::vector<Token> tokensEntrada){
    return ((match("value", tokensEntrada) && identifierList(pos, tokensEntrada) && match(";", tokensEntrada)) || true);
}

bool specificationPart(int pos, std::vector<Token> tokensEntrada){
    return ((auxSpecificationPart(pos, tokensEntrada) || (specifier(pos, tokensEntrada) && identifierList(pos, tokensEntrada) && match(";", tokensEntrada) && auxSpecificationPart(pos, tokensEntrada))));
}

bool auxSpecificationPart(int pos, std::vector<Token> tokensEntrada){
    return ((specifier(pos, tokensEntrada) && identifierList(pos, tokensEntrada) && auxSpecificationPart(pos, tokensEntrada)) || true);
}

bool specifier(int pos, std::vector<Token> tokensEntrada){
    return (type(pos, tokensEntrada) || match("array", tokensEntrada) || (type(pos, tokensEntrada) && match("array", tokensEntrada)) || match("label", tokensEntrada) || match("procedure", tokensEntrada) || (type(pos, tokensEntrada) && match("procedure", tokensEntrada)));
}

bool identifierList(int pos, std::vector<Token> tokensEntrada){
    return (identifier(pos, tokensEntrada) && auxIdentifierList(pos, tokensEntrada));
}

bool auxIdentifierList(int pos, std::vector<Token> tokensEntrada){
    return ((match(",", tokensEntrada) && identifier(pos, tokensEntrada) && auxIdentifierList(pos, tokensEntrada)) || true);
}

bool procedureBody(int pos, std::vector<Token> tokensEntrada){
    return (statement(pos, tokensEntrada) || true); //tem um <code> aqui na bnf
}

bool statement(int pos, std::vector<Token> tokensEntrada){
    return (unconditionalStatement(pos, tokensEntrada) || conditionalStatement(pos, tokensEntrada) || forStatement(pos, tokensEntrada));
}

bool unconditionalStatement(int pos, std::vector<Token> tokensEntrada){
    return (basicStatement(pos, tokensEntrada) || compoundStatement(pos, tokensEntrada) || block(pos, tokensEntrada));
}

bool basicStatement(int pos, std::vector<Token> tokensEntrada){
    return (unlabelledBasicStatement(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && basicStatement(pos, tokensEntrada)));
}

bool label(int pos, std::vector<Token> tokensEntrada){
    return (identifier(pos, tokensEntrada) || unsignedInteger(pos, tokensEntrada));
}

bool unlabelledBasicStatement(int pos, std::vector<Token> tokensEntrada){
    return (assignmentStatement(pos, tokensEntrada) || goToStatement(pos, tokensEntrada) || procedureStatement(pos, tokensEntrada));
}

bool assignmentStatement(int pos, std::vector<Token> tokensEntrada){
    return ((leftPartList(pos, tokensEntrada) && arithmeticExpression(pos, tokensEntrada)) || (leftPartList(pos, tokensEntrada) && booleanExpression(pos, tokensEntrada)));
}

bool leftPartList(int pos, std::vector<Token> tokensEntrada){
    return (leftPart(pos, tokensEntrada) && auxLeftPartList(pos, tokensEntrada));
}

bool auxLeftPartList(int pos, std::vector<Token> tokensEntrada){
    return ((leftPart(pos, tokensEntrada) && auxLeftPartList(pos, tokensEntrada)) || true);
}

bool leftPart(int pos, std::vector<Token> tokensEntrada){
    return ((variable(pos, tokensEntrada) && match(":=", tokensEntrada)) || (procedureIdentifier(pos, tokensEntrada) && match(":=", tokensEntrada)));
}

bool goToStatement(int pos, std::vector<Token> tokensEntrada){
    return (match("goto", tokensEntrada) && designationalExpression(pos, tokensEntrada));
}

bool designationalExpression(int pos, std::vector<Token> tokensEntrada){
    return (simpleDesignationalExpression(pos, tokensEntrada) || (ifClause(pos, tokensEntrada) && simpleDesignationalExpression(pos, tokensEntrada) && match("else", tokensEntrada) && designationalExpression(pos, tokensEntrada) ) );
}

bool simpleDesignationalExpression(int pos, std::vector<Token> tokensEntrada){
    return (label(pos, tokensEntrada) || (match("(", tokensEntrada) && designationalExpression(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool procedureStatement(int pos, std::vector<Token> tokensEntrada){
    return ((procedureIdentifier(pos, tokensEntrada) && actualParameterPart(pos, tokensEntrada)));
}

bool actualParameterPart(int pos, std::vector<Token> tokensEntrada){
    return (true || (match("(", tokensEntrada) && actualParameterList(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool actualParameterList(int pos, std::vector<Token> tokensEntrada){
    return (actualParameter(pos, tokensEntrada), auxActualParameterList(pos, tokensEntrada));
}

bool auxActualParameterList(int pos, std::vector<Token> tokensEntrada){
    return ((parameterDelimiter(pos, tokensEntrada) && actualParameter(pos, tokensEntrada) && auxActualParameterList(pos, tokensEntrada)) || true);
}

bool parameterDelimiter(int pos, std::vector<Token> tokensEntrada){
    return (match(",", tokensEntrada));
}

bool actualParameter(int pos, std::vector<Token> tokensEntrada){
    return (expression(pos, tokensEntrada) || arrayIdentifier(pos, tokensEntrada) || procedureIdentifier(pos, tokensEntrada));
}

bool conditionalStatement(int pos, std::vector<Token> tokensEntrada){
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
    return (arithmeticExpression(pos, tokensEntrada) && ((match("step" , tokensEntrada) && arithmeticExpression(pos, tokensEntrada) && match("until", tokensEntrada) && 
    arithmeticExpression(pos, tokensEntrada)) || (match("while" , tokensEntrada) && booleanExpression(pos, tokensEntrada))));
}

bool expression(int pos, std::vector<Token> tokensEntrada){
    return (arithmeticExpression(pos, tokensEntrada) || booleanExpression(pos, tokensEntrada) || designationalExpression(pos, tokensEntrada));
}

bool arithmeticExpression(int pos, std::vector<Token> tokensEntrada){
    return (simpleArithmeticExpression(pos, tokensEntrada) || ((ifClause(pos, tokensEntrada) && simpleArithmeticExpression(pos, tokensEntrada) &&
    match("else", tokensEntrada) && arithmeticExpression(pos, tokensEntrada))));
}

bool simpleArithmeticExpression(int pos, std::vector<Token> tokensEntrada){
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
    return (factor(pos, tokensEntrada) && auxTerm(pos, tokensEntrada));
}

bool auxTerm(int pos, std::vector<Token> tokensEntrada){
    return ((multiplyingOperator(pos, tokensEntrada) && factor(pos, tokensEntrada) && auxTerm(pos, tokensEntrada)) || true);
}

bool multiplyingOperator(int pos, std::vector<Token> tokensEntrada){
    return (match("*", tokensEntrada));
}

bool factor(int pos, std::vector<Token> tokensEntrada){
    return (primary(pos, tokensEntrada) || factor(pos, tokensEntrada));
}

bool primary(int pos, std::vector<Token> tokensEntrada){
    return (variable(pos, tokensEntrada) || functionDesignator(pos, tokensEntrada) || 
    (match("(", tokensEntrada) && arithmeticExpression(pos, tokensEntrada) && match(")", tokensEntrada)));
}

bool unsignedInteger(int pos, std::vector<Token> tokensEntrada){
    return (digit(pos, tokensEntrada) && auxUnsignedInteger(pos, tokensEntrada));
}

bool auxUnsignedInteger(int pos, std::vector<Token> tokensEntrada){
    return ((digit(pos, tokensEntrada) && auxUnsignedInteger(pos, tokensEntrada)) || true);
}

bool exponentialPart(int pos, std::vector<Token> tokensEntrada){
    return (match("^", tokensEntrada) && integer(pos, tokensEntrada));
}

bool integer(int pos, std::vector<Token> tokensEntrada){
    return ((unsignedInteger(pos, tokensEntrada)) || (match("+", tokensEntrada) && unsignedInteger(pos, tokensEntrada)) || 
    (match("-", tokensEntrada) && unsignedInteger(pos, tokensEntrada)));
}

bool booleanExpression(int pos, std::vector<Token> tokensEntrada){
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
    return (logicalValue(pos, tokensEntrada) || variable(pos, tokensEntrada) || funcionDesignator(pos, tokensEntrada) || relation(pos, tokensEntrada) || (match("(", tokensEntrada) && booleanExpression(pos, tokensEntrada) && match(")", tokensEntrada) ));
}

bool functionDesignator(int pos, std::vector<Token> tokensEntrada){
    return (procedureIdentifier(pos, tokensEntrada) && actualParameterPart(pos, tokensEntrada));
}

bool relation(int pos, std::vector<Token> tokensEntrada){
    return (simpleArithmeticExpression(pos, tokensEntrada) && relationalOperator(pos, tokensEntrada) && simpleArithmeticExpression(pos, tokensEntrada));
}

bool funcionDesignator(int pos, std::vector<Token> tokensEntrada){
    return (procedureIdentifier(pos, tokensEntrada)&&actualParameterPart(pos, tokensEntrada));
}

bool variable(int pos, std::vector<Token> tokensEntrada){
    return (simpleVariable(pos, tokensEntrada) || subscriptedVariable(pos, tokensEntrada));
}

bool simpleVariable(int pos, std::vector<Token> tokensEntrada){
    return variableIdenfier(pos, tokensEntrada);
}

bool variableIdenfier(int pos, std::vector<Token> tokensEntrada){
    return identifier(pos, tokensEntrada);
}

bool subscriptedVariable(int pos, std::vector<Token> tokensEntrada){
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
    return (letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada));
}

bool auxIdentifier(int pos, std::vector<Token> tokensEntrada){
    return ((letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || (digit(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || true);
}

bool basicSymbol(int pos, std::vector<Token> tokensEntrada){
    return(letter(pos, tokensEntrada) || digit(pos, tokensEntrada) || logicalValue(pos, tokensEntrada) || delimiter(pos, tokensEntrada));
}

bool letter(int pos, std::vector<Token> tokensEntrada){
    return matchLetter(tokensEntrada);
}

bool digit(int pos, std::vector<Token> tokensEntrada){
    return matchDigit(tokensEntrada);
}

bool variableIdentifier(int pos, std::vector<Token> tokensEntrada){
     return (identifier(pos, tokensEntrada));
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
    return (match("goto", tokensEntrada) || match("if", tokensEntrada) || match("then", tokensEntrada));
}

bool separator(int pos, std::vector<Token> tokensEntrada){
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
    return (match("label", tokensEntrada) || match("value", tokensEntrada));
}