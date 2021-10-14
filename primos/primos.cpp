#include <iostream>
#include <omp.h>
#include <chrono>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]){
    long long numero = 922337203861,val;
    bool ehPrimo =true;
    double inicio = omp_get_wtime();
    long long fim = sqrt(numero);

    #pragma omp parallel for
    for (long long i = 2; i <fim; i++)
    {
       if (numero % i == 0)
       {
          ehPrimo=false;
          val = i;
       }
    }
    if (ehPrimo)
    {
       cout << "Valor primo"<< endl; 
    }
      if (!ehPrimo)
    {
       cout << "Valor nao eh primo"<<val<< endl;
    }
    
    
    double final = omp_get_wtime();
    
    cout << "Duracao total: " << final - inicio;
}