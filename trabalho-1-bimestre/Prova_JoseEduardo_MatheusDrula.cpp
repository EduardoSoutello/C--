#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
pthread_mutex_t chave;
int num, t;
string nome,temp;
vector<string> lista01;
map<string,int> nomes;

void *contagem  (void *parametro){       
    for (int i = 0; i < t; i++){
        if (lista01[i] != " ")
            temp = lista01[i];
            nomes[temp] += 1;
            lista01[i] = " ";
    }
return NULL;
}

int main(){

    
    cin >> num; // numero da quantidade de threads a serem criadas
    
    int qtd;
    ifstream entrada("teste.txt"); //leitura de arquivo txt
    auto inicio = chrono::high_resolution_clock::now();
    if (entrada.is_open()){    
        while(!entrada.eof()){// le arquivos até o fim do arquivo end of file   
            entrada >> temp;
            lista01.push_back (temp);
            t++;
        }
        entrada.close();
        cout << "Arquivo lido com sucesso !\n";
       
    }
    else{
        cout << "Erro para abrir arquivo !";
    }
	pthread_t *th = new pthread_t[num];
	
	for ( int i = 0; i < num; i++){
      pthread_create(&th[i], NULL, contagem, NULL);
    }

	for (int i = 0; i < num; i++){
    pthread_join(th[i], NULL);
    }
	auto fim = chrono::high_resolution_clock::now();
	chrono::duration<float> duracao = fim - inicio;
    cout << "Duracao total: " << duracao.count() <<"s"<< endl;

    for (auto dupla : nomes){
        if(dupla.first != "ㅤ"){
            cout << "Nome " << dupla.first << " Qtd " << dupla.second << endl; 
        }
    }
}