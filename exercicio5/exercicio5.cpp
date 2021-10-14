#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 8
using namespace std;

string temp;

pthread_mutex_t chave = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condFila = PTHREAD_COND_INITIALIZER;

void * portugues(void *parametro){
    int id = *(int *)parametro;
    while (1){
       if (temp == "ola"){
            cout << "Alo da thread "<< id << endl;
            
        }
         if (temp == "tchau"){        
            return NULL;
        }
        pthread_cond_wait(&condFila,&chave);
    }
    return NULL;
}

void * ingles(void *parametro){
    int id = *(int *)parametro;
    while (1){
        if (temp == "hello"){
            cout << "Hello from thread "<< id << endl;
        }
        if (temp == "bye"){        
            return NULL;
        }
        pthread_cond_wait(&condFila,&chave);
    }
    return NULL;
}

int main(int argc, char *argv[]){

    pthread_t th[NUM_THREADS];
    
    cin >> temp;

    for (int i = 0; i < NUM_THREADS; i++){
        int *threadID = (int *)malloc(sizeof(int));
        *threadID = i;
       
       if (i%2 == 0){
            pthread_create(&th[i], NULL, portugues, threadID);
        }
        else
            pthread_create(&th[i], NULL, ingles, threadID);   
    }
    int x =0; //laço repetição

    while (x!=2){
        cin >> temp;
        pthread_cond_broadcast(&condFila);
        
        if (temp == "tchau"){
            x ++;
        }
        if (temp == "bye"){
            x ++;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(th[i],NULL);
    }
    
}
