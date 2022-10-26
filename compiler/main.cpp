#include <iostream>
#include <fstream>
#include "AnalisadorLexico.cpp"
#include "AnalisadorSintdr.cpp"

int main() {
    bool flag_lexico = true;
    std::list<Token> ClassesTokens;

    flag_lexico = Analisador_Lexico();

    if (!flag_lexico) //Caso der erro no analisador léxico, ele termina o programa
    {
        std::cout << "Erro na análise léxica" << std::endl;
        exit(0);
    }

   ClassesTokens = TokensLexico();

   ClassesTokens = InicialState(ClassesTokens);

   if(ClassesTokens.empty()){
    std::cout << "Análise Sintática concluida com sucesso" << std::endl;
   }
   else{
    
   }
}
