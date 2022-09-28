#include <stdio.h>
#include "veety.c"

int main() {
  while (0==0) {
    int workspace = getWorkspace();
    startMoros();
    drawString("Graphing Calculator", 10, 1, 0);
    button(15, 15, "graph");
    //TextBox("test", 10, 10);
    window(50, 26, "Ez-Graph 2");
    getInput();
  }
  return 0;
}
