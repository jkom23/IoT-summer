#include <stdio.h>

int main(void) {

  char name [8]= "internet";
  
  for(int i=0; i<8; i++){
    name[i]= name[i]-32;
    printf("%c", name[i]);

  }
  return 0;
}