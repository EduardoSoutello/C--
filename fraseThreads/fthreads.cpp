#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <windows.h>

#define NUM_THREADS 10

char msg[50];
int t =0;

void *eco(void *parametro)
{
    char temp[50];
    memcpy(temp,msg,50); 
    while (strcmp(msg, "fim"))
    {   
        int id = pthread_self();
        printf("Thread %i %s\n",id , temp);
        Sleep(1000);
    }
    return NULL;
}

int main()
{
    pthread_t th[NUM_THREADS];

    printf("Digite uma mensagem:\n");
    scanf("%s", &msg);

    pthread_create(&th[0], NULL, eco, NULL);

    t+=1;

    while (strcmp(msg, "fim"))
    {        
        printf("Digite uma mensagem:\n");
        scanf("%s", &msg);
      
        char *msg2[t][50] = {msg};

        pthread_create(&th[t], NULL, eco, NULL);
        t++;
    }
    for ( int i = 0; i < t ; i++)
    {
     pthread_join(th[i], NULL);
    }    
}
