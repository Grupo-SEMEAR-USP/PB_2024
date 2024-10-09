// Programa teste que envia valores para o arquivo "valores.txt"
#include <stdio.h>

int main(){
    FILE *fp = fopen("valores.txt", "w");
    float a = 80, j = 0.2;
    for(int i=0; i<200; i++){
        if(a >= 110.00) j = -j; //cresce até 110
        a += j; 

        fprintf(fp, "%.2f ", a);
    }
}