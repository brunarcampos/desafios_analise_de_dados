#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Linha
{
   char data[11];
   double temperatua_media;
   double umidade;
   double velocidade_vento;
   double pressao_media;
};

struct Linha pegar_dados(char linha[100])
{
   const char virgula[4] = ",";
   char *token = strtok(linha, virgula);
   struct Linha li;
   int i = 1;
   while (token != NULL)
   {
      if (i == 1)
      {
         strncpy(li.data, token, 10);
         li.data[10] = '\0';  // garantir que esteja terminada com null
      }
      else if (i == 2)
      {
         li.temperatua_media = atof(token);
      }
      else if (i == 3)
      {
         li.umidade = atof(token);
      }
      else if (i == 4)
      {
         li.velocidade_vento = atof(token);
      }
      else if (i == 5)
      {
         li.pressao_media = atof(token);
      }
      token = strtok(NULL, virgula);
      i = i + 1;
   }

   return li;
}

double calcular_media_temperatura(struct Linha linhas[1576])
{
   // printf("Qual foi a temperatura média registrada durante os meses?");
   int i;
   double total = 0;

   for (i = 1; i <= 1576; i++)
   {
      total = total + linhas[i].temperatua_media;
   }

   return total / 1576;
}

int main()
{
   FILE *arquivo;
   arquivo = fopen("Original.csv", "r");

   int total_linas = 1576;
   struct Linha linhas[total_linas];

   int i = 0;
   while (!feof(arquivo))
   {
      char linha[100];
      char *result = fgets(linha, 100, arquivo);

      if (i == 0)
      {
         i++;
         continue;
      }
      struct Linha li = pegar_dados(linha);
      linhas[i] = li;
      i++;

      if (i == total_linas)
      {
         break;
      }
   }

   for (int x = 1; x <= total_linas; x++)
   {
      printf("========= Nova linha {%d}\n", x);
      printf("Data: %s\n", linhas[x].data);
      printf("Temperatura media: %f\n", linhas[x].temperatua_media);
      printf("Umidade: %f\n", linhas[x].umidade);
      printf("Velocidade do vento: %f\n", linhas[x].velocidade_vento);
      printf("Pressão media: %f\n", linhas[x].pressao_media);
   }

   double total = calcular_media_temperatura(linhas);
   printf("Valor total: %f", total);
   fclose(arquivo);

   // printf("Qual foi o dia mais quente e o dia mais frio?");
   // printf("Quantos dias tiveram temperatura máxima acima de 30°C?");
   // printf("Qual foi a variação média diária (diferença entre máxima e mínima)?");
   // Gerar um relatório com todas essas respostas em arquivo TXT.

   return 0;
}
