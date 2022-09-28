#include <stdio.h>
#include "veety.c"

int main() {
  while (0==0) {
    int workspace = getWorkspace();
    startVeety();
    
    button(32, 10, "Graph");
    TextBox("Input Equation", 27, 6);
    window(50, 26, "Graphing Calculator");
    
    getInput();
  }
  return 0;
}
