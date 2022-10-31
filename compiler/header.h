#pragma once
#include <string>
#include <list>

//-----Declaração da classe Token, não sei se foi feita direito
class Token{
    public:
        std::string rotulo;
        std::string tipo;
};

bool Analisador_Lexico();

//---------- Encontrando os Simples
std::list<Token> SeekLetters(int i, char *Letters, int Size, char character, std::list<Token> TokensClasses);
bool SeekDigits(char *Digits, int Size, char character,std::list<Token> TokensClasses);
bool SeekSeparators(char *separators, int size, char character,std::list<Token> TokensClasses);
bool SeekArithmetic(char *opArithmetic, int size, char character,std::list<Token> TokensClasses);
bool SeekRelational(char *opRelational, int size, char character,std::list<Token> TokensClasses);

//---------- Encontrando compostos
//Bracket
std::list<Token> SeekBegin(int &validBegin, std::string* Bracket, char character, std::list<Token> TokensClasses);
std::list<Token> SeekEnd(int &validEnd, std::string* Bracket, char character, std::list<Token> TokensClasses);

//compSeparators
std::list<Token> SeekAssigment(int &validAssigment, std::string* compSeparators, char character, std::list<Token> TokensClasses);
std::list<Token> SeekStep(int &validStep, std::string* compSeparators, char character, std::list<Token> TokensClasses);
std::list<Token> Seekuntil(int &validuntil, std::string* compSeparators, char character, std::list<Token> TokensClasses);
std::list<Token> SeekWhile(int &validWhile, std::string* compSeparators, char character, std::list<Token> TokensClasses);
std::list<Token> SeekComment(int &validComment, std::string* compSeparators, char character, std::list<Token> TokensClasses);

//opComRelational
std::list<Token> SeekMenorIgual(int &validMenorIgual, std::string* opCompRelational, char character, std::list<Token> TokensClasses);
std::list<Token> SeekDiferente(int &validDiferente, std::string* opCompRelational, char character, std::list<Token> TokensClasses);
std::list<Token> SeekMaiorIgual(int &validMaiorIgual, std::string* opCompRelational, char character, std::list<Token> TokensClasses);


//Declarator
std::list<Token> SeekOwn(int &validOwn, std::string* declarador, char character, std::list<Token> TokensClasses);
std::list<Token> SeekInteger(int &validInt, std::string* declarador, char character, std::list<Token> TokensClasses);
std::list<Token> SeekArray(int &validArray, std::string* declarador, char character, std::list<Token> TokensClasses);
std::list<Token> SeekProcedure(int &validProcedure, std::string* declarador, char character, std::list<Token> TokensClasses);

//OpSequential
std::list<Token> SeekGoto(int &validGoto, std::string* opSequential, char character, std::list<Token> TokensClasses);
std::list<Token> SeekIf(int &validIf, std::string* opSequential, char character, std::list<Token> TokensClasses);
std::list<Token> SeekThen(int &validThen, std::string* opSequential, char character, std::list<Token> TokensClasses);
std::list<Token> SeekElse(int &validElse, std::string* opSequential, char character, std::list<Token> TokensClasses);
std::list<Token> SeekFor(int &validFor, std::string* opSequential, char character, std::list<Token> TokensClasses);
std::list<Token> SeekDo(int &validDo, std::string* opSequential, char character, std::list<Token> TokensClasses);

// Check errors
std::list<Token> TokensLexico();
bool ChecaValidos(char *validos, char character, int size_arr);

// verify reserverd words
std::list<Token> seekReserved(int start, int end, std::fstream& File, std::list<Token> TokensClasses, std::string* BracketComp, std::string* opCompRelational,std::string* compSeparators,  std::string* declarator, std::string* opSequential, char *Digits);

