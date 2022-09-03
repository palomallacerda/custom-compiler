
#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

std::list<std::string> SeekLetters(int i, char *Letters, int Size, char Caracter, std::list <std::string> TokensClasses, bool Found);

int main(){ 
    //Criar uma função para idenficar cada um dos Tokens
    char Separadores[]{',', ':','_', ' ', '(', ')', '[', ']'};
    std::string BracketComp[]{"begin", "end"};
    std::string SeparadoresComp[]{":=", "step", "until", "while", "comment"};
    char Op_Aritimeticos[]{'+', '-', '*', '/'};
    char Op_Relacionais_simples[]{'<', '=', '>'};
    std::string Op_RelacionaisComp[]{"<=", "!=", ">="};
    std::string Declarador[]{"own", "integer", "array", "procedure"};
    std::string Op_Sequenciais[] {"goto", "if", "then", "else", "for", "do"};
    char Letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char Digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    bool Found = false;

    std::list <std::string> TokensClasses; //Lista final do output
    
    std::fstream File;    //Criando o objeto (arquivo)
    File.open("algol.txt", std::ios_base::in);

    if(File.is_open()){
        char Caracter;

        while(!File.eof()){
            File.get(Caracter);
            TokensClasses=SeekLetters( 0, Letters, (sizeof(Letters)/sizeof(Letters[0])), Caracter, TokensClasses, Found);
        }
        //Verificar pq não está funcionando 
        File.close();
        if(File.is_open()){
            std::cout << "Não foi possivel fechar o arquivo\n";
        }
    }

    for (std::string Letra: TokensClasses)
    {
        std::cout << Letra;
    }
    
    
    return 0;
}
std::list<std::string> SeekLetters(int i, char *Letters, int Size, char Caracter, std::list<std::string> TokensClasses, bool Found){
    if(i == Size){
        return TokensClasses;
    }else{
        if(Caracter == Letters[i]){ //Faz parte do alfabeto
            std::string Classe = "\nLetra - ";
            Classe+=Caracter;

            TokensClasses.push_back(Classe);  
            Found = true;            
            // std::cout << "Letra " << Letters[i] << " encontrada!\n";
        }
        return SeekLetters(i+1, Letters, Size, Caracter, TokensClasses, Found);
    }
}