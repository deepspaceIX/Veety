#include <stdio.h>

int g_win_sizeX = 10;
int g_win_sizeY = 10;
char c;

int g_cursor_x = 1;
int g_cursor_y = 1;
const char g_cursor_char = '^';
char g_cursor_color[] = "0;31";


float slopeEYO = 1;


char g_win_character_cords[20000];
char g_cursor_clickpoints[5000];
int g_win_characters_count = 0;
char g_win_current_window[100];
int workspace = 0;
int disableBack = 0;

int whyIsntThisWorking = 0;
int isEven(int num) {
  if (num % 2 == 0)
    return 4;
  else
    return 3;
}

void append_string(char * str, char c) {
  for (;* str; str++);
  * str++ = c;
  * str++ = 0;
}

int string_length(char string[]) {
  int s = 0;
  int t = 0;
  char blankChar[] = "";
  for (s = 0; s >= 0; s += 1) {
    if (string[s] == blankChar[0]) {
      s = -10;
    } else {
      t++;
    }
  }
  return t;
}

void addClickpoint(int xCord, int yCord) {
  if (xCord != 0 && yCord != 0) {
    int length = string_length(g_cursor_clickpoints);

    g_cursor_clickpoints[length] = xCord;
    g_cursor_clickpoints[length + 1] = yCord;
  }
}

void drawCharacter(char Character, int xCord, int yCord, int button) {
  if (xCord != 0 && yCord != 0) {
    int length = string_length(g_win_character_cords);

    g_win_character_cords[length] = Character;
    g_win_character_cords[length + 1] = xCord;
    g_win_character_cords[length + 2] = yCord;
    g_win_characters_count++;
    if (button == 1) {
      addClickpoint(xCord, yCord);
    }
  }
}

void drawString(char string[], int xCord, int yCord, int button) {
  int stringLength = string_length(string);
  int p;

  for (p = 0; p <= stringLength - 1; p++) {
    drawCharacter(string[p], xCord + p, yCord, button);
  }
}

void button(int xCord, int yCord, char centerText[]) {
  int i;
  int centerTextLength = string_length(centerText);

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacter('=', xCord + i, yCord, 1);
  }
  drawCharacter('=', xCord, yCord + 1, 1);
  drawCharacter(' ', xCord + 1, yCord + 1, 1);
  drawString(centerText, xCord + 2, yCord + 1, 1);
  drawCharacter(' ', centerTextLength + xCord + 2, yCord + 1, 1);
  drawCharacter('=', xCord + centerTextLength + 3, yCord + 1, 1);

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacter('=', xCord + i, yCord + 2, 1);
  }
  drawCharacter(' ', centerTextLength + 4, yCord + 2, 1);
}

void cursor() {
  int length = string_length(g_win_character_cords);
  int p;
  
  char charCursorIcon = '^';

  for (p = 0; p <= length - 1; p += 2) {
    int cordXEYO = g_cursor_clickpoints[p - 2];
    int cordYEYO = g_cursor_clickpoints[p - 1];
    if (cordXEYO == g_cursor_x && cordYEYO == g_cursor_y) {
      charCursorIcon = '!';
    }
  }

  drawCharacter(charCursorIcon, g_cursor_x, g_cursor_y, 0);
}

void clearCharacterMemory() {
  int i;
  for (i = 0; i < 20000; ++i)
    g_win_character_cords[i] = 0;
  for (i = 0; i < 5000; ++i)
    g_cursor_clickpoints[i] = 0;
  g_win_characters_count = 0;
}

void disableBackFucntion() {
  disableBack = 1;
}

int getWorkspace() {
  return workspace;
}

void drawLine(char axis, float slope, int posX, int posY) {
  char lineCharacter = '+';
  if (axis == 'y') {
    if (slope==0) {
      lineCharacter = '-';
    } else if (slope < 0) {
      lineCharacter = '\\';
    } else if (slope > 0) {
      lineCharacter = '/';
    }
  } else if (axis == 'x') {
    if (slope == 0) {
      lineCharacter = '|';
    } else if (slope > 0) {
      lineCharacter = '/';
    } else if (slope < 0) {
      lineCharacter = '\\';
    }
  }
  
  int i;
  for (i=0; i<=g_win_sizeY; i++) {
    int yCord = (i*slope*-1) + posY;
    int xCord = (i*slope*-1) + posX;
    if (axis == 'y') {
      drawCharacter(lineCharacter, posX+i, yCord, 0);
    } else if(axis == 'x') {
      drawCharacter(lineCharacter, xCord, posY+i, 0);
    }
    
  } 
}

void TextBox(char placeHolder[], int posX, int posY) {
  
}

//Shelly functions
void window(int sizeX, int sizeY, char title[]) {
  if (isEven(sizeX) == 4 && isEven(sizeY) == 4) {
    printf("\e[1;1H\e[2J");

    g_win_sizeX = sizeX;
    g_win_sizeY = sizeY;

    int sizeXDV2 = sizeX / 2;
    int sizeYDV2 = sizeY / 2;
    int i;
    int e;

    printf("+");
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    }
    printf("%s", title);
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    }
    printf("+\n");

    for (e = 1; e <= sizeYDV2; e++) {
      printf("|");
      for (i = 1; i <= sizeX + 2 + string_length(title); i++) {
        int o = 2;
        int w;
        int drawn = 0;
        int drawnCharacters = 0;
        int length = string_length(g_win_character_cords);

        for (; o <= length - 1; o += 3) {
          char charEYO = g_win_character_cords[o - 2];
          int cordXEYO = g_win_character_cords[o - 1];
          int cordYEYO = g_win_character_cords[o];

          if (cordXEYO == i && cordYEYO == e) {
            if (drawnCharacters >= 1) {
              break;
            } else {
              printf("%c", charEYO);
              drawn = 1;
              drawnCharacters++;
            }
          }
        }
        if (drawn == 0) {
          printf(" ");
        }
      }
      printf("|\n");
    }
    printf("+");
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    }
    for (i = 0; i <= string_length(title); i++) {
      printf("-");
    }
    for (i = 0; i <= sizeXDV2-1; i++) {
      printf("-");
    }
    printf("+\n");
  } else {
    printf("x and y must be even for code to work");
  }
  if (c == '<') {
    if (disableBack != 1) {
      workspace--;
    }
  }
  if (c == 'd') {
    g_cursor_x += 1;
  }
  if (c == 'a') {
    g_cursor_x -= 1;
  }
  if (c == 'w') {
    g_cursor_y -= 1;
  }
  if (c == 's') {
    g_cursor_y += 1;
  }
  if (c=='+') {
    slopeEYO += 0.5;
  } else if (c=='-') {
    slopeEYO -= 0.5;
  }
  if (c == ' ') {
    int o;
    int length = string_length(g_cursor_clickpoints);
    
    
    for (o = 0; o <= length - 1; o += 2) {
      int cordXEYO = g_cursor_clickpoints[o - 2];
      int cordYEYO = g_cursor_clickpoints[o - 1];
      if (cordXEYO == g_cursor_x && cordYEYO == g_cursor_y) {
        workspace++;
      }
    }
  }
  clearCharacterMemory();
}

void startMoros() {
  cursor();
}

void getInput() { 
  scanf("%c", &c);
}
