#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){
   FILE *arquivo;
   arquivo = fopen("desafio_1.csv", " ");
   char linha[1600];
   if(arquivo = NULL){
    perror("Erro ao abrir o arquivo");
    return 1;
   } 

   return 0;
}