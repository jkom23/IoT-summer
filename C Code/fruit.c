#include <stdio.h>

int main(void) {
 char fruit;
  
  printf("Enter the first letter of a fruit\n");
  scanf("%c", &fruit);
  switch (fruit){
    case 'o':
      printf("You chose Orange");
      break;
    case 'b':
      printf("\nYou chose Banana");
      break;
    case 's':
      printf("\nYou chose Strawberry");
      break;
    case 'l':
      printf("\nYou chose Lemon");
      break;
    case 'g':
      printf("\nYou chose Grape");
      break;
    default:
      printf("\nThat is not a fruit/ERROR");
      break;
  }
}