#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

int inteiros[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

//TH1 0 1 2 3 4
//TH2 5 6 7 8 9

void *rotina(void *parametro)
{
    int indice = *(int *)parametro;
    int soma = 0;
    //indice total de entrada / quantidade de threads = 8
    for (int i = 0; i < 8; i++)
        soma += inteiros[indice + i];

    *(int *)parametro = soma;
    return (void *)parametro;
}

int main()
{
    for (int i = 0; i < 32; i++)
    {
        inteiros[i] = i;
    }
    

    pthread_t th[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        //i=1
        int *threadID = (int *)malloc(sizeof(int));
        *threadID = i * 8;
        pthread_create(&th[i], NULL, rotina, threadID);
    }
    int somaTotal = 0;
    int *resp;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(th[i], (void **)&resp);

        somaTotal += *resp;
    }

    printf("A soma total : %d\n", somaTotal);
    
    pthread_exit(NULL);
}