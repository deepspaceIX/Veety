//This is an example of how Veety could be used for an actual purpose, here it is being used as a basic graphing calculator.
//This gives you a better idea on how the syntax works in Veety.

#include <stdio.h>
#include "veety.h"

int main(){
  while (0==0) {
    int workspace = getWorkspace();
    startVeety(16, 16, "Graphing Calculator");

    if (workspace==0){
      drawString("Put equation in slope intercept form", 1, 4);
      drawString("Example: y=2x+1; x=4y+1", 1, 5);
      TextBox("Input Equation", 8, 6);
      button(8, 10, "Graph");
    } else {
      char axis = 'y';
      int slope = 1;
      int intercept = 1;
      
      const char* textBoxString = returnTextBoxText(0, g_win_textBoxTexts);
      
      if (textBoxString[0] == 'y') {
        axis = 'y';
      } else if (textBoxString[0] == 'x') {
        axis = 'x';
      }
      int i;
      int dontSetSlopeAsZero = 0;
      int slopeLocation = -1;
      for (i=0; i<=string_length(textBoxString); i++) {
        if (textBoxString[i] == 'x' && i!=0){
          dontSetSlopeAsZero = 1;
          slopeLocation = i;
        }
        if (textBoxString[i] == 'y' && i!=0){
          dontSetSlopeAsZero = 1;
          slopeLocation = i;
        }
      }

      if (dontSetSlopeAsZero == 0) {
         slope = 0;
      }

      if (slopeLocation != -1) {
        slope = textBoxString[slopeLocation-1];
        if (slope=='=') {
          slope = 1;
        } else {
          slope = (int)textBoxString[slopeLocation-1] - 48;
        }
      }

    if (textBoxString[slopeLocation+1]=='+' || textBoxString[slopeLocation+1]=='-') {
      if (slopeLocation+1=='-') {
        intercept = -(int)textBoxString[slopeLocation+2] - 48;
      } else {
        intercept = (int)textBoxString[slopeLocation+2] - 48;
      }
    }
      drawLine(axis, slope, 9+(string_length(title)/2), 8-intercept);
      drawLine('x', 0, 9+(string_length(title)/2), 8);
      drawLine('y', 0, 0, 8);
      
    }
    
    
    window();
    getInput();
  }
  return 0;
}
