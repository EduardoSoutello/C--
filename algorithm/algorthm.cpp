#include<iostream>
#include<omp.h>
#include<algorithm>
#include<ctime>
#include<vector>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
   
    vector<int> lista(100000000,0);
    generate(lista.begin(),lista.end(),rand);
    int valor_maximo = lista[0];
    double inicio = omp_get_wtime();

    #pragma omp parallel for reduction (max : valor_maximo)
    for (int i = 0; i < lista.size(); i++)
    {
        valor_maximo = valor_maximo >lista[i] ? valor_maximo : lista[i];
    }
    double fim = omp_get_wtime();
    cout << valor_maximo << " em " << fim - inicio << " segundos";
}