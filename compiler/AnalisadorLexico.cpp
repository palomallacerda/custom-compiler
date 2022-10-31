#include <iostream>
#include <fstream>
#include "header.h"
#include "FuncoesSimples.cpp"
#include "VerificadorReservadas.cpp"

std::list<Token> TokensClasses; //Lista final do output

bool Analisador_Lexico(){
    char separators[]{',', ':','_', '(', ')', '[', ']', ' ', ';', '!'};
    char opArithmetic[]{'+', '-', '*', '/'};
    char opRelational[]{'<', '=', '>'};
    char Letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char Digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char ignore[]{'\n', '\t'};

    std::string BracketComp[]{"begin", "end"};
    std::string compSeparators[]{":=", "step", "until", "while", "comment"}; //:= pode ser : ou :=
    std::string opCompRelational[]{"<=", "!=", ">="};
    std::string declarator[]{"own", "integer", "array", "procedure"};
    std::string opSequential[] {"goto", "if", "then", "else", "for", "do"}; //'e' pode ser end ou else

    int start, end;
    bool s_sep;

    std::fstream File;    //Criando o objeto (arquivo)
    File.open("arquivos/algol.txt", std::ios_base::in);

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
                std::cout << "Caracter desconhecido: " << character << std::endl;
                return false;
            }
        }
        File.clear();
        File.seekg(0);
        //salva a posição inicial do arquivo
        start = File.tellg();

        while(!File.eof())
        {
            File.get(character);

            if (character == '<' || character == '>' || character == '!' || character == ':'){
                char next; 
                Token Classe;

                if (character == ':'){
                    Classe.tipo = "Separador";
                    Classe.rotulo += character;
                }
                else {
                    Classe.tipo = "Operador relacional";
                    Classe.rotulo += character;
                }

                end = File.tellg();
                File.get(next);

                if (next == '='){
                    Classe.rotulo += next;
                    File.seekg(start);

                    TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential, Digits);
                    start = end + 1;

                    File.seekg(end + 1);
                    TokensClasses.push_back(Classe);
                }
                else{
                    File.seekg(start);

                    TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential, Digits);
                    start = end;
                    File.seekg(end);
                    TokensClasses.push_back(Classe);
                }
            }
            //verifica se é um separador
            else  if(SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses)){
                // salva a posição do separador
                end = File.tellg();

                // volta o ponteiro do arquivo para a posição start
                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential, Digits);

                // seta o start para a posição de end(ou seja voltou para onde tinha chamando seekReserved)
                start = end;

                File.get(character);
                if (character != ' '){
                    Token Classe;
                    switch (character)
                    {
                    case '(':
                        Classe.tipo = "SepAbPar";
                        break;
                    case ')':
                        Classe.tipo = "SepFePar";
                        break;
                    case '[':
                        Classe.tipo = "SepAbCoch";
                        break;
                    case ']':
                        Classe.tipo = "SepFeCoch";
                        break;
                    default:
                        Classe.tipo = "Separador";
                        break;
                    }
                    Classe.rotulo += character;
                    TokensClasses.push_back(Classe);
                }
            }
            else if (SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses)){
                end = File.tellg();

                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential, Digits);
                start = end;

                Token Classe;
                Classe.tipo = "Operador aritmetico";
                File.get(character);
                File.seekg(end);
                Classe.rotulo = character;
                TokensClasses.push_back(Classe);
            }
            else if (SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses)){
                end = File.tellg();

                File.seekg(start);

                TokensClasses = seekReserved(start, end, File, TokensClasses, BracketComp, opCompRelational, compSeparators, declarator, opSequential, Digits);
                start = end;

                Token Classe;
                Classe.tipo = "Operador relacional";
                File.get(character);
                Classe.rotulo = character;
                TokensClasses.push_back(Classe);
            }
        }
        File.close();
        if(File.is_open())
        {
            std::cout << "Não foi possivel fechar o arquivo\n";
        }
    }
    Token Classe;
    Classe.tipo = "Fim";
    Classe.rotulo = "$";
    TokensClasses.push_back(Classe);

    //Imprimindo lista com os tokens Finais
    for (auto i: TokensClasses)
    {
            std::cout << i.tipo << " - " << i.rotulo << std::endl;
    }

    return true;
}

std::list<Token> TokensLexico(){ //Metodo para retornar tokens lexicos
    return TokensClasses;
}

bool ChecaValidos(char *validos, char character, int size_arr){
    //Procura por caracteres que não estão na gramática
    for (int i = 0; i < size_arr; i++)
    {
        if (validos[i] == character)
        {
            return true;
        }
    }
    return false;
}