// Verify Sintatic Analysis
std::list<Token> InicialState(std::list<Token> tokensEntrada);
bool block(Token* aux, std::list<Token> tokensEntrada);
bool UnlabelledBlock(Token* aux, std::list<Token> tokensEntrada);
bool blockHead(Token* aux, std::list<Token> tokensEntrada);
bool blockaux(Token* aux, std::list<Token> tokensEntrada);
bool compoundStatement(Token* aux, std::list <Token> tokensEntrada);
bool unlabelledCompound(Token* aux, std::list <Token> tokensEntrada);
bool declaration(Token* aux, std::list <Token> TokensEntrada);
bool arrayDeclaration(Token* aux, std::list <Token> tokensEntrada);
bool arrayList(Token* aux, std::list <Token> tokensEntrada);
bool auxArrayList(Token* aux, std::list <Token> tokensEntrada);
bool arraySegment(Token* aux, std::list <Token> tokensEntrada);
bool boundPairList(Token* aux, std::list <Token> tokensEntrada);
bool auxBoundPair(Token* aux, std::list <Token> tokensEntrada);
bool boundPair(Token* aux, std::list <Token> tokensEntrada);
bool lowerBound(Token* aux, std::list <Token> tokensEntrada);
bool procedureDeclaration(Token* aux, std::list <Token> tokensEntrada);
bool type(Token* aux, std::list <Token> tokensEntrada);
bool procedureHeading(Token* aux, std::list <Token> tokensEntrada);
bool specificationPart(Token* aux, std::list <Token> tokensEntrada);
bool auxSpecificationPart(Token* aux, std::list <Token> tokensEntrada);
bool subscriptExpression(Token* aux, std::list <Token> tokensEntrada);
bool auxIdentifierList(Token* aux, std::list <Token> tokensEntrada);
bool specifier(Token* aux, std::list <Token> tokensEntrada);
bool valuePart(Token* aux, std::list <Token> tokensEntrada);
bool formalParameterPart(Token* aux, std::list <Token> tokensEntrada);
bool formalParameterList(Token* aux, std::list <Token> tokensEntrada);
bool auxFormalParameterList(Token* aux, std::list <Token> tokensEntrada);
bool parameterDelimiter(Token* aux, std::list <Token> tokensEntrada);
bool formalParameter(Token* aux, std::list <Token> tokensEntrada);
bool procedureBody(Token* aux, std::list <Token> tokensEntrada);
bool typedeclaration(Token* aux, std::list<Token> TokensEntrada);
bool typeList(Token* aux, std::list <Token> tokensEntrada);
bool simpleVariable(Token* aux, std::list <Token> tokensEntrada);
bool Local_or_Own_type(Token* aux, std::list<Token> tokensEntrada);
bool compoundTail(Token* aux, std::list <Token> tokensEntrada);
bool statement(Token* aux, std::list <Token> tokensEntrada);
bool uncoditionalStatement(Token* aux, std::list <Token> tokensEntrada);
bool basicStatement(Token* aux, std::list <Token> tokensEntrada);
bool label(Token* aux, std::list <Token> tokensEntrada);
bool UnlabelledbasicStatement(Token* aux, std::list <Token> tokensEntrada);
bool unsignedInteger(Token* aux, std::list <Token> tokensEntrada);
bool unsignedIntegerAux(Token* aux, std::list <Token> tokensEntrada, char character, int i, int tam);
bool conditionalStatement(Token* aux, std::list <Token> tokensEntrada);
bool forStatement(Token* aux, std::list <Token> tokensEntrada);
bool assignmentStatement(Token* aux, std::list <Token> tokensEntrada);
bool leftPart(Token* aux, std::list <Token> tokensEntrada);
bool leftPartList(Token* aux, std::list <Token> tokensEntrada);
bool forClause(Token *aux, std::list <Token> tokensEntrada);
bool forList(Token* aux, std::list <Token> tokensEntrada);
bool forListAux(Token* aux, std::list <Token> tokensEntrada);
bool arithmeticExpression(Token* aux, std::list <Token> tokensEntrada);
bool simpleArithmeticExpression(Token* aux, std::list <Token> tokensEntrada);
bool addingOperator(Token *aux, std::list <Token> tokensEntrada);
bool term(Token* aux, std::list <Token> tokensEntrada);
bool auxTerm(Token* aux, std::list <Token> tokensEntrada);
bool multiplyingOperator(Token* aux, std::list <Token> tokensEntrada);
bool factor(Token *aux, std::list <Token> tokensEntrada);
bool forListElement(Token* aux, std::list <Token> tokensEntrada);
bool primary(Token* aux, std::list <Token> tokensEntrada);
bool exponentialPart(Token* aux, std::list <Token> tokensEntrada);
bool integer(Token* aux, std::list <Token> tokensEntrada);
bool functionDesignator(Token* aux, std::list <Token> tokensEntrada);
bool procedureIdentifier(Token* aux, std::list <Token> tokensEntrada);
bool actualParameterPart(Token* aux, std::list <Token> tokensEntrada);
bool actualParameterList(Token* aux, std::list <Token> tokensEntrada);
bool actualParameterListAux(Token* aux, std::list <Token> tokensEntrada);
bool actualParameter(Token* aux, std::list <Token> tokensEntrada);
bool goToStatement(Token* aux, std::list <Token> tokensEntrada);
bool dummyStatement(Token* aux, std::list <Token> tokensEntrada);
bool procedureStatement(Token* aux, std::list <Token> tokensEntrada);
bool designationalExpression(Token* aux, std::list <Token> tokensEntrada);
bool ifClause(Token* aux, std::list <Token> tokensEntrada);
bool simplesDesignationalExpression(Token* aux, std::list <Token> tokensEntrada);
bool identifier(Token* aux, std::list <Token> tokensEntrada);
bool auxIdentifier(Token* aux, std::list <Token> tokensEntrada, char character, int i, int tam);
bool booleanExpression(Token* aux, std::list <Token> tokensEntrada);
bool simpleBoolean(Token * aux, std::list <Token> tokensEntrada);
bool implication(Token * aux, std::list <Token> tokensEntrada);
bool booleanTerm(Token * aux, std::list <Token> tokensEntrada);
bool auxBooleanTerm(Token * aux, std::list <Token> tokensEntrada);
bool booleanFactor(Token * aux, std::list <Token> tokensEntrada);
bool auxBooleanFactor(Token * aux, std::list <Token> tokensEntrada);
bool booleanSecondary(Token * aux, std::list <Token> tokensEntrada);
bool booleanPrimary(Token * aux, std::list <Token> tokensEntrada);
bool expression(Token* aux, std::list <Token> tokensEntrada);
bool logicalValue(Token * aux, std::list <Token> tokensEntrada);
bool relation(Token * aux, std::list <Token> tokensEntrada);
bool relationalOperator(Token * aux, std::list <Token> tokensEntrada);
bool ifStatement(Token * aux, std::list <Token> tokensEntrada);
bool variable(Token* aux, std::list <Token> tokensEntrada);
bool variableIdenfier(Token* aux, std::list <Token> tokensEntrada);
bool subscriptedVariable(Token* aux, std::list <Token> tokensEntrada);
bool arrayIdentifier(Token * aux, std::list <Token> tokensEntrada);
bool subscriptList(Token * aux, std::list <Token> tokensEntrada);
bool subscriptExpression(Token * aux, std::list <Token> tokensEntrada);
bool letter(Token* aux, std::list <Token> tokensEntrada, char character);
bool digit(Token* aux, std::list <Token> tokensEntrada, char character);
bool auxSimpleBoolean(Token *aux, std::list<Token> tokensEntrada);
bool identifierList(Token* aux, std::list <Token> tokensEntrada);
bool basicSymbol(Token* aux, std::list <Token> tokensEntrada, char character);
bool delimiterFunction(Token* aux, std::list <Token> tokensEntrada);
bool separator(Token* aux, std::list <Token> tokensEntrada);
bool operatorFunction(Token* aux, std::list <Token> tokensEntrada);
bool declator(Token* aux, std::list <Token> tokensEntrada);
bool bracket(Token* aux, std::list <Token> tokensEntrada);
bool specificator(Token* aux, std::list <Token> tokensEntrada);
bool arithmeticOperator(Token* aux, std::list <Token> tokensEntrada);
bool logicalOperator(Token* aux, std::list <Token> tokensEntrada);
bool sequentialOperator(Token* aux, std::list <Token> tokensEntrada);
bool auxSimpleArithmeticExpression(Token* aux, std::list <Token> tokensEntrada);