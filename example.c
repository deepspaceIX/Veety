#include <stdio.h>
#include "veety.c"

int main() {
  int i;
  printf("help");
  int workspace = getWorkspace();
  for (i = 0; i >= i; i++) {
    startMoros();
    if (workspace == 1) {
      drawString("GRAPHING PROGRAM 200", 21, 11, 0);
      button(25, 6, "GRAPH");
    } else if (workspace == 2) {
      drawString("GRAPHING PROGRAM", 21, 11, 0);
    } else {
      button(25, 6, "GRAPH");
      drawString("Testing", 1, 1, 0);
    }
    window(50, 26, "Moros");
    getInput();
  }
  return 0;
}
