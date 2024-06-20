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

int smallerIndex(struct dados populacao[], int tam, int ini) {
    int min = ini, j; // Inicializa `min` com o índice `ini` e declara `j`
    for (j = ini + 1; j < tam; j++) { // Percorre os elementos a partir de `ini + 1` até o final do array
        if (populacao[j].populacao > populacao[min].populacao) // Compara a população no índice `j` com a população no índice `min`
            min = j; // Atualiza `min` se encontrar uma população maior
    }
    return min; // Retorna o índice do maior elemento encontrado
}


void ordenaPopulacao(struct dados *populacao, int tam) {
    int i, min, aux; // Declara variáveis para iteração, armazenamento do índice mínimo e variável auxiliar
    for (i = 0; i < tam; i++) { // Percorre todos os elementos do array
        min = smallerIndex(populacao, tam, i); // Chama `smallerIndex` para encontrar o índice do maior elemento a partir de `i`
        
        // Troca os elementos nas posições `i` e `min`
        aux = populacao[i].populacao; // Armazena temporariamente a população do elemento na posição `i`
        populacao[i] = populacao[min]; // Coloca o elemento da posição `min` na posição `i`
        populacao[min].populacao = aux; // Coloca a população armazenada temporariamente na posição `min`
    }
}



int main(){
    struct dados dados[5571];
    FILE *fp = fopen("estimativa_dou_2021.csv", "r");
    if(fp == NULL){
        puts("Arquivo não encontrado\n");
        system("pause");
        exit(0);
    }

    FILE *ff = fopen("arquivo_ordenado_selecao", "w");
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
                i++;
        }
        
        // mecanismo para benchmarking
        clock_t start_time = clock();

        ordenaPopulacao(dados, i);//função avaliada no benchmarking

        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("Done in %f seconds\n", elapsed_time);
        //fim do mecanismo

        for(int j = 0 ; j < i ; j++){
            fprintf(ff, "%s;%s;%s;%s;%d\n",
            dados[j].uf,
            dados[j].cod_uf,
            dados[j].cod_mun,
            dados[j].nome,
            dados[j].populacao);
        }

    
        fclose(ff);
        fclose(fp);
        return 0;


    }
}