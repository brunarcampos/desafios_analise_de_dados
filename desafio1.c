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
         li.data[10] = '\0'; // garantir que esteja terminada com null
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

void resultado_final(double total_media_temperatura, char *dia_mais_quente, double temperatura_maxima, char *dia_mais_frio, double temperatura_minima, int dias_acima_30)
{
   // Gerar um relatório com todas essas respostas em arquivo TXT.
   FILE *arquivo = fopen("resultado.txt", "w");

   if (arquivo == NULL)
   {
      perror("Erro ao abrir o arquivo");
   }

   fprintf(arquivo, "Resultados: \n");
   fprintf(arquivo, "\nQual foi a temperatura média registrada durante os meses?\n");
   fprintf(arquivo, "Resposta: %f\n", total_media_temperatura);

   fprintf(arquivo, "\nQual foi o dia mais quente e o dia mais frio?\n");
   fprintf(arquivo, "Dia mais quente: %s com %.2f°C\n", dia_mais_quente, temperatura_maxima);
   fprintf(arquivo, "Dia mais frio: %s com %.2f°C\n", dia_mais_frio, temperatura_minima);

   fprintf(arquivo, "\nQuantos dias tiveram temperatura máxima acima de 30°C?\n"),
       fprintf(arquivo, "Resposta: %d dias\n", dias_acima_30);

   fclose(arquivo);
}

void calcular_dia_quente_e_frio(struct Linha linhas[], int total_linas, char *dia_mais_quente, char *dia_mais_frio, double *temperatura_maxima, double *temperatura_minima)
{
   // printf("Qual foi o dia mais quente e o dia mais frio?");
   *temperatura_maxima = linhas[1].temperatua_media;
   *temperatura_minima = linhas[1].temperatua_media;
   strcpy(dia_mais_quente, linhas[1].data);
   strcpy(dia_mais_frio, linhas[1].data);
   for (int i = 2; i <= total_linas; i++)
   {
      if (linhas[i].temperatua_media > *temperatura_maxima)
      {
         *temperatura_maxima = linhas[i].temperatua_media;
         strcpy(dia_mais_quente, linhas[i].data);
      }
      if (linhas[i].temperatua_media < *temperatura_minima)
      {
         *temperatura_minima = linhas[i].temperatua_media;
         strcpy(dia_mais_frio, linhas[i].data);
      }
   }
}

int calcular_temperatura_maxima(struct Linha linhas[], int total_linas)
{
   // printf("Quantos dias tiveram temperatura máxima acima de 30°C?");
   int temperatura_acima_30 = 0;
   for (int i = 1; i <= total_linas; i++)
   {
      if (linhas[i].temperatua_media > 30.0)
      {
         temperatura_acima_30 = temperatura_acima_30 + 1;
      }
   }
   return temperatura_acima_30;
}

double calcular_variacao_media_diaria()
{
   // printf("Qual foi a variação média diária (diferença entre máxima e mínima)?");
}

int main()
{
   setlocale(LC_ALL, "Portuguese");
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

      if (i == total_linas + 1)
      {
         break;
      }
   }

   // for (int x = 1; x <= total_linas; x++)
   //{
   //    printf("========= Nova linha {%d}\n", x);
   //    printf("Data: %s\n", linhas[x].data);
   //    printf("Temperatura media: %f\n", linhas[x].temperatua_media);
   //    printf("Umidade: %f\n", linhas[x].umidade);
   //    printf("Velocidade do vento: %f\n", linhas[x].velocidade_vento);
   //    printf("Pressão media: %f\n", linhas[x].pressao_media);
   // }

   double total_media_temperatura = calcular_media_temperatura(linhas);
   printf("Valor total: %.2f", total_media_temperatura);

   char dia_mais_frio[11], dia_mais_quente[11];
   double temperatura_maxima, temperatura_minima;
   calcular_dia_quente_e_frio(linhas, total_linas, dia_mais_quente, dia_mais_frio, &temperatura_maxima, &temperatura_minima);
   printf("\n Dia mais quente: %s com %.2f°C\n", dia_mais_quente, temperatura_maxima);
   printf("\n Dia mais frio: %s com %.2f°C\n", dia_mais_frio, temperatura_minima);

   int dias_acima_30 = calcular_temperatura_maxima(linhas, total_linas);
   printf("\n Dias com temperatura máxima acima de 30°C: %d\n", dias_acima_30);

   fclose(arquivo);

   resultado_final(total_media_temperatura, dia_mais_quente, temperatura_maxima, dia_mais_frio, temperatura_minima, dias_acima_30);

   return 0;
}
