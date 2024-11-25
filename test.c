#include <stdio.h>

int factorial(int n){
    if(n==0) return 1;
    return factorial(n-1)*n;
}

int main(){
    printf("Factorial of 5 is %d\n", factorial(5));
    return 0;
}