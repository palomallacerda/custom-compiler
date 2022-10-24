#pragma once
#include <string>
#include <list>

//-----Declaração da classe Token, não sei se foi feita direito
class Token{
    public:
        std::string rotulo;
        std::string tipo;
};

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
bool ChecaValidos(char *validos, char character, int size_arr);

// verify reserverd words
std::list<Token> seekReserved(int start, int end, std::fstream& File, std::list<Token> TokensClasses, std::string* BracketComp, std::string* opCompRelational,
std::string* compSeparators,  std::string* declarator, std::string* opSequential, char *Digits);
