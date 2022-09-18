
#include <iostream>
#include <fstream>

// #include "FuncoesCompostas.cpp"
#include "FuncoesSimples.cpp"
#include "ChecaErros.cpp"
<<<<<<< HEAD
#include "VerificadorReservadas.cpp"
/* TODO
- Falta analisar os casos dos separadores compostos (Só analisar uma posição afrente
    já que todos compostos são de tamanho 2);
- Os digitos não estão sendo considerados como números;
*/
=======
>>>>>>> main

int main(){
    char separators[]{',', ':','_', '(', ')', '[', ']', ' ', ';'};
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
<<<<<<< HEAD
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
        //salva a posição inicial do arquivo
        start = File.tellg();

        while(!File.eof())
        {
            File.get(character);

            //verifica se é um separador
            if (SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses)){
                // salva a posição do separador
                end = File.tellg();

                // volta o ponteiro do arquivo para a posição start
                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                
                // seta o start para a posição de end(ou seja voltou para onde tinha chamando seekReserved)
                start = end;

                File.get(character);
                if (character != ' '){
                    std::string Classe = "\nSeparador - ";
                    Classe += character;
                    TokensClasses.push_back(Classe);
                }
            }
            else if (SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses)){
                end = File.tellg();

                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                start = end;

                std::string Classe = "\noperador aritmetico - ";
                File.get(character);
                Classe += character;
                TokensClasses.push_back(Classe);
            }
            else if (SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses)){
                end = File.tellg();

                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential);
                
                start = end;

                std::string Classe = "\noperador relacional - ";
                File.get(character);
                Classe += character;
                TokensClasses.push_back(Classe);
            }

            // Verificação dos caracteres simples
            // TokensClasses=SeekLetters(0, Letters, (sizeof(Letters)/sizeof(Letters[0])), character, TokensClasses);
            // TokensClasses=SeekDigits(Digits, (sizeof(Digits)/sizeof(Digits[0])), character, TokensClasses);
=======
            if(CheackUpperCase(character) && ChecaValidos(separators, character) || ChecaValidos(opArithmetic, character) || ChecaValidos(opRelational, character) || 
            ChecaValidos(Letters, character)|| ChecaValidos(Digits, character)){
                 // Verificação dos caracteres Compostos
                if(character == 'b' || validBegin >=0){
                    TokensClasses=SeekBegin(validBegin, BracketComp,character, TokensClasses);
                }
                if(character == 'e' || validEnd >=0){
                    TokensClasses=SeekEnd(validEnd, BracketComp, character, TokensClasses);
                }
                if(character == ':' || validAssigment >= 0){
                    TokensClasses=SeekAssigment(validAssigment, compSeparators, character, TokensClasses);
                }
                if(character == 's' || validStep >= 0){
                    TokensClasses=SeekStep(validStep, compSeparators, character, TokensClasses);
                }
                if(character == 'u' || validUntil >=0){
                    TokensClasses=Seekuntil(validUntil, compSeparators, character, TokensClasses);
                }
                if(character=='w' || validWhile>=0){
                    TokensClasses=SeekWhile(validWhile,compSeparators, character, TokensClasses);
                }
                if(character=='c' || validComment>=0){
                    TokensClasses=SeekComment(validComment, compSeparators, character, TokensClasses);
                }
                if(character=='<' || validMenorIgual>=0){
                    TokensClasses=SeekMenorIgual(validMenorIgual, opCompRelational, character, TokensClasses);
                }
                if(character=='!' || validDiferente>=0){
                    TokensClasses=SeekDiferente(validDiferente, opCompRelational, character, TokensClasses);
                }
                if(character=='>' || validMaiorIgual>=0){
                    TokensClasses=SeekMaiorIgual(validMaiorIgual, opCompRelational, character, TokensClasses);
                }
                if(character=='o' || validOwn>=0){
                    TokensClasses=SeekOwn(validOwn, declarator, character, TokensClasses);
                }
                if(character=='i' || validInt >=0){
                    TokensClasses=SeekInteger(validInt, declarator, character, TokensClasses);
                }
                if(character=='a' || validArray >=0){
                    TokensClasses=SeekArray(validArray, declarator, character, TokensClasses);
                }
                if(character=='p' || validProcedure >=0){
                    TokensClasses=SeekProcedure(validProcedure, declarator, character, TokensClasses);
                }
                if(character=='g' || validGoto >=0){
                    TokensClasses=SeekGoto(validGoto, opSequential, character, TokensClasses);
                }
                if(character=='i' || validIf >=0){
                    TokensClasses=SeekIf(validIf, opSequential, character, TokensClasses);
                }
                if(character=='t' || validThen >=0){
                    TokensClasses=SeekThen(validThen, opSequential, character, TokensClasses);
                }
                if(character=='e' || validElse >=0){
                    TokensClasses=SeekElse(validElse, opSequential, character, TokensClasses);
                }
                if(character=='f' || validFor >=0){
                    TokensClasses=SeekFor(validFor, opSequential, character, TokensClasses);
                }
                if(character=='d' || validDo >=0){
                    TokensClasses=SeekDo(validDo, opSequential, character, TokensClasses);
                }

                // Verificação dos caracteres simples
                TokensClasses=SeekLetters(0, Letters, (sizeof(Letters)/sizeof(Letters[0])), character, TokensClasses);
                TokensClasses=SeekDigits(Digits, (sizeof(Digits)/sizeof(Digits[0])), character, TokensClasses);
                TokensClasses=SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses);
                TokensClasses=SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses);
                TokensClasses=SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses);
            }
            else{
                std::cout << "Erro On --- " << character << std::endl;
                exit(1);
            }
            
>>>>>>> main
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
