#include <string>
#include <list>

//---------- Encontrando os Simples
std::list<std::string> SeekLetters(int i, char *Letters, int Size, char character, std::list <std::string> TokensClasses);
bool SeekDigits(char *Digits, int Size, char character,std::list<std::string> TokensClasses);
bool SeekSeparators(char *separators, int size, char character,std::list<std::string> TokensClasses);
bool SeekArithmetic(char *opArithmetic, int size, char character,std::list<std::string> TokensClasses);
bool SeekRelational(char *opRelational, int size, char character,std::list<std::string> TokensClasses);

//---------- Encontrando compostos
//Bracket
std::list<std::string> SeekBegin(int &validBegin, std::string* Bracket, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekEnd(int &validEnd, std::string* Bracket, char character, std::list<std::string> TokensClasses);

//compSeparators
std::list<std::string> SeekAssigment(int &validAssigment, std::string* compSeparators, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekStep(int &validStep, std::string* compSeparators, char character, std::list<std::string> TokensClasses);
std::list<std::string> Seekuntil(int &validuntil, std::string* compSeparators, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekWhile(int &validWhile, std::string* compSeparators, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekComment(int &validComment, std::string* compSeparators, char character, std::list<std::string> TokensClasses);

//opComRelational
std::list<std::string> SeekMenorIgual(int &validMenorIgual, std::string* opCompRelational, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekDiferente(int &validDiferente, std::string* opCompRelational, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekMaiorIgual(int &validMaiorIgual, std::string* opCompRelational, char character, std::list<std::string> TokensClasses);


//Declarator
std::list<std::string> SeekOwn(int &validOwn, std::string* declarador, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekInteger(int &validInt, std::string* declarador, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekArray(int &validArray, std::string* declarador, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekProcedure(int &validProcedure, std::string* declarador, char character, std::list<std::string> TokensClasses);

//OpSequential
std::list<std::string> SeekGoto(int &validGoto, std::string* opSequential, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekIf(int &validIf, std::string* opSequential, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekThen(int &validThen, std::string* opSequential, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekElse(int &validElse, std::string* opSequential, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekFor(int &validFor, std::string* opSequential, char character, std::list<std::string> TokensClasses);
std::list<std::string> SeekDo(int &validDo, std::string* opSequential, char character, std::list<std::string> TokensClasses);

// Check errors
bool ChecaValidos(char *validos, char character, int size_arr);

// verify reserverd words
std::list<std::string> seekReserved(int start, int end, std::fstream& File, std::list<std::string> TokensClasses, std::string* BracketComp, std::string* opCompRelational,
std::string* compSeparators,  std::string* declarator, std::string* opSequential, char *Digits);
