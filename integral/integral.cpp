#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 12

long num_passos = 1000000000;
double passo;

int main(){
    double pi =0;
    passo = 1.0 /num_passos;
    int ntReal;

    double inicio = omp_get_wtime();

#pragma omp parallel num_threads(NUM_THREADS)
{
    double x;
    int id = omp_get_thread_num();
    int nThreads = omp_get_num_threads();

    if (id==0){
        ntReal = nThreads;
    }
    double somaT;
    for (int i = id; i < num_passos; i+=nThreads){
       x = (i + 0.5)*passo;
       somaT += 4.0/(1+x*x);
    }

    #pragma omp crtitical
        pi+= somaT*passo;
}
        
    double total = omp_get_wtime() - inicio;

    printf("Tempod e calculo %lf\n", total);
    printf("PI: %lf\n", pi);

}