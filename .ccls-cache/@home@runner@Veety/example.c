#include <stdio.h>
#include "veety.h"
int main() {
  while (0==0) {
    int workspace = getWorkspace();
    startVeety();
    
    button(32, 10, "Graph");
    //TextBox("Input Equation", 27, 6);
    window(50, 26, "Graphing Calculator");
        printf("%d, %d, %d, %d, %d", g_cursor_x, g_cursor_y, g_win_sizeX, g_win_sizeY, sizeXTitle); 
    getInput();
  }
  return 0;
}
