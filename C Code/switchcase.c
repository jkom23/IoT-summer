#include <stdio.h>

int main(void) {
  int valUser;
  printf("Enter a value between 0 and 4\n");
  scanf("%d", &valUser);
  switch (valUser){
    case 0:
      printf("Val:0");
      break;
    case 1:
      printf("\nVal:1");
      break;
    case 2:
      printf("\nVal:2");
      break;
    case 3:
      printf("\nVal:3");
      break;
    case 4:
      printf("\nVal:4");
      break;
    default:
      printf("\n Value exceeds limit");
      break;
  }
}