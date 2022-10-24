#include <iostream>
#include <fstream>
#include "AnalisadorLexico.cpp"

int main() {
    bool flag_lexico = true;
    flag_lexico = Analisador_Lexico();

    if (!flag_lexico) //Caso der erro no analisador léxico, ele termina o programa
    {
        std::cout << "Erro na análise léxica" << std::endl;
        exit(0);
    }
}
