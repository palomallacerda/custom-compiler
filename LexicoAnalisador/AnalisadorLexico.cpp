
#include <iostream>
#include <fstream>

#include "FuncoesCompostas.cpp"
#include "FuncoesSimples.cpp"
#include "ChecaErros.cpp"

/* TODO
- A função foi colocada aqui pq deu problema com o header fiquei puto e botei aqui
    tem que descomentar do VerificadorReservadas.cpp e ajeitar as importações;
- Falta analisar os casos dos separadores compostos (Só analisar uma posição afrente
    já que todos compostos são de tamanho 2);
- Os identificadores que não são reservados tão meio bugados talvez seja o caso de 
    analisar caso tenham dois separadores distintos seguidos;
*/


std::list<std::string> seekReserved(int start, int end, std::fstream& File, std::list<std::string> TokensClasses, std::string* BracketComp, std::string* opCompRelational,
std::string* compSeparators,  std::string* declarator, std::string* opSequential){
    int validBegin{-1};
    int validEnd{-1};
    int validAssigment{-1};
    int validStep{-1};
    int validUntil{-1};
    int validWhile{-1};
    int validComment{-1};
    int validMenorIgual{-1};
    int validDiferente{-1};
    int validMaiorIgual{-1};
    int validOwn{-1};
    int validInt{-1};
    int validArray{-1};
    int validProcedure{-1};
    int validGoto{-1};
    int validIf{-1};
    int validThen{-1};
    int validElse{-1};
    int validFor{-1};
    int validDo{-1};

    bool found = false;
    std::string id;

    File.seekg(start);

    while(!File.eof()){
        if (File.tellg() == end-1){
            break;
        }
        char character;
        File.get(character);
        id += character;

        if(character=='<' || validMenorIgual>=0){
            TokensClasses=SeekMenorIgual(validMenorIgual, opCompRelational, character, TokensClasses);
            if(validMenorIgual == 1) {
                found = true;
            }
        }
        if(character=='!' || validDiferente>=0){
            TokensClasses=SeekDiferente(validDiferente, opCompRelational, character, TokensClasses);
            if(validDiferente == 1) {
                found = true;
            }
        }
        if(character=='>' || validMaiorIgual>=0){
            TokensClasses=SeekMaiorIgual(validMaiorIgual, opCompRelational, character, TokensClasses);
            if(validMaiorIgual == 1) {
                found = true;
            }
        }
        // Verificação dos caracteres Compostos
        if(character == 'b' || validBegin >=0){
            TokensClasses=SeekBegin(validBegin, BracketComp,character, TokensClasses);
            if(validBegin == 4) {
                found = true;
            }
        }
        if(character == 'e' || validEnd >=0){
            TokensClasses=SeekEnd(validEnd, BracketComp, character, TokensClasses);
            if(validEnd == 2) {
                found = true;
            }
        }
        if(character == ':' || validAssigment >= 0){
            TokensClasses=SeekAssigment(validAssigment, compSeparators, character, TokensClasses);
            if(validAssigment == 1) {
                found = true;
            }
        }
        if(character == 's' || validStep >= 0){
            TokensClasses=SeekStep(validStep, compSeparators, character, TokensClasses);
            if(validStep == 3) {
                found = true;
            }
        }
        if(character == 'u' || validUntil >=0){
            TokensClasses=Seekuntil(validUntil, compSeparators, character, TokensClasses);
            if(validUntil == 4) {
                found = true;
            }
        }
        if(character=='w' || validWhile>=0){
            TokensClasses=SeekWhile(validWhile,compSeparators, character, TokensClasses);
            if(validWhile == 4) {
                found = true;
            }
        }
        if(character=='c' || validComment>=0){
            TokensClasses=SeekComment(validComment, compSeparators, character, TokensClasses);
            if(validComment == 6) {
                found = true;
            }
        }
        
        if(character=='o' || validOwn>=0){
            TokensClasses=SeekOwn(validOwn, declarator, character, TokensClasses);
            if(validOwn == 1) {
                found = true;
            }
        }
        if(character=='i' || validInt >=0){
            TokensClasses=SeekInteger(validInt, declarator, character, TokensClasses);
            if(validInt == 6) {
                found = true;
            }
        }
        if(character=='a' || validArray >=0){
            TokensClasses=SeekArray(validArray, declarator, character, TokensClasses);
            if(validArray == 4) {
                found = true;
            }
        }
        if(character=='p' || validProcedure >=0){
            TokensClasses=SeekProcedure(validProcedure, declarator, character, TokensClasses);
            if(validArray == 8) {
                found = true;
            }
        }
        if(character=='g' || validGoto >=0){
            TokensClasses=SeekGoto(validGoto, opSequential, character, TokensClasses);
            if(validGoto == 3) {
                found = true;
            }
        }
        if(character=='i' || validIf >=0){
            TokensClasses=SeekIf(validIf, opSequential, character, TokensClasses);
            if(validIf == 1) {
                found = true;
            }
        }
        if(character=='t' || validThen >=0){
            TokensClasses=SeekThen(validThen, opSequential, character, TokensClasses);
            if(validThen == 3) {
                found = true;
            }
        }
        if(character=='e' || validElse >=0){
            TokensClasses=SeekElse(validElse, opSequential, character, TokensClasses);
            if(validElse == 3) {
                found = true;
            }
        }
        if(character=='f' || validFor >=0){
            TokensClasses=SeekFor(validFor, opSequential, character, TokensClasses);
            if(validFor == 2) {
                found = true;
            }
        }
        if(character=='d' || validDo >=0){
            TokensClasses=SeekDo(validDo, opSequential, character, TokensClasses);
            if(validDo == 1) {
                found = true;
            }
        }
    }

    if(found == false){
        TokensClasses.push_back("Identidicador - " + id);
    }

    return TokensClasses;
}

