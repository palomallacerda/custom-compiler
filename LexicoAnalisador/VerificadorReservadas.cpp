// #include <fstream>
// #include "FuncoesCompostas.cpp"


// void seekReserved(int start, int end, std::fstream& File, std::list<std::string> TokensClasses, std::string* BracketComp, std::string* opCompRelational,
// std::string* compSeparators,  std::string* declarator, std::string* opSequential){
//     int validBegin{-1};
//     int validEnd{-1};
//     int validAssigment{-1};
//     int validStep{-1};
//     int validUntil{-1};
//     int validWhile{-1};
//     int validComment{-1};
//     int validMenorIgual{-1};
//     int validDiferente{-1};
//     int validMaiorIgual{-1};
//     int validOwn{-1};
//     int validInt{-1};
//     int validArray{-1};
//     int validProcedure{-1};
//     int validGoto{-1};
//     int validIf{-1};
//     int validThen{-1};
//     int validElse{-1};
//     int validFor{-1};
//     int validDo{-1};

//     while(!File.eof()){
//         if (File.tellg() == end){
//             break;
//         }
//         char character;
//         File.get(character);

//         if(character=='<' || validMenorIgual>=0){
//             TokensClasses=SeekMenorIgual(validMenorIgual, opCompRelational, character, TokensClasses);
//         }
//         if(character=='!' || validDiferente>=0){
//             TokensClasses=SeekDiferente(validDiferente, opCompRelational, character, TokensClasses);
//         }
//         if(character=='>' || validMaiorIgual>=0){
//             TokensClasses=SeekMaiorIgual(validMaiorIgual, opCompRelational, character, TokensClasses);
//         }
//         // Verificação dos caracteres Compostos
//         if(character == 'b' || validBegin >=0){
//             TokensClasses=SeekBegin(validBegin, BracketComp,character, TokensClasses);
//         }
//         if(character == 'e' || validEnd >=0){
//             TokensClasses=SeekEnd(validEnd, BracketComp, character, TokensClasses);
//         }
//         if(character == ':' || validAssigment >= 0){
//             TokensClasses=SeekAssigment(validAssigment, compSeparators, character, TokensClasses);
//         }
//         if(character == 's' || validStep >= 0){
//             TokensClasses=SeekStep(validStep, compSeparators, character, TokensClasses);
//         }
//         if(character == 'u' || validUntil >=0){
//             TokensClasses=Seekuntil(validUntil, compSeparators, character, TokensClasses);
//         }
//         if(character=='w' || validWhile>=0){
//             TokensClasses=SeekWhile(validWhile,compSeparators, character, TokensClasses);
//         }
//         if(character=='c' || validComment>=0){
//             TokensClasses=SeekComment(validComment, compSeparators, character, TokensClasses);
//         }
        
//         if(character=='o' || validOwn>=0){
//             TokensClasses=SeekOwn(validOwn, declarator, character, TokensClasses);
//         }
//         if(character=='i' || validInt >=0){
//             TokensClasses=SeekInteger(validInt, declarator, character, TokensClasses);
//         }
//         if(character=='a' || validArray >=0){
//             TokensClasses=SeekArray(validArray, declarator, character, TokensClasses);
//         }
//         if(character=='p' || validProcedure >=0){
//             TokensClasses=SeekProcedure(validProcedure, declarator, character, TokensClasses);
//         }
//         if(character=='g' || validGoto >=0){
//             TokensClasses=SeekGoto(validGoto, opSequential, character, TokensClasses);
//         }
//         if(character=='i' || validIf >=0){
//             TokensClasses=SeekIf(validIf, opSequential, character, TokensClasses);
//         }
//         if(character=='t' || validThen >=0){
//             TokensClasses=SeekThen(validThen, opSequential, character, TokensClasses);
//         }
//         if(character=='e' || validElse >=0){
//             TokensClasses=SeekElse(validElse, opSequential, character, TokensClasses);
//         }
//         if(character=='f' || validFor >=0){
//             TokensClasses=SeekFor(validFor, opSequential, character, TokensClasses);
//         }
//         if(character=='d' || validDo >=0){
//             TokensClasses=SeekDo(validDo, opSequential, character, TokensClasses);
//         }
//     }
// }