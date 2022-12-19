#include <iostream>
#include "header.h"
#include "AnalisadorLexico.cpp"

int pos = 0;
TabelaPred tabelaAtual;
std::vector<Token> erros;

std::vector<Token> inicialState(std::vector<Token> tokensEntrada){
    //Começa percorrer a bnf
    block(tokensEntrada);

    if(pos == tokensEntrada.size() - 1){
        if(!erros.empty()){
            std::cout << "Foram encontrados os seguintes erros:" << std::endl;
            for (auto i: erros)
            {
                std::cout << i.tipo << " - " << i.rotulo << std::endl;
            }
        }  
        if(tokensEntrada.at(pos).rotulo == "$"){
            std::cout << "deu ok" << std::endl;
            return tokensEntrada;
        }
    }
    else{
        if(tokensEntrada.at(pos).rotulo == "$"){
            std::cout << "deu ok" << std::endl;
            return tokensEntrada;
        }
        std::cout << "Erro na análise sintática" << std::endl;
        std::cout << "POSIÇÃO ATUAL DO POS: " << pos << std::endl;
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

bool program(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: program" << std::endl;
    int auxPos = pos;
    
    //return (block(tokensEntrada) || compoundStatement(tokensEntrada));
    if (not block(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not compoundStatement(tokensEntrada)){
        pos = auxPos;
        return false;
    }

    return true;
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

bool unlabelledBlock(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: unlabelledBlock" << std::endl;
    int auxPos = pos;
    
    if (not (blockHead(tokensEntrada) && match(";", tokensEntrada) && compoundTail(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    //return (blockHead(tokensEntrada) && match(";", tokensEntrada) && compoundTail(tokensEntrada));
    return true;
}

bool blockHead(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: blockHead" << std::endl;
    int auxPost = pos;  
    //return ((match("begin", tokensEntrada) && declaration(tokensEntrada) && blockAux(tokensEntrada)));
    if (not (match("begin", tokensEntrada) && declaration(tokensEntrada) && blockAux(tokensEntrada))){
        pos = auxPost;
        return false;
    }
    return true;
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

bool unlabelledCompound(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: unlabelledCompound" << std::endl;
    int auxPos = pos;

    //return (match("begin", tokensEntrada) && compoundTail(tokensEntrada));
    if(not (match("begin", tokensEntrada) && compoundTail(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;
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
    int auxPos = pos;
    if (not typedeclaration(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not arrayDeclaration(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not procedureDeclaration(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    return true;
}

bool typedeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: typeDeclaration" << std::endl;
    int auxPos = pos;
    //return(localOrOwnType(tokensEntrada) && typeList(tokensEntrada));
    if(not (localOrOwnType(tokensEntrada) && typeList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;    
}

bool localOrOwnType(std::vector<Token> tokensEntrada){
    std::cout << "Função: localOrOwnType" << std::endl;
    int auxPos = pos;
    //return (type(tokensEntrada) || (match("own", tokensEntrada) && type(tokensEntrada)));
    if(not type(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not (match("own", tokensEntrada) && type(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
}

bool type(std::vector<Token> tokensEntrada){
    std::cout << "Função: type" << std::endl;
    int auxPos = pos;
    
    //return (match("integer", tokensEntrada));
    if(not (match("integer", tokensEntrada))){
        pos = auxPos;
        return false;   
    }
    return true;
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
// nhank
bool arrayDeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayDeclaration" << std::endl;
    int auxPos = pos;
    if (not (match("array", tokensEntrada) && arrayList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (localOrOwnType(tokensEntrada) && match("array", tokensEntrada) && arrayList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match("array", tokensEntrada) && arrayList(tokensEntrada)) || (localOrOwnType(tokensEntrada) && match("array", tokensEntrada) && arrayList(tokensEntrada)));
}

bool arrayList(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayList" << std::endl;
    int auxPos = pos;
    //return (arraySegment(tokensEntrada) && auxArrayList(tokensEntrada));
    if(not (arraySegment(tokensEntrada) && auxArrayList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
}

bool auxArrayList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxArrayList" << std::endl;
    int auxPos = pos;
    if(not (match(",", tokensEntrada) && arraySegment(tokensEntrada) && auxArrayList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match(",", tokensEntrada) && arraySegment(tokensEntrada) && auxArrayList(tokensEntrada)) || true);
}

bool arraySegment(std::vector<Token> tokensEntrada){
    std::cout << "Função: arraySegment" << std::endl;
    int auxPos = pos;
    if(not (arrayIdentifier(tokensEntrada) && (match("[", tokensEntrada) && boundPairList(tokensEntrada) && match("]", tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    if (not (arrayIdentifier(tokensEntrada) && match(",", tokensEntrada) && arraySegment(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((arrayIdentifier(tokensEntrada) && (match("[", tokensEntrada) && boundPairList(tokensEntrada) && match("]", tokensEntrada))) || (arrayIdentifier(tokensEntrada) && match(",", tokensEntrada) && arraySegment(tokensEntrada))); 
}

bool arrayIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: arrayIdentifier" << std::endl;
    int auxPos = pos;
    if (not (identifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return identifier(tokensEntrada);
}

bool boundPairList(std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPairList" << std::endl;
    int auxPos = pos;
    if (not (boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada));
}

bool auxBoundPairList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxBoundPairList" << std::endl;
    int auxPos = pos;
    if (not (match(",", tokensEntrada) && boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return((match(",", tokensEntrada) && boundPair(tokensEntrada) && auxBoundPairList(tokensEntrada)) || true);
}

bool boundPair(std::vector<Token> tokensEntrada){
    std::cout << "Função: boundPair" << std::endl;
    int auxPos = pos;
    if (not (lowerBound(tokensEntrada) && match(":", tokensEntrada) && lowerBound(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return(lowerBound(tokensEntrada) && match(":", tokensEntrada) && lowerBound(tokensEntrada));
}

bool lowerBound(std::vector<Token> tokensEntrada){
    std::cout << "Função: lowerBound" << std::endl;
    int auxPos = pos;
    if (not (arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return arithmeticExpression(tokensEntrada);
}

bool procedureDeclaration(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureDeclaration" << std::endl;
    int auxPos = pos;
    if (not (match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (type(tokensEntrada) && match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada)) || (type(tokensEntrada) && match("procedure", tokensEntrada) && procedureHeading(tokensEntrada) && procedureBody(tokensEntrada)));
}

bool procedureHeading(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureHeading" << std::endl;
    int auxPos = pos;
    if (not (procedureIdentifier(tokensEntrada) && formalParameterPart(tokensEntrada) && match(";", tokensEntrada) && valuePart(tokensEntrada) && specificationPart(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (procedureIdentifier(tokensEntrada) && formalParameterPart(tokensEntrada) && match(";", tokensEntrada) && valuePart(tokensEntrada) && specificationPart(tokensEntrada));
}

bool procedureIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureIdentifier" << std::endl;
    int auxPos = pos;
    if (not (identifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return identifier(tokensEntrada);
}

bool formalParameterPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterPart" << std::endl;
    int auxPos = pos;
    if (not ((match("(", tokensEntrada) && formalParameterList(tokensEntrada) && match(")", tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match("(", tokensEntrada) && formalParameterList(tokensEntrada) && match(")", tokensEntrada)) || true);
}

bool formalParameterList(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameterList" << std::endl;
    int auxPos = pos;
    if (not (formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return(formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada));
}

bool auxFormalParameterList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxFormalParameterList" << std::endl;
    int auxPos = pos;
    if (not ((parameterDelimiter(tokensEntrada) && formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((parameterDelimiter(tokensEntrada) && formalParameter(tokensEntrada) && auxFormalParameterList(tokensEntrada) || true));
}

bool formalParameter(std::vector<Token> tokensEntrada){
    std::cout << "Função: formalParameter" << std::endl;
    int auxPos = pos;
    if (not (identifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return identifier(tokensEntrada);
}

bool valuePart(std::vector<Token> tokensEntrada){
    std::cout << "Função: valuePart" << std::endl;
    int auxPos = pos;
    if (not (match("value", tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match("value", tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada)) || true);
}

bool specificationPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: specificationPart" << std::endl;
    int auxPos = pos;
    if (not ((specifier(tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada) && auxSpecificationPart(tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (((specifier(tokensEntrada) && identifierList(tokensEntrada) && match(";", tokensEntrada) && auxSpecificationPart(tokensEntrada))) || true);
}

bool auxSpecificationPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxSpecificationPart" << std::endl;
    int auxPos = pos;
    if (not ((specifier(tokensEntrada) && identifierList(tokensEntrada) && auxSpecificationPart(tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((specifier(tokensEntrada) && identifierList(tokensEntrada) && auxSpecificationPart(tokensEntrada)) || true);
}

bool specifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: specifier" << std::endl;
    int auxPos = pos;
    if (not (type(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("array", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("array", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (type(tokensEntrada) && match("array", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("label", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("procedure", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (type(tokensEntrada) && match("procedure", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (type(tokensEntrada) || match("array", tokensEntrada) || (type(tokensEntrada) && match("array", tokensEntrada)) || match("label", tokensEntrada) || match("procedure", tokensEntrada) || (type(tokensEntrada) && match("procedure", tokensEntrada)));
}

bool identifierList(std::vector<Token> tokensEntrada){
    std::cout << "Função: identifierList" << std::endl;
    int auxPos = pos;
    if (not (identifier(tokensEntrada) && auxIdentifierList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (identifier(tokensEntrada) && auxIdentifierList(tokensEntrada));
}

bool auxIdentifierList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (match(",", tokensEntrada) && identifier(tokensEntrada) && auxIdentifierList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((match(",", tokensEntrada) && identifier(tokensEntrada) && auxIdentifierList(tokensEntrada)) || true);
}

bool procedureBody(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (statement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (statement(tokensEntrada) || true); //tem um <code> aqui na bnf
}

bool statement(std::vector<Token> tokensEntrada){
    std::cout << "Função: statement" << std::endl;
    int auxPos = pos;
    if (not (unconditionalStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (conditionalStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (forStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (unconditionalStatement(tokensEntrada) || conditionalStatement(tokensEntrada) || forStatement(tokensEntrada));
}

bool unconditionalStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função unconditionalStatement" << std::endl;
    int auxPos = pos;
    if (not (basicStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (compoundStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (block(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (basicStatement(tokensEntrada) || compoundStatement(tokensEntrada) || block(tokensEntrada));
}

bool basicStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: basicStatement" << std::endl;
    int auxPos = pos;
    if (not (unlabelledBasicStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (label(tokensEntrada) && match(":", tokensEntrada) && basicStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (unlabelledBasicStatement(tokensEntrada) || (label(tokensEntrada) && match(":", tokensEntrada) && basicStatement(tokensEntrada)));
}
// end nhank (proced)
bool label(std::vector<Token> tokensEntrada){
    std::cout << "Função: label" << std::endl;
    int auxPos = pos;
    if (not (identifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (unsignedInteger(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (identifier(tokensEntrada) || unsignedInteger(tokensEntrada));
}

bool unlabelledBasicStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: unlabelledBasicStatement" << std::endl;
    int auxPos = pos;
    if (not (assignmentStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (goToStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (procedureStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (assignmentStatement(tokensEntrada) || goToStatement(tokensEntrada) || procedureStatement(tokensEntrada));
}

bool assignmentStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: assignmentStatement" << std::endl;
    int auxPos = pos;
    if (not (leftPartList(tokensEntrada) && arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (leftPartList(tokensEntrada) && booleanExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((leftPartList(tokensEntrada) && arithmeticExpression(tokensEntrada)) || (leftPartList(tokensEntrada) && booleanExpression(tokensEntrada)));
}

bool leftPartList(std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPartList" << std::endl;
    int auxPos = pos;
    if (not (leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada));
}

bool auxLeftPartList(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxLeftPartList" << std::endl;
    int auxPos = pos;
    if (not (leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((leftPart(tokensEntrada) && auxLeftPartList(tokensEntrada)) || true);
}
//Correto
bool leftPart(std::vector<Token> tokensEntrada){
    std::cout << "Função: leftPart" << std::endl;
    int auxPos = pos;
    if (not (variable(tokensEntrada) && match(":=", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (procedureIdentifier(tokensEntrada) && match(":=", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((variable(tokensEntrada) && match(":=", tokensEntrada)) || (procedureIdentifier(tokensEntrada) && match(":=", tokensEntrada)));
}

bool goToStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: goToStatement" << std::endl;
    int auxPos = pos;
    if (not (match("goto", tokensEntrada) && designationalExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (match("goto", tokensEntrada) && designationalExpression(tokensEntrada));
}

bool designationalExpression(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (simpleDesignationalExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (ifClause(tokensEntrada) && simpleDesignationalExpression(tokensEntrada) && match("else", tokensEntrada) && designationalExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (simpleDesignationalExpression(tokensEntrada) || (ifClause(tokensEntrada) && simpleDesignationalExpression(tokensEntrada) && match("else", tokensEntrada) && designationalExpression(tokensEntrada) ) );
}

bool simpleDesignationalExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleDesignationalExpression" << std::endl;
    int auxPos = pos;
    if (not (label(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("(", tokensEntrada) && designationalExpression(tokensEntrada) && match(")", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (label(tokensEntrada) || (match("(", tokensEntrada) && designationalExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool procedureStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: procedureStatement" << std::endl;
    int auxPos = pos;
    if (not (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada)));
}

bool actualParameterPart(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (match("(", tokensEntrada) && actualParameterList(tokensEntrada) && match(")", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (true || (match("(", tokensEntrada) && actualParameterList(tokensEntrada) && match(")", tokensEntrada)));
}

bool actualParameterList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada));
}

bool auxActualParameterList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (parameterDelimiter(tokensEntrada) && actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return ((parameterDelimiter(tokensEntrada) && actualParameter(tokensEntrada) && auxActualParameterList(tokensEntrada)) || true);
}

bool parameterDelimiter(std::vector<Token> tokensEntrada){
    return (match(",", tokensEntrada));
}



bool actualParameter(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: actualParameter" << std::endl;
    int auxPos = pos;
   // return (expression(tokensEntrada) || arrayIdentifier(tokensEntrada) || procedureIdentifier(tokensEntrada));
    if (not expression(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not arrayIdentifier(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not procedureIdentifier(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    return true;
}

bool conditionalStatement(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: conditionalStatement" << std::endl;
    int auxPos = pos;
    
    // return ((ifStatement(tokensEntrada)) || (ifStatement(tokensEntrada) && match("else", tokensEntrada) && statement(tokensEntrada)) || 
    //(ifClause(tokensEntrada) && forStatement(tokensEntrada)) || (label(tokensEntrada) && match(":", tokensEntrada) && conditionalStatement(tokensEntrada)));
    
    if (not (ifStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if(not (ifStatement(tokensEntrada) && match("else", tokensEntrada) && statement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if(not (ifClause(tokensEntrada) && forStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if(not (label(tokensEntrada) && match(":", tokensEntrada) && conditionalStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;
}

bool ifStatement(std::vector<Token> tokensEntrada){ //Paloma
    //return (ifClause(tokensEntrada) && unconditionalStatement(tokensEntrada));
    int auxPos = pos;
    if (not (ifClause(tokensEntrada) && unconditionalStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
}

bool ifClause(std::vector<Token> tokensEntrada){ //Paloma
    int auxPos = pos;
    //return ((match("if", tokensEntrada) && booleanExpression(tokensEntrada) && match("then", tokensEntrada)));
    
    if (not (match("if", tokensEntrada) && booleanExpression(tokensEntrada) && match("then", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;   
}

bool forStatement(std::vector<Token> tokensEntrada){
    std::cout << "Função: forStatement" << std::endl;
    //return ((forClause(tokensEntrada) && statement(tokensEntrada)) || (label(tokensEntrada) && match(":", tokensEntrada) && forStatement(tokensEntrada)));
    int auxPos = pos;
    
    if(not (forClause(tokensEntrada) && statement(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    if(not (label(tokensEntrada) && match(":", tokensEntrada) && forStatement(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    
    return true;
}

bool forClause(std::vector<Token> tokensEntrada){ //Paloma

    //return (match("for", tokensEntrada) && variable(tokensEntrada) && match(":=", tokensEntrada) && forList(tokensEntrada) && match("do", tokensEntrada));
    int auxPos = pos;
    if(not (match("for", tokensEntrada) && variable(tokensEntrada) && match(":=", tokensEntrada) && forList(tokensEntrada) && match("do", tokensEntrada))){
        pos = auxPos;
        return false;
    }    
    return true;
}

bool forList(std::vector<Token> tokensEntrada){ //Paloma
    int auxPos = pos;
    //return (forListElement(tokensEntrada) && auxForList(tokensEntrada));
    if(not (forListElement(tokensEntrada) && auxForList(tokensEntrada))){
        pos = auxPos;
        return false;
    }    
    return true;
}
bool auxForList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    //return ((match(",", tokensEntrada) && forListElement(tokensEntrada) && auxForList(tokensEntrada)) || true);
    if(not (match(",", tokensEntrada) && forListElement(tokensEntrada) && auxForList(tokensEntrada))){
        pos = auxPos;
    }    
    return true;
}

bool forListElement(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: forListElement" << std::endl;
    int auxPos = pos;
    //return ((arithmeticExpression(tokensEntrada)) || (arithmeticExpression(tokensEntrada) && match("step" , tokensEntrada) && arithmeticExpression(tokensEntrada) && match("until", tokensEntrada) && 
    //arithmeticExpression(tokensEntrada)) || (arithmeticExpression(tokensEntrada) && match("while" , tokensEntrada) && booleanExpression(tokensEntrada)));
    
    if(not (arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if((arithmeticExpression(tokensEntrada) && match("step" , tokensEntrada) && arithmeticExpression(tokensEntrada) && match("until", tokensEntrada) && 
    arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if((arithmeticExpression(tokensEntrada) && match("while" , tokensEntrada) && booleanExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }       
    return true;
}

bool expression(std::vector<Token> tokensEntrada){
    std::cout << "Função: expression" << std::endl;
    int auxPos = pos;
    
    //return (arithmeticExpression(tokensEntrada) || booleanExpression(tokensEntrada) || designationalExpression(tokensEntrada));
    if(not arithmeticExpression(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not booleanExpression(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not designationalExpression(tokensEntrada)){
        pos = auxPos;
        return false;
    }

    return true;
}

bool arithmeticExpression(std::vector<Token> tokensEntrada){//Paloma
    std::cout << "Função: arithmeticExpression" << std::endl;
    int auxPos = pos;
    
    //return (simpleArithmeticExpression(tokensEntrada) || ((ifClause(tokensEntrada) && simpleArithmeticExpression(tokensEntrada) &&
    //match("else", tokensEntrada) && arithmeticExpression(tokensEntrada))));
    
    if(not simpleArithmeticExpression(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if(not simpleArithmeticExpression(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if((ifClause(tokensEntrada) && simpleArithmeticExpression(tokensEntrada) && match("else", tokensEntrada) && arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    
    return true;
}

bool simpleArithmeticExpression(std::vector<Token> tokensEntrada){ //Paloma
    std::cout << "Função: simpleArithmeticExpression" << std::endl;
    int auxPos = pos;
    //return ((term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)) || (addingOperator(tokensEntrada) && term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)));
    
    if(not (term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if(not ((addingOperator(tokensEntrada) && term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)))){
        pos = auxPos;
        return false;
    }
    return true;

}

bool auxSimpleArithmeticExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxSimpleArithmeticExpression" << std::endl;
    int auxPos = pos;
    //return ((addingOperator(tokensEntrada) && term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada)) || true);
    if(not (addingOperator(tokensEntrada) && term(tokensEntrada) && auxSimpleArithmeticExpression(tokensEntrada))){
        pos = auxPos;
    }
    
    return true;
}

bool addingOperator(std::vector<Token> tokensEntrada){ 
    return (match("+", tokensEntrada) || match("-", tokensEntrada));
}

bool term(std::vector<Token> tokensEntrada){
    std::cout << "Função: term" << std::endl;
    int auxPos = pos;

    //return (factor(tokensEntrada) && auxTerm(tokensEntrada));

    if(not ( factor(tokensEntrada) && auxTerm(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
}

bool auxTerm(std::vector<Token> tokensEntrada){ //Paloma 
    int auxPos = pos;
    
    //return ((multiplyingOperator(tokensEntrada) && factor(tokensEntrada) && auxTerm(tokensEntrada)) || true);
    if(not (multiplyingOperator(tokensEntrada) && factor(tokensEntrada) && auxTerm(tokensEntrada))){
        pos = auxPos;
    }
    
    return true;

}

bool multiplyingOperator(std::vector<Token> tokensEntrada){
    return (match("*", tokensEntrada));
}

// ELIAS A PARTIR DAQ 


bool factor(std::vector<Token> tokensEntrada){
    std::cout << "Função: factor" << std::endl;
    int auxPos = pos;
    if (not primary(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not (factor(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    //return (primary(tokensEntrada) || factor(tokensEntrada));
}

bool primary(std::vector<Token> tokensEntrada){
    std::cout <<"Função: primary"<<std::endl;
    int auxPos = pos;
    
    if (not unsignedNumber(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not variable(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not functionDesignator(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not (match("(", tokensEntrada) && arithmeticExpression(tokensEntrada) && match(")", tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;
    // return (unsignedNumber(tokensEntrada) || variable(tokensEntrada) || functionDesignator(tokensEntrada) || 
    // (match("(", tokensEntrada) && arithmeticExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool unsignedNumber(std::vector<Token> tokensEntrada){
    std::cout <<"Função: unsignedNumber"<<std::endl;
    int auxPos = pos;
    
    if (not decimalNumber(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not exponentialPart(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not (decimalNumber(tokensEntrada) && exponentialPart(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return false;
    
    // return (decimalNumber(tokensEntrada) || exponentialPart(tokensEntrada) || (decimalNumber(tokensEntrada) && exponentialPart(tokensEntrada)));
}

bool decimalNumber(std::vector<Token> tokensEntrada){
    std::cout <<"Função: decimalNumber"<<std::endl;
    int auxPos = pos;
    
    if (not unsignedInteger(tokensEntrada)){
        pos = auxPos;
        return false;
    }

    return true;
    // return (unsignedInteger(tokensEntrada));
}

bool unsignedInteger(std::vector<Token> tokensEntrada){
    std::cout << "Função: unsignedInteger" << std::endl;
    int auxPos = pos;
    if (not (digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada));
}

bool auxUnsignedInteger(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxUnsignedInteger" << std::endl;
    int auxPos = pos;
    if (not (digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada))){
        pos = auxPos;
    }
    return true;
    // return ((digit(tokensEntrada) && auxUnsignedInteger(tokensEntrada)) || true);
}

bool exponentialPart(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (match("^", tokensEntrada) && integer(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (match("^", tokensEntrada) && integer(tokensEntrada));
}

bool integer(std::vector<Token> tokensEntrada){
    std::cout <<"Função: Integer"<<std::endl;
    int auxPos = pos;
    
    if (not (unsignedInteger(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if(not (match("+", tokensEntrada) && unsignedInteger(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("-", tokensEntrada) && unsignedInteger(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    
    return true;
    // return ((unsignedInteger(tokensEntrada)) || (match("+", tokensEntrada) && unsignedInteger(tokensEntrada)) || 
    // (match("-", tokensEntrada) && unsignedInteger(tokensEntrada)));
}

bool booleanExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: booleanExpression" << std::endl;
    int auxPos = pos;
    
    if (not (simpleBoolean(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (ifClause(tokensEntrada) && simpleBoolean(tokensEntrada) && match("else", tokensEntrada) && booleanExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;

    // return (simpleBoolean(tokensEntrada) || (ifClause(tokensEntrada) && simpleBoolean(tokensEntrada)
    // && match("else", tokensEntrada) && booleanExpression(tokensEntrada)));
}

bool simpleBoolean(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada));
}

bool auxSimpleBoolean(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (match("==", tokensEntrada) && implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada))){
        pos = auxPos;
    }
    return true;
    // return ((match("==", tokensEntrada) && implication(tokensEntrada) && auxSimpleBoolean(tokensEntrada)) || true);
}

bool implication(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (booleanTerm(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return booleanTerm(tokensEntrada);
}

bool booleanTerm(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;

    // return (booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada));
}

bool auxBooleanTerm(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (match("||", tokensEntrada) && booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada))){
        pos = auxPos;
    }
    return true;

    //return ((match("||", tokensEntrada) && booleanFactor(tokensEntrada) && auxBooleanTerm(tokensEntrada)) || true);
}

bool booleanFactor(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    // return (booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada));
}

bool auxBooleanFactor(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (match("&&", tokensEntrada) && booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada))){
        pos = auxPos;
    }
    return true;
    // return ((match("&&", tokensEntrada) && booleanSecondary(tokensEntrada) && auxBooleanFactor(tokensEntrada)) || true);
}

bool booleanSecondary(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (booleanPrimary(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("!", tokensEntrada) && booleanPrimary(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;

    //return (booleanPrimary(tokensEntrada) || (match("!", tokensEntrada) && booleanPrimary(tokensEntrada) ));
}

bool booleanPrimary(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (logicalValue(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (variable(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (funcionDesignator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (relation(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("(", tokensEntrada) && booleanExpression(tokensEntrada) && match(")", tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;

    // return (logicalValue(tokensEntrada) || variable(tokensEntrada) || funcionDesignator(tokensEntrada) || relation(tokensEntrada) || (match("(", tokensEntrada) && booleanExpression(tokensEntrada) && match(")", tokensEntrada)));
}

bool functionDesignator(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    // return (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada));
}

bool relation(std::vector<Token> tokensEntrada){
    std::cout << "Função: relation" << std::endl;
    int auxPos = pos;
    
    if (not (simpleArithmeticExpression(tokensEntrada) && relationalOperator(tokensEntrada) && simpleArithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return false;

    //return (simpleArithmeticExpression(tokensEntrada) && relationalOperator(tokensEntrada) && simpleArithmeticExpression(tokensEntrada));
}

bool funcionDesignator(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (procedureIdentifier(tokensEntrada) && actualParameterPart(tokensEntrada));
}

bool variable(std::vector<Token> tokensEntrada){
    std::cout << "Função: variable" << std::endl;
    int auxPos = pos;
    
    if (not (simpleVariable(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (subscriptedVariable(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (simpleVariable(tokensEntrada) || subscriptedVariable(tokensEntrada));
}

bool simpleVariable(std::vector<Token> tokensEntrada){
    std::cout << "Função: simpleVariable" << std::endl;
    int auxPos = pos;
    
    if (not (variableIdenfier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return variableIdenfier(tokensEntrada);
}

bool variableIdenfier(std::vector<Token> tokensEntrada){
    std::cout << "Função: variableIdentifier" << std::endl;
    int auxPos = pos;
    
    if (not (identifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    
    return true;
    //return identifier(tokensEntrada);
}

bool subscriptedVariable(std::vector<Token> tokensEntrada){
    std::cout << "Função: subscriptedVariable" << std::endl;
    int auxPos = pos;
    
    if (not (arrayIdentifier(tokensEntrada) && match("[", tokensEntrada) && subscriptList(tokensEntrada) && match("]", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    // return (arrayIdentifier(tokensEntrada) && match("[", tokensEntrada) && subscriptList(tokensEntrada) && match("]", tokensEntrada));
}

bool subscriptList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    // return (subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada));
}

bool auxSubscriptList(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (match(",", tokensEntrada) && subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada))){
        pos = auxPos;
    }
    return true;
    // return ((match(",", tokensEntrada) && subscriptExpression(tokensEntrada) && auxSubscriptList(tokensEntrada)) || true);
}

bool subscriptExpression(std::vector<Token> tokensEntrada){
    std::cout << "Função: subscriptExpression" << std::endl;
    int auxPos = pos;
    
    if (not (arithmeticExpression(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    // return (arithmeticExpression(tokensEntrada));
}

bool identifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: identifier" << std::endl;
    int auxPos = pos;
    
    if (not (letter(tokensEntrada) && auxIdentifier(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    // return (letter(tokensEntrada) && auxIdentifier(tokensEntrada));
}

bool auxIdentifier(std::vector<Token> tokensEntrada){
    std::cout << "Função: auxIdentifier" << std::endl;
    int auxPos = pos;
    
    if (not (digit(tokensEntrada) && auxIdentifier(tokensEntrada))){
        pos = auxPos;
    }
    if (not (letter(tokensEntrada) && auxIdentifier(tokensEntrada))){
        pos = auxPos;
    }
    
    return true;
    //return ((digit(tokensEntrada) && auxIdentifier(tokensEntrada)) || (letter(tokensEntrada) && auxIdentifier(tokensEntrada)) || true);
}

bool basicSymbol(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    
    if (not (letter(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not digit(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not logicalValue(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    if (not delimiter(tokensEntrada)){
        pos = auxPos;
        return false;
    }
    return true;
    
    //return(letter(tokensEntrada) || digit(tokensEntrada) || logicalValue(tokensEntrada) || delimiter(tokensEntrada));
}

bool letter(std::vector<Token> tokensEntrada){
    std::cout << "Função: letter" << std::endl;
    int auxPos = pos;
    if (not (matchLetter(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    //return matchLetter(tokensEntrada);
}

bool digit(std::vector<Token> tokensEntrada){
    std::cout << "Função: digit" << std::endl;
    int auxPos = pos;
    if (not (matchDigit(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    //return matchDigit(tokensEntrada);
}

bool logicalValue(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (match("true", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (match("false", tokensEntrada))){
        pos = auxPos;
        return false;
    }
    return true;
    
    //return (match("true", tokensEntrada) || match("false", tokensEntrada));
}

bool delimiter(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (Operator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (separator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (bracket(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (declarator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (specificator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    
    return true;
    
    // return (Operator(tokensEntrada) || separator(tokensEntrada) || bracket(tokensEntrada) || declarator(tokensEntrada) || specificator(tokensEntrada));
}

bool Operator(std::vector<Token> tokensEntrada){
    int auxPos = pos;
    if (not (arithmeticOperator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (relationalOperator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (logicalOperator(tokensEntrada))){
        pos = auxPos;
        return false;
    }
    if (not (sequentialOperator(tokensEntrada))){
        pos = auxPos;
        return false;
    }

    return true;
    // return (arithmeticOperator(tokensEntrada) || relationalOperator(tokensEntrada) || logicalOperator(tokensEntrada) || sequentialOperator(tokensEntrada));
}

bool arithmeticOperator(std::vector<Token> tokensEntrada){
    return (match("+", tokensEntrada) || match("-", tokensEntrada) || match("*", tokensEntrada) || match("/", tokensEntrada));
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