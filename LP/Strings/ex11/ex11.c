#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>

char palavrasecreta[20];
char chutes[26];
int chutasdados = 0;

void abertura(){
    printf("\n");
    printf("****************\n");
    printf("* Jogo de Forca *\n");
    printf("****************\n\n");
}

void adicionapalavra(){

  char quer;
  printf("Você deseja adicionar alguma palavra nova?: (S/N)");
  scanf(" %c", &quer);

  if(quer == 'S'){
    char novapalavra[20];
    printf("Digite a nova palavra: ");
    scanf("%s", &novapalavra);

    FILE* f;
    f = fopen("palavras.txt", "r+");
    if(f == 0){
      printf("Banco de dados indisponivel\n\n");
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
}

void escolhepalavra(){
  FILE* f;
  
  f = fopen("palavras.txt", "r");
  if(f == 0){
    printf("Banco de dados não disponível.\n\n");
    exit(1);
  }

  int qtddepalavras;
  fscanf(f, "%d", &qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for(int i = 0; i <= randomico; i++){
    fscanf(f, "%s", &palavrasecreta);
  }


  fclose(f);
}


int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutasdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca(){
  for(int i = 0; i < strlen(palavrasecreta); i++) {
            
    int achou = jachutou(palavrasecreta[i]);

      if(achou) {
        printf("%c ", palavrasecreta[i]);
      } else {
        printf("_ ");
      }
  }
    printf("\n");
}

void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutasdados] = chute;
    chutasdados++;
}

int acertou(){
  for(int i = 0; i < strlen(palavrasecreta); i++){
    if(!jachutou(palavrasecreta[i])){
      return 0;
    }
  }
  return 1;
}

int enforcou(){
  
  int erros = 0;

  for(int i = 0; i < chutasdados; i++){
    int existe = 0;

    for(int j = 0; j < strlen(palavrasecreta); j++){
      if(chutes[i] == palavrasecreta[j]){
        existe = 1;
        break;
      }
    }

    if(!existe) erros++;
  }

  return erros >= 5;
}

int main() {
    
    escolhepalavra();
    abertura();

    do {

      desenhaforca();
      chuta();
      
    } while (!acertou() && !enforcou());
    adicionapalavra();
}
