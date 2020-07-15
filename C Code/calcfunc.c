#include <stdio.h>

int add(int a, int b){
    return a+b;
}

int sub(int a, int b){
    return a-b;
}
int times(int a, int b){
    return a*b;
}
float div(float a, int b){
    return a/b;
}

int main(void) {
printf("%d", add(1, 2));
printf("\n%d", sub(1, 2));
printf("\n%d", times(1, 2));
printf("\n%f", div(1, 2));
  return 0;
}