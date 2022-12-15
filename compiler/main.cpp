#include <iostream>
#include <fstream>
#include <vector>
#include "AnalisadorLexico.cpp"
// #include "AnalisadorSintdr.cpp"
#include "miniStd.cpp"

int main(){
    bool flag_lexico = true;
    std::vector<Token> ClassesTokens;

    flag_lexico = Analisador_Lexico();

    if (!flag_lexico) //Caso der erro no analisador léxico, ele termina o programa
    {
        std::cout << "Erro na análise léxica" << std::endl;
        exit(0);
    }

    ClassesTokens = TokensLexico();   
    ClassesTokens = inicialState(ClassesTokens);

//    if(ClassesTokens.empty()){
//         std::cout << "Análise Sintática concluida com sucesso" << std::endl;
//     }else{
//     // std::cout << "PILHA DPS DO SINTATICO" << std::endl;
//     // for (auto i : ClassesTokens){
//     //     std::cout << i.rotulo << " - " << i.tipo << std::endl;
//     // }
//     std::cout << "Análise Sintática não foi concluida com sucesso" << std::endl;
//    }

   return 0;
}