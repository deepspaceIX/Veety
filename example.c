#include <stdio.h>
#include "veety.h"

int main(){
  while (0==0) {
    int workspace = getWorkspace();
    startVeety();
    button(13, 10, "Graph");
    TextBox("Input Equation", 13, 6);
    TextBox("Secondary Input Test", 13, 20);
    window(26, 26, "Graphing Calculator");
    
    addTextBoxText("TEST1");
    addTextBoxText("TEST2");
    addTextBoxText("TEST3");
    addTextBoxText("TEST4");

    getInput();
  }
  return 0;
}