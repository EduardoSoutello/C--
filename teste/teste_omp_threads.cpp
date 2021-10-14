#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    
    int arr[] = {10,20,30,40,50,60,70,80,90,100};
    int tam=10;

#pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        
        for (int i = id; i < tam; i+=numThreads)
        {
           arr[i] *= arr[i];
        }
        
    }
for (int i = 0; i < 10; i++)
    {
        printf(" %d \n",arr[i]);
    }
    
    printf("Fim do programa");
}