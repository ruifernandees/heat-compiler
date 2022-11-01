#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    
    struct no *prox;
}No;

No *nascente()
{
    No *aux = (No*) malloc(sizeof(No));
    
    aux->canibais = 3;
    aux->missio = 3;
    aux->cc = NULL;
    aux->cm = NULL;
    aux->mc = NULL;
    aux->mm = NULL;
    
    return aux;
}

void imprimir(No *rio)
{
    if (rio != NULL)
    {
        printf("%i %i\n", rio->canibais, rio->missio);
        //printf("RioCC\n");
        imprimir(rio->cc);
        //printf("RioCM\n");
        imprimir(rio->cm);
        //printf("RioMC\n");
        imprimir(rio->mc);
        //printf("RioMM\n");
        imprimir(rio->mm);
    }
}

void busca (No *inicio, char padrao[], int tam, int cont)
{
    int difC, difM;
    No *aux = malloc(sizeof(No));

    //printf("%i\n", tam);
    
    if (cont < tam - 1) // 0 1 2 3 4 5 6
    {
        if (padrao[cont] == '1')
        {
            printf ("Vao dois canibais\n");
            aux = inicio->cc;
            //printf ("\n");

            //printf ("inicio->canibais: %d inicio->missio: %d\n", inicio->canibais, inicio->missio);
            //printf ("aux->canibais: %d aux->missio: %d\n", aux->canibais, aux->missio);

            difC = aux->canibais - (inicio->canibais-2);
            difM = aux->missio - inicio->missio;
            printf ("volta %d canibal e %d missionario\n\n", difC, difM);
            
            inicio = inicio->cc;
            busca (inicio, padrao, tam, cont+1);
        }
        else if (padrao[cont] == '2')
        {
            printf ("Vao 1 canibal e 1 missionario\n");
            aux = inicio->cm;
            //printf ("\n");
            //printf ("inicio->canibais: %d inicio->missio: %d\n", inicio->canibais, inicio->missio);
            //printf ("aux->canibais: %d aux->missio: %d\n", aux->canibais, aux->missio);
            difC = aux->canibais - (inicio->canibais-1);
            difM = aux->missio - (inicio->missio-1);
            printf ("volta %d canibal e %d missionario\n\n", difC, difM);
            
            inicio = inicio->cm;
            busca (inicio, padrao, tam, cont+1);
        }
        else if (padrao[cont] == '3')
        {
            printf ("Vao 1 missionario e 1 canibal\n");
            aux = inicio->mc;
            //printf ("\n");
            //printf ("inicio->canibais: %d inicio->missio: %d\n", inicio->canibais, inicio->missio);
            //printf ("aux->canibais: %d aux->missio: %d\n", aux->canibais, aux->missio);
            difC = aux->canibais - (inicio->canibais-1);
            difM = aux->missio - (inicio->missio-1);
            printf ("volta %d canibal e %d missionario\n\n", difC, difM);
            
            inicio = inicio->mc;
            busca (inicio, padrao, tam, cont+1);
        }
        else if (padrao[cont] == '4')
        {
            printf ("Vao dois missionarios\n");
            aux = inicio->mm;
            //printf ("\n");
            //printf ("inicio->canibais: %d inicio->missio: %d\n", inicio->canibais, inicio->missio);
            //printf ("aux->canibais: %d aux->missio: %d\n", aux->canibais, aux->missio);
            difC = aux->canibais - inicio->canibais;
            difM = aux->missio - (inicio->missio-2);
            printf ("volta %d canibal e %d missionario\n\n", difC, difM);
            
            inicio = inicio->mm;
            busca (inicio, padrao, tam, cont+1);
        }
    }
    else
    {
        printf ("-=-=-=-=-=-Game Over-=-=-=-=-=-\n\n");
    }
}

void Pvetor (char padrao[], int tam, int n)
{
    // n < tam (CERTO)
    if (n < tam)
    {
        printf ("%c ", padrao[n]);
        Pvetor (padrao, tam, n+1);
    }
    else
    {
        printf ("\nPrintado\n");
    }
}

