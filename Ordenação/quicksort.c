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

int separa(struct dados *a[], int p, int r) {
    int c = a[r]->populacao; // Define o pivô como a população do último elemento do subarray
    int j = p; // Inicializa o índice para elementos menores ou iguais ao pivô
    for (int k = p; k < r; ++k) { // Percorre o subarray de `p` até `r-1`
        if (a[k]->populacao <= c) { // Se a população do elemento atual é menor ou igual ao pivô
            struct dados *t = a[j]; // Troca os elementos a[j] e a[k]
            a[j] = a[k];
            a[k] = t;
            ++j; // Incrementa `j` para o próximo elemento
        }
    }
    struct dados *t = a[j]; // Troca o elemento a[j] com o pivô (a[r])
    a[j] = a[r];
    a[r] = t;
    return j; // Retorna o índice do pivô
}


void quicksort(struct dados *a[], int p, int r) {
    if (p < r) { // Verifica se o subarray tem mais de um elemento
        int j = separa(a, p, r); // Particiona o array e obtém o índice do pivô
        quicksort(a, p, j - 1); // Aplica o quicksort à sublista à esquerda do pivô
        quicksort(a, j + 1, r); // Aplica o quicksort à sublista à direita do pivô
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

    FILE *ff = fopen("arquivo_ordenado_quicksort", "w");
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

        quicksort(dados_ptrs, 0, i - 1);//função avaliada no benchmarking

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