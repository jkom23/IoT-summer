#include <stdio.h>
int main() {
   float num1;
   int num2;
   char operation;

    printf("Enter the first value\n");
    scanf("\n%f", &num1);
    printf("Enter the second value\n");
    scanf("\n%d", &num2);
    printf("Enter the operation of your choosing\n");
    scanf("\n%c", &operation);
    switch (operation){
    case '+':
      printf("%f", num1+num2);
      break;
    case '-':
      printf("%f", num1-num2);
      break;
    case '*':
      printf("%f", num1*num2);
      break;
    case '/':
      printf("%f", num1/num2);
      break;
    default:
      printf("Invalid Operator or ERROR");
      break;
  }

}