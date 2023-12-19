#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *f;
  f = fopen("a.txt", "r");
  fseek(f, 25, SEEK_SET);
  char a[25];
  fgets(a, 25, f);
  printf("%s", a);
}
