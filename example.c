#include <stdio.h>
#include "veety.h"

int main(){
  while (0==0) {
    int workspace = getWorkspace();
    startVeety(26, 26, "Graphing Calculator");
    
    button(13, 10, "Graph");
    TextBox("Input Equation", 13, 6);
    TextBox("Secondary Input Test", 13, 20);
    
    window();
    getInput();
  }
  return 0;
}