int main(){
    char separators[]{',', ':','_', '(', ')', '[', ']', ' '};
    char opArithmetic[]{'+', '-', '*', '/'};
    char opRelational[]{'<', '=', '>'};
    char Letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char Digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char ignore[]{' ', '\n', ';'};

    std::string BracketComp[]{"begin", "end"};
    std::string compSeparators[]{":=", "step", "until", "while", "comment"}; //:= pode ser : ou :=
    std::string opCompRelational[]{"<=", "!=", ">="};
    std::string declarator[]{"own", "integer", "array", "procedure"};
    std::string opSequential[] {"goto", "if", "then", "else", "for", "do"}; //'e' pode ser end ou else

    int start, end;
    bool s_sep;

    std::list<std::string> TokensClasses; //Lista final do output,,,,

    std::fstream File;    //Criando o objeto (arquivo)
    File.open("algol.txt", std::ios_base::in);

    if(File.is_open()){
        char character;

        // Checa o arquivo por caracteres estranhos
        while(!File.eof())
        {
            File.get(character);
            bool flag = false;

            if(ChecaValidos(Letters, character, sizeof(Letters)/ sizeof(Letters[0])))
            {
                continue;
            }
            if(ChecaValidos(Digits, character, sizeof(Digits)/ sizeof(Digits[0])))
            {
                continue;
            }
            if(ChecaValidos(separators, character, sizeof(separators)/ sizeof(separators[0])))
            {
                continue;
            }
            if(ChecaValidos(opArithmetic, character, sizeof(opArithmetic)/ sizeof(opArithmetic[0])))
            {
                continue;
            }
            if(ChecaValidos(opRelational, character, sizeof(opRelational)/ sizeof(opRelational[0])))
            {
                continue;
            }
            if(ChecaValidos(ignore, character, sizeof(opRelational)/ sizeof(opRelational[0])))
            {
                continue;
            }
            if (!flag)
            {
                std::cout << "Error on --- " << character << std::endl;
                exit(1);
            }
        }

        File.clear();
        File.seekg(0);
        start = File.tellg();

        while(!File.eof())
        {
            File.get(character);
            
            
            if (SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses)){
                end = File.tellg();
                File.seekg(start);
                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                start = File.tellg();
                std::string Classe = "\nseparador - ";
                File.get(character);
                Classe += character;
                TokensClasses.push_back(Classe);  
            }
            else if (SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses)){
                end = File.tellg();
                File.seekg(start);
                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                start = File.tellg();
                std::string Classe = "\noperador aritmetico - ";
                File.get(character);
                Classe += character;
                TokensClasses.push_back(Classe);  
            }
            else if (SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses)){
                end = File.tellg();
                File.seekg(start);
                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                start = File.tellg();  
                std::string Classe = "\noperador relacional - ";
                File.get(character);
                Classe += character;     
                TokensClasses.push_back(Classe);      
            }

            // Verificação dos caracteres simples
            // TokensClasses=SeekLetters(0, Letters, (sizeof(Letters)/sizeof(Letters[0])), character, TokensClasses);
            // TokensClasses=SeekDigits(Digits, (sizeof(Digits)/sizeof(Digits[0])), character, TokensClasses);
            
        }
        File.close();
        if(File.is_open())
        {
            std::cout << "Não foi possivel fechar o arquivo\n";
        }
    }

    //Imprimindo lista com os tokens Finais
    for (auto i: TokensClasses)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