int pesquisa(No *rio, No *inicio, char padrao[], int cont)
{
    int tam;

    if (rio != NULL)
    {
        if (rio->canibais == 0 && rio->missio == 0)
        {
            //printf ("%d\n", cont);
            tam = strlen(padrao);
            printf("\n");
            //Pvetor (padrao, tam, 0);
            //printf("\n\n");
            busca (inicio, padrao, tam, 0);
            //printf ("\n\n");
            //printf("ATRAVESSADO\n");
            return 1;
        }
        //printf("(%i)", cont);
        padrao[cont] = '1';
        //printf("1 ");
        pesquisa(rio->cc, inicio, padrao, cont+1);
        padrao[cont] = '2';
        //printf("2 ");
        pesquisa(rio->cm, inicio, padrao, cont+1);
        padrao[cont] = '3';
        //printf("3 ");
        pesquisa(rio->mc, inicio, padrao, cont+1);
        padrao[cont] = '4';
        //printf("4 ");
        pesquisa(rio->mm, inicio, padrao, cont+1);
        //printf("SAIU ");
    }
    return 0;
}

int verificarIgualdade(int c, int m, int a[], int tamanho, int contador)
{
    if (c < 0 || m < 0)
    {
        return 0;
    }
    if (contador >= tamanho)
    {
        //printf("PODE PASSAR");
        return 1;
    }
    if (c == a[contador] && m == a[contador + 1])
    {
        // c = 1, m = 2
        // 1 2 3 4
        //printf("NAO PODE PASSAR CONFIGURACAO ERRADA");
        return 0;
    }
    else
    {
        //printf("PASSOU %i\n", contador);
        return verificarIgualdade(c, m, a, tamanho, contador + 2);
    }
}

No *inserir(No *rio, int c, int m, int devorados[], int condicao)
{
    No *aux = (No*) malloc(sizeof(No));
    int pode, a, b;
    if (c == 0 && m == 0)
    {
        aux->canibais = c;
        aux->missio = m;
            
        aux->cc = NULL;
        aux->cm = NULL;
        aux->mc = NULL;
        aux->mm = NULL;
        return aux;
    }
    if (rio == NULL)
    {
        //printf("ENTROU AQ");
        pode = verificarIgualdade(c, m, devorados, 12, 0);
        if (pode == 1)
        {
            if (c != 3 && m != 3)
            {
                if (condicao == 0) // cc ou cm
                {
                    a = c + 1;
                    b = m;
                }
                else if (condicao == 1) // mc ou mm
                {
                    b = m + 1;
                    a = c;
                }
                
                pode = verificarIgualdade(a, b, devorados, 12, 0);
                if (pode == 0)
                {
                    if (b != m)
                    {
                        condicao = 0;
                    }
                    if (a != c)
                    {
                        condicao = 1;
                    }
                }
                // 2 0, << c e m, 2 1 << a e b
                // a != c || b != m  se b for diferente c = c + 1
                // se a for
            }
            if (c == 1 && m == 1)
            {
                c = c + 1;
                m = m + 1;
            }
            else if (condicao == 0) // cc ou cm
            {
                c = c + 1; // VOLTA
            }
            else if (condicao == 1) // mc ou mm
            {
                //printf("(%i %i)\n", c, m);
                m = m + 1;
            }
            
            pode = verificarIgualdade(c, m, devorados, 12, 0);
            if (pode == 1)
            {
                aux->canibais = c;
                aux->missio = m;
            
                aux->cc = NULL;
                aux->cm = NULL;
                aux->mc = NULL;
                aux->mm = NULL;
                //printf("\n1\n");
            }
            else
            {
                aux = NULL;
            }
        }
        else
        {
            aux = NULL;
        }
        return aux;
    }
    else
    {
        //printf("\n2\n");
        rio->cc = inserir(rio->cc, rio->canibais - 2, rio->missio, devorados, 0);
        rio->cm = inserir(rio->cm, rio->canibais - 1, rio->missio - 1, devorados, 0);
        rio->mc = inserir(rio->mc, rio->canibais - 1, rio->missio - 1, devorados, 1);
        rio->mm = inserir(rio->mm, rio->canibais, rio->missio - 2, devorados, 1);
    }
    
    return rio;
}

int main()
{
    No *rio;
    rio = nascente ();
    
    //printf("%i %i", rio->canibais, rio->missio);
    int devorados[12] = {2, 1, 3, 1, 3, 2, 1, 2, 0, 2, 0, 1};

    char padrao[8];
    
    for (int m = 0; m < 6; m++)
    {
        rio = inserir(rio, rio->canibais, rio->missio, devorados, 0);
    }
    
    pesquisa(rio, rio, padrao, 0);

    //imprimir(rio);
    
    return 0;
}