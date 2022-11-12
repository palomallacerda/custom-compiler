#pragma once
#include <vector>
#include <string>
#include <list>

//-----Declaração da classe Token, não sei se foi feita direito
class Token{
    public:
        std::string rotulo;
        std::string tipo;
};

class TabelaPred{
    public:
        std::string nome;
        std::string tipo;
        std::string valorInicial;
        std::string escopo;
};

bool Analisador_Lexico();

//---------- Encontrando os Simples
std::vector<Token> SeekLetters(int i, char *Letters, int Size, char character, std::vector<Token> TokensClasses);
bool SeekDigits(char *Digits, int Size, char character,std::vector<Token> TokensClasses);
bool SeekSeparators(char *separators, int size, char character,std::vector<Token> TokensClasses);
bool SeekArithmetic(char *opArithmetic, int size, char character,std::vector<Token> TokensClasses);
bool SeekRelational(char *opRelational, int size, char character,std::vector<Token> TokensClasses);

//---------- Encontrando compostos
//Bracket
std::vector<Token> SeekBegin(int &validBegin, std::string* Bracket, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekEnd(int &validEnd, std::string* Bracket, char character, std::vector<Token> TokensClasses);

//compSeparators
std::vector<Token> SeekAssigment(int &validAssigment, std::string* compSeparators, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekStep(int &validStep, std::string* compSeparators, char character, std::vector<Token> TokensClasses);
std::vector<Token> Seekuntil(int &validuntil, std::string* compSeparators, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekWhile(int &validWhile, std::string* compSeparators, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekComment(int &validComment, std::string* compSeparators, char character, std::vector<Token> TokensClasses);

//opComRelational
std::vector<Token> SeekMenorIgual(int &validMenorIgual, std::string* opCompRelational, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekDiferente(int &validDiferente, std::string* opCompRelational, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekMaiorIgual(int &validMaiorIgual, std::string* opCompRelational, char character, std::vector<Token> TokensClasses);


//Declarator
std::vector<Token> SeekOwn(int &validOwn, std::string* declarador, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekInteger(int &validInt, std::string* declarador, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekArray(int &validArray, std::string* declarador, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekProcedure(int &validProcedure, std::string* declarador, char character, std::vector<Token> TokensClasses);

//OpSequential
std::vector<Token> SeekGoto(int &validGoto, std::string* opSequential, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekIf(int &validIf, std::string* opSequential, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekThen(int &validThen, std::string* opSequential, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekElse(int &validElse, std::string* opSequential, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekFor(int &validFor, std::string* opSequential, char character, std::vector<Token> TokensClasses);
std::vector<Token> SeekDo(int &validDo, std::string* opSequential, char character, std::vector<Token> TokensClasses);

// Check errors
std::vector<Token> TokensLexico();
bool ChecaValidos(char *validos, char character, int size_arr);

// verify reserverd words
std::vector<Token> seekReserved(int start, int end, std::fstream& File, std::vector<Token> TokensClasses, std::string* BracketComp, std::string* opCompRelational,std::string* compSeparators,  std::string* declarator, std::string* opSequential, char *Digits);

// Verify Sintatic Analysis
// std::list<Token> InicialState(std::list <Token> tokensEntrada);
// bool block(Token* aux, std::list <Token>* tokensEntrada);
// bool UnlabelledBlock(Token* aux, std::list <Token>* tokensEntrada);
// bool blockHead(Token* aux, std::list <Token>* tokensEntrada);
// bool blockaux(Token* aux, std::list <Token>* tokensEntrada);
// bool compoundStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool unlabelledCompound(Token* aux, std::list <Token>* tokensEntrada);
// bool declaration(Token* aux, std::list <Token>* tokensEntrada);
// bool arrayDeclaration(Token* aux, std::list <Token>* tokensEntrada);
// bool arrayList(Token* aux, std::list <Token>* tokensEntrada);
// bool auxArrayList(Token* aux, std::list <Token>* tokensEntrada);
// bool arraySegment(Token* aux, std::list <Token>* tokensEntrada);
// bool boundPairList(Token* aux, std::list <Token>* tokensEntrada);
// bool auxBoundPair(Token* aux, std::list <Token>* tokensEntrada);
// bool boundPair(Token* aux, std::list <Token>* tokensEntrada);
// bool lowerBound(Token* aux, std::list <Token>* tokensEntrada);
// bool procedureDeclaration(Token* aux, std::list <Token>* tokensEntrada);
// bool type(Token* aux, std::list <Token>* tokensEntrada);
// bool procedureHeading(Token* aux, std::list <Token>* tokensEntrada);
// bool specificationPart(Token* aux, std::list <Token>* tokensEntrada);
// bool auxSpecificationPart(Token* aux, std::list <Token>* tokensEntrada);
// bool subscriptExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool auxIdentifierList(Token* aux, std::list <Token>* tokensEntrada);
// bool specifier(Token* aux, std::list <Token>* tokensEntrada);
// bool valuePart(Token* aux, std::list <Token>* tokensEntrada);
// bool formalParameterPart(Token* aux, std::list <Token>* tokensEntrada);
// bool formalParameterList(Token* aux, std::list <Token>* tokensEntrada);
// bool auxFormalParameterList(Token* aux, std::list <Token>* tokensEntrada);
// bool parameterDelimiter(Token* aux, std::list <Token>* tokensEntrada);
// bool formalParameter(Token* aux, std::list <Token>* tokensEntrada);
// bool procedureBody(Token* aux, std::list <Token>* tokensEntrada);
// bool typedeclaration(Token* aux, std::list<Token>* TokensEntrada);
// bool typeList(Token* aux, std::list <Token>* tokensEntrada);
// bool simpleVariable(Token* aux, std::list <Token>* tokensEntrada);
// bool Local_or_Own_type(Token* aux, std::list<Token>* tokensEntrada);
// bool compoundTail(Token* aux, std::list <Token>* tokensEntrada);
// bool statement(Token* aux, std::list <Token>* tokensEntrada);
// bool uncoditionalStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool basicStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool label(Token* aux, std::list <Token>* tokensEntrada);
// bool UnlabelledbasicStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool unsignedInteger(Token* aux, std::list <Token>* tokensEntrada);
// bool unsignedIntegerAux(Token* aux, std::list <Token>* tokensEntrada, char character, int i, int tam);
// bool conditionalStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool forStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool assignmentStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool leftPart(Token* aux, std::list <Token>* tokensEntrada);
// bool leftPartList(Token* aux, std::list <Token>* tokensEntrada);
// bool forClause(Token *aux, std::list <Token>* tokensEntrada);
// bool forList(Token* aux, std::list <Token>* tokensEntrada);
// bool forListAux(Token* aux, std::list <Token>* tokensEntrada);
// bool arithmeticExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool simpleArithmeticExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool addingOperator(Token *aux, std::list <Token>* tokensEntrada);
// bool term(Token* aux, std::list <Token>* tokensEntrada);
// bool auxTerm(Token* aux, std::list <Token>* tokensEntrada);
// bool multiplyingOperator(Token* aux, std::list <Token>* tokensEntrada);
// bool factor(Token *aux, std::list <Token>* tokensEntrada);
// bool forListElement(Token* aux, std::list <Token>* tokensEntrada);
// bool primary(Token* aux, std::list <Token>* tokensEntrada);
// bool exponentialPart(Token* aux, std::list <Token>* tokensEntrada);
// bool integer(Token* aux, std::list <Token>* tokensEntrada);
// bool functionDesignator(Token* aux, std::list <Token>* tokensEntrada);
// bool procedureIdentifier(Token* aux, std::list <Token>* tokensEntrada);
// bool actualParameterPart(Token* aux, std::list <Token>* tokensEntrada);
// bool actualParameterList(Token* aux, std::list <Token>* tokensEntrada);
// bool actualParameterListAux(Token* aux, std::list <Token>* tokensEntrada);
// bool actualParameter(Token* aux, std::list <Token>* tokensEntrada);
// bool goToStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool dummyStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool procedureStatement(Token* aux, std::list <Token>* tokensEntrada);
// bool designationalExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool ifClause(Token* aux, std::list <Token>* tokensEntrada);
// bool simplesDesignationalExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool identifier(Token* aux, std::list <Token>* tokensEntrada);
// bool auxIdentifier(Token* aux, std::list <Token>* tokensEntrada, char character, int i, int tam);
// bool booleanExpression(Token* aux, std::list <Token>* tokensEntrada);
// bool simpleBoolean(Token * aux, std::list <Token>* tokensEntrada);
// bool implication(Token * aux, std::list <Token>* tokensEntrada);
// bool booleanTerm(Token * aux, std::list <Token>* tokensEntrada);
// bool auxBooleanTerm(Token * aux, std::list <Token>* tokensEntrada);
// bool booleanFactor(Token * aux, std::list <Token>* tokensEntrada);
// bool auxBooleanFactor(Token * aux, std::list <Token>* tokensEntrada);
// bool booleanSecondary(Token * aux, std::list <Token>* tokensEntrada);
// bool booleanPrimary(Token * aux, std::list <Token>* tokensEntrada);
// bool expression(Token* aux, std::list <Token>* tokensEntrada);
// bool logicalValue(Token * aux, std::list <Token>* tokensEntrada);
// bool relation(Token * aux, std::list <Token>* tokensEntrada);
// bool relationalOperator(Token * aux, std::list <Token>* tokensEntrada);
// bool ifStatement(Token * aux, std::list <Token>* tokensEntrada);
// bool variable(Token* aux, std::list <Token>* tokensEntrada);
// bool variableIdenfier(Token* aux, std::list <Token>* tokensEntrada);
// bool subscriptedVariable(Token* aux, std::list <Token>* tokensEntrada);
// bool arrayIdentifier(Token * aux, std::list <Token>* tokensEntrada);
// bool subscriptList(Token * aux, std::list <Token>* tokensEntrada);
// bool subscriptExpression(Token * aux, std::list <Token>* tokensEntrada);
// bool letter(Token* aux, std::list <Token>* tokensEntrada, char character);
// bool digit(Token* aux, std::list <Token>* tokensEntrada, char character);
// bool auxSimpleBoolean(Token *aux, std::list <Token>* tokensEntrada);
// bool identifierList(Token* aux, std::list <Token>* tokensEntrada);
// bool basicSymbol(Token* aux, std::list <Token>* tokensEntrada, char character);
// bool delimiterFunction(Token* aux, std::list <Token>* tokensEntrada);
// bool separator(Token* aux, std::list <Token>* tokensEntrada);
// bool operatorFunction(Token* aux, std::list <Token>* tokensEntrada);
// bool declator(Token* aux, std::list <Token>* tokensEntrada);
// bool bracket(Token* aux, std::list <Token>* tokensEntrada);
// bool specificator(Token* aux, std::list <Token>* tokensEntrada);
// bool arithmeticOperator(Token* aux, std::list <Token>* tokensEntrada);
// bool logicalOperator(Token* aux, std::list <Token>* tokensEntrada);
// bool sequentialOperator(Token* aux, std::list <Token>* tokensEntrada);
// bool auxSimpleArithmeticExpression(Token* aux, std::list <Token>* tokensEntrada);

bool program(std::vector<Token> tokensEntrada);
bool block(std::vector<Token> tokensEntrada);
bool unlabelledBlock(std::vector<Token> tokensEntrada);
bool blockHead(std::vector<Token> tokensEntrada);
bool blockAux(std::vector<Token> tokensEntrada);
bool compoundStatement(std::vector<Token> tokensEntrada);
bool unlabelledCompound(std::vector<Token> tokensEntrada);
bool compoundTail(std::vector<Token> tokensEntrada);
bool declaration(std::vector<Token> tokensEntrada);
bool typedeclaration(std::vector<Token> tokensEntrada);
bool localOrOwnType(std::vector<Token> tokensEntrada);
bool type(std::vector<Token> tokensEntrada);
bool typeList(std::vector<Token> tokensEntrada);
bool arrayDeclaration(std::vector<Token> tokensEntrada);
bool arrayList(std::vector<Token> tokensEntrada);
bool auxArrayList(std::vector<Token> tokensEntrada);
bool arraySegment(std::vector<Token> tokensEntrada);
bool arrayIdentifier(std::vector<Token> tokensEntrada);
bool boundPairList(std::vector<Token> tokensEntrada);
bool auxBoundPairList(std::vector<Token> tokensEntrada);
bool boundPair(std::vector<Token> tokensEntrada);
bool lowerBound(std::vector<Token> tokensEntrada);
bool procedureDeclaration(std::vector<Token> tokensEntrada);
bool procedureHeading(std::vector<Token> tokensEntrada);
bool procedureIdentifier(std::vector<Token> tokensEntrada);
bool formalParameterPart(std::vector<Token> tokensEntrada);
bool formalParameterList(std::vector<Token> tokensEntrada);
bool auxFormalParameterList(std::vector<Token> tokensEntrada);
bool formalParameter(std::vector<Token> tokensEntrada);
bool valuePart(std::vector<Token> tokensEntrada);
bool specificationPart(std::vector<Token> tokensEntrada);
bool auxSpecificationPart(std::vector<Token> tokensEntrada);
bool specifier(std::vector<Token> tokensEntrada);
bool identifierList(std::vector<Token> tokensEntrada);
bool auxIdentifierList(std::vector<Token> tokensEntrada);
bool procedureBody(std::vector<Token> tokensEntrada);
bool statement(std::vector<Token> tokensEntrada);
bool unconditionalStatement(std::vector<Token> tokensEntrada);
bool basicStatement(std::vector<Token> tokensEntrada);
bool label(std::vector<Token> tokensEntrada);
bool unlabelledBasicStatement(std::vector<Token> tokensEntrada);
bool assignmentStatement(std::vector<Token> tokensEntrada);
bool leftPartList(std::vector<Token> tokensEntrada);
bool auxLeftPartList(std::vector<Token> tokensEntrada);
bool leftPart(std::vector<Token> tokensEntrada);
bool goToStatement(std::vector<Token> tokensEntrada);
bool designationalExpression(std::vector<Token> tokensEntrada);
bool simpleDesignationalExpression(std::vector<Token> tokensEntrada);
bool procedureStatement(std::vector<Token> tokensEntrada);
bool actualParameterPart(std::vector<Token> tokensEntrada);
bool actualParameterList(std::vector<Token> tokensEntrada);
bool auxActualParameterList(std::vector<Token> tokensEntrada);
bool parameterDelimiter(std::vector<Token> tokensEntrada);
bool actualParameter(std::vector<Token> tokensEntrada);
bool conditionalStatement(std::vector<Token> tokensEntrada);
bool ifStatement(std::vector<Token> tokensEntrada);
bool ifClause(std::vector<Token> tokensEntrada);
bool forStatement(std::vector<Token> tokensEntrada);
bool forClause(std::vector<Token> tokensEntrada);
bool forList(std::vector<Token> tokensEntrada);
bool auxForList(std::vector<Token> tokensEntrada);
bool forListElement(std::vector<Token> tokensEntrada);
bool expression(std::vector<Token> tokensEntrada);
bool arithmeticExpression(std::vector<Token> tokensEntrada);
bool simpleArithmeticExpression(std::vector<Token> tokensEntrada);
bool auxSimpleArithmeticExpression(std::vector<Token> tokensEntrada);
bool addingOperator(std::vector<Token> tokensEntrada);
bool term(std::vector<Token> tokensEntrada);
bool auxTerm(std::vector<Token> tokensEntrada);
bool multiplyingOperator(std::vector<Token> tokensEntrada);
bool factor(std::vector<Token> tokensEntrada);
bool primary(std::vector<Token> tokensEntrada);
bool unsignedNumber(std::vector<Token> tokensEntrada);
bool decimalNumber(std::vector<Token> tokensEntrada);
bool unsignedInteger(std::vector<Token> tokensEntrada);
bool auxUnsignedInteger(std::vector<Token> tokensEntrada);
bool exponentialPart(std::vector<Token> tokensEntrada);
bool integer(std::vector<Token> tokensEntrada);
bool booleanExpression(std::vector<Token> tokensEntrada);
bool simpleBoolean(std::vector<Token> tokensEntrada);
bool auxSimpleBoolean(std::vector<Token> tokensEntrada);
bool implication(std::vector<Token> tokensEntrada);
bool booleanTerm(std::vector<Token> tokensEntrada);
bool auxBooleanTerm(std::vector<Token> tokensEntrada);
bool booleanFactor(std::vector<Token> tokensEntrada);
bool auxBooleanFactor(std::vector<Token> tokensEntrada);
bool booleanSecondary(std::vector<Token> tokensEntrada);
bool booleanPrimary(std::vector<Token> tokensEntrada);
bool functionDesignator(std::vector<Token> tokensEntrada);
bool relation(std::vector<Token> tokensEntrada);
bool funcionDesignator(std::vector<Token> tokensEntrada);
bool variableIdenfier(std::vector<Token> tokensEntrada);
bool subscriptedVariable(std::vector<Token> tokensEntrada);
bool subscriptList(std::vector<Token> tokensEntrada);
bool auxSubscriptList(std::vector<Token> tokensEntrada);
bool subscriptExpression(std::vector<Token> tokensEntrada);
bool identifier(std::vector<Token> tokensEntrada);
bool auxIdentifier(std::vector<Token> tokensEntrada);
bool basicSymbol(std::vector<Token> tokensEntrada);
bool letter(std::vector<Token> tokensEntrada);
bool digit(std::vector<Token> tokensEntrada);
bool logicalValue(std::vector<Token> tokensEntrada);
bool Operator(std::vector<Token> tokensEntrada);
bool arithmeticOperator(std::vector<Token> tokensEntrada);
bool relationalOperator(std::vector<Token> tokensEntrada);
bool logicalOperator(std::vector<Token> tokensEntrada);
bool variable(std::vector<Token> tokensEntrada);
bool simpleVariable(std::vector<Token> tokensEntrada);
bool variableIdentifier(std::vector<Token> tokensEntrada);
bool subscriptedVariable(std::vector<Token> tokensEntrada);
bool subscriptList(std::vector<Token> tokensEntrada);
bool subscriptExpression(std::vector<Token> tokensEntrada);
bool identifier(std::vector<Token> tokensEntrada);
bool auxIdentifier(std::vector<Token> tokensEntrada);
bool basicSymbol(std::vector<Token> tokensEntrada);
bool delimiter(std::vector<Token> tokensEntrada);
bool sequentialOperator(std::vector<Token> tokensEntrada);
bool separator(std::vector<Token> tokensEntrada);
bool bracket(std::vector<Token> tokensEntrada);
bool declarator(std::vector<Token> tokensEntrada);
bool specificator(std::vector<Token> tokensEntrada);