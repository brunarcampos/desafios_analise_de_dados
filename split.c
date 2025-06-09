#include <stdio.h>
#include <string.h>

int main(){
    char linha[] = "caqui,laranja,banana";
    const char virgula[2] = ",";

    char *token = strtok(linha, virgula);
    

    while(token != NULL){
        printf("token: %s\n", token);
        token = strtok(NULL, virgula);
    }
    return 0;
}
