#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

std::list<std::string> SeekLetters(int i, char *Letters, int Size, char character, std::list <std::string> TokensClasses, bool Found);
std::list<std::string> SeekDigits(int i, char *Letters, int Size, char character, std::list <std::string> TokensClasses, bool Found);
std::list<std::string> SeekSeparators(char *separators, int size, char character,std::list<std::string> TokensClasses);
std::list<std::string> SeekArithmetic(char *opArithmetic, int size, char character,std::list<std::string> TokensClasses);
std::list<std::string> SeekRelational(char *opRelational, int size, char character,std::list<std::string> TokensClasses);

int main(){
    //Criar uma função para idenficar cada um dos Tokens
    char Separadores[]{',', ':','_', ' ', '(', ')', '[', ']'};
    std::string BracketComp[]{"begin", "end"};
    std::string compSeparators[]{":=", "step", "until", "while", "comment"};
    char opArithmetic[]{'+', '-', '*', '/'};
    char opRelational[]{'<', '=', '>'};
    std::string opCompRelational[]{"<=", "!=", ">="};
    std::string declarator[]{"own", "integer", "array", "procedure"};
    std::string opSequential[] {"goto", "if", "then", "else", "for", "do"};
    char Letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char Digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    bool Found = false;

    std::list <std::string> TokensClasses; //Lista final do output

    std::fstream File;    //Criando o objeto (arquivo)
    File.open("algol.txt", std::ios_base::in);

    if(File.is_open()){
        char character;

        while(!File.eof()){
            File.get(character);
            TokensClasses=SeekLetters( 0, Letters, (sizeof(Letters)/sizeof(Letters[0])), character, TokensClasses, Found);
            TokensClasses= SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses);
            TokensClasses= SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses);
            TokensClasses= SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses);
        }
        //Verificar pq não está funcionando
        File.close();
        if(File.is_open()){
            std::cout << "Não foi possivel fechar o arquivo\n";
        }
    }

    for (auto i: TokensClasses)
    {
        std::cout << i;
    }

    return 0;
}

// Verifica se é uma letra
std::list<std::string> SeekLetters(int i, char *Letters, int Size, char character, std::list<std::string> TokensClasses, bool Found){
    if(i == Size){
        return TokensClasses;
    }else{
        if(character == Letters[i]){ //Faz parte do alfabeto
            std::string Classe = "\nLetra - ";
            Classe+=character;

            TokensClasses.push_back(Classe);
            Found = true;
            // std::cout << "Letra " << Letters[i] << " encontrada!\n";
        }
        return SeekLetters(i+1, Letters, Size, character, TokensClasses, Found);
    }
}

// Verifica se é um separador simples
std::list<std::string> SeekSeparators(char *separators, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == separators[i]){ //Faz parte dos separadores simples
            std::string Classe = "\nseparador - ";
            Classe+=character;

            TokensClasses.push_back(Classe);  
            // std::cout << "separador " << separators[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

// Verifica se é um operador aritmetico simples
std::list<std::string> SeekArithmetic(char *opArithmetic, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opArithmetic[i]){ //Faz parte dos operadores aritmeticos simples
            std::string Classe = "\nop aritmetico - ";
            Classe+=character;

            TokensClasses.push_back(Classe);  
            // std::cout << "operadore aritmetico " << opArithmetic[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

// Verifica se é um operador relacional simples
std::list<std::string> SeekRelational(char *opRelational, int size, char character,std::list<std::string> TokensClasses){
    for (int i = 0; i < size; i++){
        if(character == opRelational[i]){ //Faz parte dos operadores relacionais simples
            std::string Classe = "\nop relacional - ";
            Classe+=character;

            TokensClasses.push_back(Classe);  
            //std::cout << "operador relacional " << opRelational[i] << " encontrado!\n";
        }
    }
    return TokensClasses;
}

std::list<std::string> SeekDigits(int i, char *Letters, int Size, char character, std::list <std::string> TokensClasses, bool Found){
    
}