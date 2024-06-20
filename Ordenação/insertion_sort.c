#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_MAX_COD_MUN 5
#define TAM_MAX_NOME 40

struct dados
{
    char uf[3];
    char cod_uf[5];
    char cod_mun[TAM_MAX_COD_MUN];
    char nome[TAM_MAX_NOME];
    int populacao;
};

void insertionSort(struct dados *list[], int n) {
    int i, j; // Declara as variáveis de iteração
    struct dados *next; // Declara um ponteiro para a estrutura que será inserida na posição correta

    for (i = 1; i < n; i++) { // Percorre a lista a partir do segundo elemento até o final
        next = list[i]; // Armazena o elemento atual em `next`
        
        // Encontra a posição correta para `next` movendo os elementos maiores para a direita
        for (j = i - 1; j >= 0 && next->populacao < list[j]->populacao; j--) {
            list[j + 1] = list[j]; // Move o elemento `list[j]` uma posição para a direita
        }
        
        list[j + 1] = next; // Insere `next` na posição correta
    }
}


int main(){
    struct dados dados[5571];
    // para poder mexer com array escrever assim
    struct dados *dados_ptrs[5571];
    FILE *fp = fopen("estimativa_dou_2021.csv", "r");
    if(fp == NULL){
        puts("Arquivo não encontrado\n");
        system("pause");
        exit(0);
    }

    FILE *ff = fopen("arquivo_ordenado_insercao", "w");
    if(ff == NULL){
        puts("Arquivo não criado\n");
        system("pause");
        exit(0);
    }


    if(fp != NULL){
        
        char primeiralinha[100]; // Lê a primeira linha do arquivo e armazena em primeiralinha
        fscanf(fp, "%[^\n]\n", primeiralinha);
        int i = 0;

        while(!feof(fp)){
                fscanf(fp, "%[^;];%2[^;];%[^;];%[^;];%d",
                dados[i].uf,
                dados[i].cod_uf,
                dados[i].cod_mun,
                dados[i].nome,
                &dados[i].populacao);
                dados_ptrs[i] = &dados[i];
                i++;
        }

        // mecanismo para benchmarking
        clock_t start_time = clock();

        insertionSort(dados_ptrs,i);//função avaliada no benchmarking

        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("Done in %f seconds\n", elapsed_time);
        //fim do mecanismo

    // tá assim por mexer com array
        for(int j = 0 ; j < i ; j++){
            fprintf(ff, "%s;%s;%s;%s;%d\n",
            dados_ptrs[j]->uf,
            dados_ptrs[j]->cod_uf,
            dados_ptrs[j]->cod_mun,
            dados_ptrs[j]->nome,
            dados_ptrs[j]->populacao);
        }

    
        fclose(ff);
        fclose(fp);
        return 0;


    }
}