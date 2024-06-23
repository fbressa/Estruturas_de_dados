#include <stdio.h>
/*uma função é recursiva primitiva se e somente se existir um número natural m tal que 
a função possa ser computada por uma Máquina de Turing que sempre com A(m, n) ou menos passos,
onde n é a soma dos argumentos da função recursiva primitiva.*/

int AckermannRecursivo(int m, int n)
{
    if(m==0)
    {
        return n+1;
    }
    else if (m>0 && n == 0)
    {
        return AckermannRecursivo(m - 1, 1);
    }
    else if (m > 0, n > 0)
    {
        return AckermannRecursivo(m-1, AckermannRecursivo(m, n-1));
    }
}

int main()
{
    int m, n;

    scanf("%d %d", &m, &n);
    printf("%d", AckermannRecursivo(m,n));

    return 0;
    
}