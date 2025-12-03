#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <chrono>

using namespace std;
pthread_mutex_t chave;

int num, t, i = 0;
string temp;
void contar();
void queue();
void queue2();


void *contagem  (void *parametro){
	contar();
return NULL;
}

struct Nomes{
    int idname;
    string nome;
    bool ver;
    Nomes *prox;
} *Head = NULL, *Tail = NULL;

struct NomesCont{
    int idname2;
    string nome2;
    bool ver2;
    NomesCont *prox2;
} *Head2 = NULL, *Tail2 = NULL;

void queue(string temp){
	Nomes *NovoElemento;
	NovoElemento = (struct Nomes*)malloc(sizeof(struct Nomes));
	NovoElemento->nome = temp;
    
	NovoElemento->prox = NULL;
	if (Head == NULL)
	{
		Head = NovoElemento;
		Tail = NovoElemento;
	}
	else //insere depois do Head
	{
		Tail->prox = NovoElemento;
		Tail = NovoElemento;
	}
	cout << NovoElemento->nome << endl;
}

void queue2(string temp2){

	NomesCont *ElementoVarredura = Head2;
	NomesCont *NovoElemento;
	NovoElemento = (struct NomesCont*)malloc(sizeof(struct NomesCont));

	if (Head2 == NULL){
		
		NovoElemento->nome2 = temp2;
		NovoElemento->idname2 = 1;
		NovoElemento->prox2 = NULL;

		Head2 = NovoElemento;
		Tail2 = NovoElemento;
	}
	else {
		while ((ElementoVarredura->nome2 != temp2)&&(ElementoVarredura->prox2 != NULL)) {
			ElementoVarredura = ElementoVarredura->prox2;
		}
		if (ElementoVarredura->nome2 == temp2){
			NovoElemento->idname2 += 1;
		}
		else{
			NovoElemento->nome2 = temp2;
			NovoElemento->idname2 = 1;
			NovoElemento->prox2 = NULL;
			Tail2 = NovoElemento;
		}
		cout << ElementoVarredura->idname2 << " " << ElementoVarredura->nome2 << " ";//tail aponta para o NULL por isso esta fora do while
	}
	
}
void contar (){
    Nomes *ElementoVarredura = Head;

	if (Head == NULL)
		cout << "\nFila vazia!!!\n";
	else {
        int id2;
        string temp2;
		// talvez por a chave aqui
		while (ElementoVarredura->prox != NULL) {

            temp2 = ElementoVarredura->nome;
			queue2(temp2);
			ElementoVarredura = ElementoVarredura->prox;
		}
		temp2 = ElementoVarredura->nome;
		queue2(temp2);//tail aponta para o NULL por isso esta fora do while
		// talvez unlock aqui
	}
}

void display(){
	NomesCont *ElementoVarredura = Head2;

	if (Head == NULL)
		cout << "\nFila vazia!!!\n";
	else {

		while (ElementoVarredura->prox2 != NULL) {
			cout << ElementoVarredura->idname2 << " "<<  ElementoVarredura->nome2  << " ";
			ElementoVarredura = ElementoVarredura->prox2;
		}
		cout << ElementoVarredura->idname2 << " " << ElementoVarredura->nome2 << " ";//tail aponta para o NULL por isso esta fora do while
	}
	cout <<"\n";
}

int main(int argc, char *argv[]){
cin >> num; // numero da quantidade de threads a serem criadas
ifstream entrada("teste.txt"); //leitura de arquivo txt
auto inicio = chrono::high_resolution_clock::now();

if (entrada.is_open()){    
        while(!entrada.eof()){// le arquivos até o fim do arquivo end of file   
            entrada >> temp;
            queue(temp);    
            t++;
        }
        entrada.close();
        cout << "Arquivo lido com sucesso !\n";
    }
    else{
        cout << "Erro para abrir arquivo !";
    }
    
	pthread_t *th = new pthread_t[num];
	
	for ( i = 0; i < num; i++){
      pthread_create(&th[i], NULL, contagem, NULL);
    }

	for (int i = 0; i < num; i++){
    pthread_join(th[i], NULL);
    }
	auto fim = chrono::high_resolution_clock::now();
	display();
	chrono::duration<float> duracao = fim - inicio;
    cout << "Duracao total: " << duracao.count() <<"s"<< endl;

}