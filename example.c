#include <stdio.h>
#include "veety.c"

int main() {
  while (0==0) {
    int workspace = getWorkspace();
    startMoros();
    if (workspace == 1) {
      drawString("GRAPHING PROGRAM 200", 21, 11, 0);
      button(25, 6, "GRAPH");
    } else if (workspace == 2) {
      drawString("GRAPHING PROGRAM", 21, 11, 0);
    } else {
      button(25, 6, "GRAPH");
      drawString("Testing", 1, 1, 0);
      drawLine('y', slopeEYO, 0, 10);
    }
    window(50, 26, "main.c");
    getInput();
  }
  return 0;
}
