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

    editTextBoxText(0, "TEST A");
    editTextBoxText(0, "TEST BA");
    editTextBoxText(1, "TEST C");
    editTextBoxText(3, "TEST D");
    editTextBoxText(2, "TEST E");
    editTextBoxText(3, "TEST ABCD");
    editTextBoxText(1, "TEST BAA");

    printf("%s\n",returnTextBoxText(0, g_win_textBoxTexts));
    printf("%s\n",returnTextBoxText(1, g_win_textBoxTexts));
    printf("%s\n",returnTextBoxText(2, g_win_textBoxTexts));
    printf("%s\n",returnTextBoxText(3, g_win_textBoxTexts));
        
    getInput();
  }
  return 0;
}