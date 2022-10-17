#include <stdio.h>
#include "veety.h"

int main(){
  while (0==0) {
    int workspace = getWorkspace();
    startVeety();
    addTextBoxText("this is a test");
    addTextBoxText("This is a second test");
    button(32, 10, "Graph");
    TextBox("Input Equation", 27, 6);
    TextBox("Secondary Input Test", 27, 20);
    window(50, 26, "Graphing Calculator");
    //printf("%d, %d", currentTextBox, workspace); 
    int i;
    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }
    getInput();
  }
  return 0;
}