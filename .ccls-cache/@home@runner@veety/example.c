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
    //printf("%d, %d", currentTextBox, workspace); 
    
    addTextBoxText("TEST1");
    addTextBoxText("TEST2");
    addTextBoxText("TEST3");
    addTextBoxText("TEST4");
    
    int i;
    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }
    printf("\n");
    editTextBoxText(0, "TEST A");
    
    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }

    printf("\n");
    editTextBoxText(0, "TEST BA");

    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }
    
    printf("\n");
    editTextBoxText(1, "TEST C");

    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }

    printf("\n");
    editTextBoxText(3, "TEST D");

    for (i=0;i<string_length(g_win_textBoxTexts); i++) {
      printf("%c", g_win_textBoxTexts[i]);
    }
    
    getInput();
  }
  return 0;
}