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

bool arithmeticExpression(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #1" << std::endl;
    return false;
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

bool parameterDelimiter(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #1" << std::endl;
    return false;
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

bool conditionalStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #2" << std::endl;
    return false;
}

bool forStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #3" << std::endl;
    return false;
}

bool basicStatement(int pos, std::vector<Token> tokensEntrada){
    return (unlabelledBasicStatement(pos, tokensEntrada) || (label(pos, tokensEntrada) && match(":", tokensEntrada) && basicStatement(pos, tokensEntrada)));
}

bool label(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #4" << std::endl;
    return false;
}

bool unlabelledBasicStatement(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #6" << std::endl;
    return false;
}

bool simpleVariable(int pos, std::vector<Token> tokensEntrada){
    return variableIdenfier(pos, tokensEntrada);
}

bool variableIdenfier(int pos, std::vector<Token> tokensEntrada){
    return identifier(pos, tokensEntrada);
}

bool identifier(int pos, std::vector<Token> tokensEntrada){
    return (letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada));
}

bool auxIdentifier(int pos, std::vector<Token> tokensEntrada){
    return ((letter(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || (digit(pos, tokensEntrada) && auxIdentifier(pos, tokensEntrada)) || true);
}

bool digit(int pos, std::vector<Token> tokensEntrada){
    std::cout << "Falta implementar aqui #5" << std::endl;
    return false;
}

bool letter(int pos, std::vector<Token> tokensEntrada){
    return matchLetter(tokensEntrada);
}

//PARAR POR AQUI PARA TESTAR