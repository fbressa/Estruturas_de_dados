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

void intercala(int p, int q, int r, struct dados *v[])
{
    // está assim por conta da alocação dinamica, w precisa ser um ponteiro duplo porque queremos um array de ponteiros,
    // e malloc precisa retornar um ponteiro para o início desse array. Portanto, w deve ser um ponteiro para ponteiro (struct dados **).
    struct dados **w;
    w = malloc((r - p) * sizeof(struct dados *));
    int i = p, j = q;
    int k = 0;

    while (i < q && j < r)
    {
        // -> pois é um ponteiro para struct e não apenas entrar no seu campo com o .
        if (v[i]->populacao <= v[j]->populacao)
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }
    while (i < q)
        w[k++] = v[i++];
    while (j < r)
        w[k++] = v[j++];
    for (i = p; i < r; ++i)
        v[i] = w[i - p];
    free(w);
}

void mergesort(int p, int r, struct dados *v[])
{
    if (p < r - 1)
    {
        int q = (p + r) / 2;
        mergesort(p, q, v);
        mergesort(q, r, v);
        intercala(p, q, r, v);
    }
}

int main()
{
    struct dados dados[5571];
    // para poder mexer com array escrever assim
    struct dados *dados_ptrs[5571];
    FILE *fp = fopen("estimativa_dou_2021.csv", "r");
    if (fp == NULL)
    {
        puts("Arquivo não encontrado\n");
        system("pause");
        exit(0);
    }

    FILE *ff = fopen("arquivo_ordenado_intercala", "w");
    if (ff == NULL)
    {
        puts("Arquivo não criado\n");
        system("pause");
        exit(0);
    }

    if (fp != NULL)
    {

        char primeiralinha[100]; // Lê a primeira linha do arquivo e armazena em primeiralinha
        fscanf(fp, "%[^\n]\n", primeiralinha);
        int i = 0;

        while (!feof(fp))
        {
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

        mergesort(0 , i, dados_ptrs);//função avaliada no benchmarking

        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("Done in %f seconds\n", elapsed_time);
        //fim do mecanismo

        for (int j = 0; j < i; j++)
        {
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