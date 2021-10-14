#include <iostream>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define NUM_THREADS 2

using namespace std;
char jokenpo[3][10] = {"PEDRA", "PAPEL", "TESOURA"};
char resultado [2][10];

void *jogo(void *parametro){
    int id = pthread_self();
     int *sorteado = (int *)malloc(sizeof(int));
    *sorteado = (rand())%3;
    
    return (void *)sorteado;
}

int main(int argc, char *argv[]){

    srand(time(NULL));
    pthread_t th[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++){
        int *sorteado;
        pthread_create(&th[i], NULL, jogo, (void *)sorteado);
    }

    for (int i = 0; i < NUM_THREADS; i++){

        int *sorteado;
        pthread_join(th[i], (void **)&sorteado);
        //printf("%d ",*sorteado);
        strcpy(resultado[i],jokenpo[*sorteado]);
    }


     cout << "Iniciando o jogo"<<endl;

    if (!strcmp(resultado[0],"PEDRA")){
        if(!strcmp(resultado[1],"TESOURA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[0]<< " Thread 1 Ganhadora";
        }
        if(!strcmp(resultado[1],"PAPEL")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[1]<< " Thread 2 Ganhadora";
        }
        if(!strcmp(resultado[1],"PEDRA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[0]<< " Empate !";
        }
    }
    if (!strcmp(resultado[0],"PAPEL")){
        if(!strcmp(resultado[1],"TESOURA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[1]<< " Thread 2 Ganhadora";
        }
        if(!strcmp(resultado[1],"PEDRA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[0]<< " Thread 1 Ganhadora";
        }
        if(!strcmp(resultado[1],"PAPEL")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout <<resultado[0]<< " Empate !";
        }
    }
    if (!strcmp(resultado[0],"TESOURA")){
        if(!strcmp(resultado[1],"PAPEL")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[0]<< " Thread 1 Ganhadora";
        }
        if(!strcmp(resultado[1],"PEDRA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[1]<< " Thread 2 Ganhadora";
        }
        if(!strcmp(resultado[1],"TESOURA")){
            cout << "Thread 1 - "<< resultado[0]<< "  Thread 2 - "<< resultado[1]<<endl;
            cout << resultado[0]<< " Empate !";
        }
    }
}