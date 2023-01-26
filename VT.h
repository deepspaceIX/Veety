#include <stdio.h>

#ifdef _WIN32
 #include <windows.h>
  void ClearScreen()
  {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
      hStdOut,
      (TCHAR) ' ',
      cellCount,
      homeCoords,
      &count
      )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
      hStdOut,
      csbi.wAttributes,
      cellCount,
      homeCoords,
      &count
      )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
  }
#endif   

char c;
char s[];

struct vector2 {
  int x, y;
};

struct vector2 vector2(int a, int b) {
  struct vector2 c = {a, b};
  return c;
}

//Window
struct vector2 g_win_size = {10, 10};
struct vector2 g_win_sizeWithTitle = {10, 10};
char g_win_title[50];
//Disables the ability to go back a workspace
int disableBack = 0;

//Cursor Configuration
struct vector2 g_cursor_pos = {1, 1};

//Global Textbox Variables
int currentTextBox = 0;
int totalTextBoxes = 0;
int textBoxChanged = 0;

//Character, clickpoints, and textboxpoints limits
char g_win_character_cords[50000];
char g_win_textBoxTexts[3000];
int g_win_characters_count = 0;

char g_cursor_clickpoints[5000];
char g_cursor_textboxpoints[5000];

char returnString[50] = "0000000000000000000000000000000000000000000000000";

int workspace = 0;

//Returns if a number is even or odd
int isEven(int num) {
  if (num % 2 == 0) {
    return 1;
  } else {
    return 0;
  };
};

//Adds a character to a string
void append_string(char *str, char c) {
  for (; *str; str++)
    ;
  *str++ = c;
  *str++ = 0;
}

//Gets the length of a string
int string_length(char * string) {
  int s = 0;
  int t = 0;
  char blankChar[] = "";
  for (s = 0; s >= 0; s += 1) {
    if (string[s] == blankChar[0]) {
      s = -10;
    } else {
      t++;
    };
  };
  return t;
}

//Gets the length of a string
int const_string_length(const char * string) {
  int s = 0;
  int t = 0;
  char blankChar[] = "";
  for (s = 0; s >= 0; s += 1) {
    if (string[s] == blankChar[0]) {
      s = -10;
    } else {
      t++;
    };
  };
  return t;
}

//Adds a point which the mouse can click to change the workspace
void addClickpoint(struct vector2 cord) {
  if (cord.x != 0 && cord.y != 0) {
    int length = string_length(g_cursor_clickpoints);

    g_cursor_clickpoints[length] = cord.x;
    g_cursor_clickpoints[length + 1] = cord.y;
  };
};

//Adds a point which the mouse can click to change a textbox
void addTextBoxPoint(struct vector2 cord, int textBoxID) {
  if (cord.x != 0 && cord.y != 0) {
    int length = string_length(g_cursor_textboxpoints);

    g_cursor_textboxpoints[length] = cord.x;
    g_cursor_textboxpoints[length + 1] = cord.y;
    g_cursor_textboxpoints[length + 2] = textBoxID;
  };
};

//Draws a character
void drawCharacter(char Character, struct vector2 cord) {
  if (cord.x != 0 && cord.y != 0) {
    int length = string_length(g_win_character_cords);

    g_win_character_cords[length] = Character;
    g_win_character_cords[length + 1] = cord.x;
    g_win_character_cords[length + 2] = cord.y;
    g_win_characters_count++;
  };
};

//Draws a character and adds a clickpoint
void drawCharacterClickpoint(char Character, struct vector2 cord) {
  if (cord.x != 0 && cord.y != 0) {
    int length = string_length(g_win_character_cords);
    g_win_character_cords[length] = Character;
    g_win_character_cords[length + 1] = cord.x;
    g_win_character_cords[length + 2] = cord.y;
    g_win_characters_count++;

    addClickpoint(cord);
  };
};

//Returns a 1 if the textboxid is valid, returns 0 if not
int doesTextBoxExist(int textBoxID) {
  int i;
  int totalTextBoxes = -1;
  for (i = 0; i <= string_length(g_win_textBoxTexts); i++)
  {
    if (g_win_textBoxTexts[i] == '`')
    {
      totalTextBoxes++;
    };
    if (totalTextBoxes == textBoxID)
    {
      return 1;
    };
  };
  return 0;
};

//Returns the text from a certain textbox
char *returnTextBoxText(int textBoxID, char * textBoxTexts) {
  int i;
  for (i = 0; i <= 50; ++i) {
    returnString[i] = 0;
  };

  int textBoxTextLength = string_length(textBoxTexts);
  int textPosition = 1;
  int textBoxesDetected = -1;
  for (i = 0; i <= textBoxTextLength; i++) {
    if (g_win_textBoxTexts[i] == '`') {
      textBoxesDetected++;
      if (textBoxID == textBoxesDetected) {
        textPosition = i;
      };
    };
  };

  int stopChecking = 0;
  for (i = 1; i <= 50; i++) {
    if (g_win_textBoxTexts[textPosition + i] == '`') {
      stopChecking = 1;
    } else if (stopChecking == 0) {
      returnString[i - 1] = g_win_textBoxTexts[textPosition + i];
    };
  };

  return returnString;
}

//Adds a piece of a text to a textbox
void addTextBoxText(char string[50]) {
  int i;
  int textBoxTextLength = string_length(g_win_textBoxTexts);
  int stringLength = string_length(string);
  int foundStart = 0;
  for (i = 0; i <= textBoxTextLength; i++) {
    if (g_win_textBoxTexts[i] == '`') {
      foundStart = 1;
    };
  };
  if (foundStart != 1) {
    g_win_textBoxTexts[0] = '`';
  };

  if (foundStart == 1) {
    if (g_win_textBoxTexts[textBoxTextLength - 1] != '`') {
      g_win_textBoxTexts[textBoxTextLength] = '`';
    };
  };
  int textBoxTextLength2 = string_length(g_win_textBoxTexts);
  int n = 0;
  for (i = textBoxTextLength2; i <= stringLength + textBoxTextLength2; i++) {
    g_win_textBoxTexts[i] = string[n];
    n++;
  };
};

//Edits a piece of text from a textbox
void editTextBoxText(int textBoxID, char newString[]) {
  int i;
  int t = -1;
  int textBoxPosition = 0;
  int totalTextBoxesFound = -1;

  for (i = 0; i <= string_length(g_win_textBoxTexts); i++) {
    if (g_win_textBoxTexts[i] == '`') {
      totalTextBoxesFound++;
    };
  };

  for (i = 0; i <= string_length(g_win_textBoxTexts); i++) {
    if (g_win_textBoxTexts[i] == '`') {
      t++;
      if (t == textBoxID) {
        textBoxPosition = i;
      };
    };
  };
  int newStringLength = string_length(newString) + 1;
  int oldStringNewPosition = textBoxPosition + newStringLength;
  int oldStringPosition = 0;

  char oldString[1000];
  int stopActive = 0;
  for (i = textBoxPosition + 1; i <= string_length(g_win_textBoxTexts); i++) {
    if (g_win_textBoxTexts[i] == '`' && stopActive == 0) {
      oldStringPosition = i;
      stopActive = 1;
    };
  };

  t = -1;
  for (i = oldStringPosition; i <= string_length(g_win_textBoxTexts); i++) {
    t++;
    oldString[t] = g_win_textBoxTexts[i];
  };

  if (totalTextBoxesFound != textBoxID) {
    t = -1;
    for (i = oldStringNewPosition; i <= string_length(g_win_textBoxTexts) + newStringLength + 4; i++) {
      t++;
      g_win_textBoxTexts[i] = oldString[t];
    };
  };
  t = -1;
  for (i = textBoxPosition; i <= string_length(g_win_textBoxTexts); i++) {
    t++;
    g_win_textBoxTexts[i + 1] = newString[t];
  };
  if (totalTextBoxesFound != textBoxID) {
    t = -1;
    for (i = oldStringNewPosition; i <= oldStringNewPosition + string_length(newString) + 30; i++) {
      t++;
      g_win_textBoxTexts[i] = oldString[t];
    };
  };
};

//Draws a character that has the traits of a textbox
void drawCharacterTextBox(char Character, struct vector2 cord, int textBoxID) {
  if (cord.x != 0 && cord.y != 0) {
    int length = string_length(g_win_character_cords);

    g_win_character_cords[length] = Character;
    g_win_character_cords[length + 1] = cord.x;
    g_win_character_cords[length + 2] = cord.y;
    g_win_characters_count++;

    addTextBoxPoint(cord, textBoxID);
  };
};

//Draws a set of characters all at once
void drawString(char * string, struct vector2 cord) {
  int stringLength = string_length(string);
  int p;
  for (p = 0; p <= stringLength - 1; p++) {
    drawCharacter(string[p], vector2(cord.x + p, cord.y));
  };
};

//Draws a set of characters all at once with each of them having the trait of a clickpoint
void drawStringClickpoint(char * string, struct vector2 cord) {
  int stringLength = string_length(string);
  int p;

  for (p = 0; p <= stringLength - 1; p++) {
    drawCharacterClickpoint(string[p], vector2(cord.x + p, cord.y));
  };
};

//Draws a set of characters all at once with each of them having the trait of a textbox
void drawStringTextBox(char * string, struct vector2 cord, int textBoxID) {
  int stringLength = string_length(string);
  int p;

  for (p = 0; p <= stringLength - 1; p++) {
    drawCharacterTextBox(string[p], vector2(cord.x + p, cord.y), textBoxID);
  };
};

//Draws a set of characters with the trait of a button but looks nicer
void button(struct vector2 cord, char * centerText) {
  int i;
  int centerTextLength = string_length(centerText);

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacterClickpoint('=', vector2(cord.x + i, cord.y));
  };
  drawCharacterClickpoint('=', vector2(cord.x, cord.y + 1));
  drawCharacterClickpoint(' ', vector2(cord.x + 1, cord.y + 1));
  drawStringClickpoint(centerText, vector2(cord.x + 2, cord.y + 1));
  drawCharacterClickpoint(' ', vector2(centerTextLength + cord.x + 2, cord.y + 1));
  drawCharacterClickpoint('=', vector2(cord.x + centerTextLength + 3, cord.y + 1));

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacterClickpoint('=', vector2(cord.x + i, cord.y + 2));
  };
  drawCharacterClickpoint(' ', vector2(centerTextLength + 4, cord.y + 2));
};

//Draws the cursor wherever it is placed
void cursor() {
  int length = string_length(g_win_character_cords);
  int p;

  char charCursorIcon = '^';

  for (p = 0; p <= length - 1; p += 2) {
    int cordXEYO = g_cursor_clickpoints[p - 2];
    int cordYEYO = g_cursor_clickpoints[p - 1];
    if (cordXEYO == g_cursor_pos.x && cordYEYO == g_cursor_pos.y) {
      charCursorIcon = '!';
    };
  };

  drawCharacter(charCursorIcon, vector2(g_cursor_pos.x, g_cursor_pos.y));
};

//Clears all the arrays 
void clearCharacterMemory()
{
  int i;
  for (i = 0; i < 50000; ++i) {
    g_win_character_cords[i] = 0;
  };
  for (i = 0; i < 5000; ++i) {
    g_cursor_clickpoints[i] = 0;
  };
  for (i = 0; i < 5000; ++i) {
    g_cursor_textboxpoints[i] = 0;
  };

  g_win_characters_count = 0;
  totalTextBoxes = 0;
};

//Disables the ability to use the '<' key to go back a workspace
void disableBackFucntion() {
  disableBack = 1;
};

//Gets the currently used workspace
int getWorkspace() {
  return workspace;
};

//Draws a line based on a y=mx+b equation
void drawLine(char axis, float slope, struct vector2 pos) {
  char lineCharacter = '+';
  if (axis == 'y') {
    if (slope == 0) {
      lineCharacter = '-';
    } else if (slope < 0) {
      lineCharacter = '\\';
    } else if (slope > 0) {
      lineCharacter = '/';
    };
  } else if (axis == 'x') {
    if (slope == 0) {
      lineCharacter = '|';
    } else if (slope > 0) {
      lineCharacter = '/';
    } else if (slope < 0) {
      lineCharacter = '\\';
    };
  };

  int i;
  for (i = 0; i <= g_win_size.y; i++) {
    struct vector2 cord = {(i * -slope) + pos.x, (i * -slope) + pos.y};
    if (axis == 'y') {
      drawCharacter(lineCharacter, vector2(pos.x + i, cord.y));
    } else if (axis == 'x') {
      drawCharacter(lineCharacter, vector2(cord.x, pos.y + i));
    };
  };
  for (i = 0; i <= g_win_size.y; i++) {
    struct vector2 cord = {(i * slope) + pos.x, (i * slope) + pos.y};
    if (axis == 'y') {
      drawCharacter(lineCharacter, vector2(pos.x - i, cord.y));
    } else if (axis == 'x') {
      drawCharacter(lineCharacter, vector2(cord.x, pos.y - i));
    };
  };
};

//Just like the button function this does the same thing except its a textbox
void TextBox(char placeHolder[], struct vector2 pos) {
  int i;

  totalTextBoxes++;

  if (doesTextBoxExist(totalTextBoxes - 1) == 0) {
    addTextBoxText(placeHolder);
  };

  int centerTextLength = string_length(returnTextBoxText(totalTextBoxes - 1, g_win_textBoxTexts));
  char * receivedString = returnTextBoxText(totalTextBoxes - 1, g_win_textBoxTexts);

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacterTextBox('-', vector2(pos.x + i, pos.y), totalTextBoxes);
  };
  drawCharacterTextBox('~', vector2(pos.x, pos.y + 1), totalTextBoxes);
  drawCharacterTextBox(' ', vector2(pos.x + 1, pos.y + 1), totalTextBoxes);

  drawStringTextBox(receivedString, vector2(pos.x + 2, pos.y + 1), totalTextBoxes);

  drawCharacterTextBox(' ', vector2(centerTextLength + pos.x + 2, pos.y + 1), totalTextBoxes);
  drawCharacterTextBox('~', vector2(pos.x + centerTextLength + 3, pos.y + 1), totalTextBoxes);

  for (i = 0; i < centerTextLength + 4; i++) {
    drawCharacterTextBox('-', vector2(pos.x + i, pos.y + 2), totalTextBoxes);
  };
  drawCharacterTextBox(' ', vector2(centerTextLength + 4, pos.y + 2), totalTextBoxes);
};

//Draws the whole window to the console
void window() {
  int sizeX = g_win_size.x;
  int sizeY = g_win_size.y;
  if (isEven(sizeX) == 1) {
    #ifdef _WIN32
      ClearScreen();
    #else
      printf("\e[1;1H\e[2J");
    #endif   

    int sizeXDV2 = g_win_size.x / 2;
    int titleLength = string_length(g_win_title);
    g_win_sizeWithTitle.x = g_win_size.x + titleLength;
    g_win_sizeWithTitle.y = sizeY;

    int i;
    int e;

    printf("+");
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    };
    printf("%s", g_win_title);
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    };
    printf("+\n");

    for (e = 1; e <= sizeY; e++) {
      printf("|");
      for (i = 1; i <= g_win_size.x + 2 + string_length(g_win_title); i++) {
        int o = 2;
        int w;
        int drawn = 0;
        int drawnCharacters = 0;
        int length = string_length(g_win_character_cords);

        for (; o <= length - 1; o += 3) {
          char charEYO = g_win_character_cords[o - 2];
          struct vector2 cordEYO = {g_win_character_cords[o - 1], g_win_character_cords[o]};

          if (cordEYO.x == i && cordEYO.y == e) {
            if (drawnCharacters >= 1) {
              break;
            } else {
              printf("%c", charEYO);
              drawn = 1;
              drawnCharacters++;
            };
          };
        };
        if (drawn == 0) {
          printf(" ");
        };
      };
      printf("|\n");
    };
    printf("+");
    for (i = 0; i <= sizeXDV2; i++) {
      printf("-");
    };
    for (i = 0; i <= string_length(g_win_title); i++) {
      printf("-");
    };
    for (i = 0; i <= sizeXDV2 - 1; i++) {
      printf("-");
    };
    printf("+\n");
  } else {
    printf("x be even for code to work");
  };
  if (currentTextBox == 0) {
    if (c == '<') {
      if (disableBack != 1) {
        if (workspace > 0) {
          workspace--;
        };
      };
    };
    if (c == 'd') {
      if (g_cursor_pos.x > g_win_sizeWithTitle.x + 1) {
        g_cursor_pos.x = 1;
      } else {
        g_cursor_pos.x += 1;
      };
    };
    if (c == 'a') {
      if (g_cursor_pos.x < 2) {
        g_cursor_pos.x = g_win_sizeWithTitle.x + 2;
      } else {
        g_cursor_pos.x -= 1;
      };
    };
    if (c == 'w') {
      if (g_cursor_pos.y < 2) {
        g_cursor_pos.y = sizeY;
      } else {
        g_cursor_pos.y -= 1;
      };
    };
    if (c == 's') {
      if (g_cursor_pos.y > g_win_sizeWithTitle.y - 1) {
        g_cursor_pos.y = 1;
      } else {
        g_cursor_pos.y += 1;
      };
    };
    if (c == ' ') {
      int o;
      int length = string_length(g_cursor_clickpoints);
      int length2 = string_length(g_cursor_textboxpoints);

      for (o = 0; o <= length - 1; o += 2) {
        struct vector2 cordEYO = {g_cursor_clickpoints[o - 2], g_cursor_clickpoints[o - 1]};
        if (cordEYO.x == g_cursor_pos.x && cordEYO.y == g_cursor_pos.y){
          workspace++;
        };
      };

      for (o = -1; o <= length2; o += 3) {
        struct vector2 cordEYO = {g_cursor_textboxpoints[o - 2], g_cursor_textboxpoints[o - 1]};
        int textBoxID = g_cursor_textboxpoints[o];

        if (cordEYO.x == g_cursor_pos.x && cordEYO.y == g_cursor_pos.y){
          currentTextBox = textBoxID;
        };
      };
    };
  };
  clearCharacterMemory();
};

//Starts up VT
void startVT(struct vector2 size, char * g_title) {
  if (currentTextBox == 0) {
    cursor();
  };
  int i;
  g_win_size.x = size.x;
  g_win_size.y = size.y;
  for (i = 0; i <= 50; i++) {
    g_win_title[i] = g_title[i];
  };
};

//Gets the inputs from the keyboard to change the screen
void getInput() {
  if (textBoxChanged == 0) {
    if (currentTextBox == 0) {
      scanf("%c", &c);
    } else {
      char temp;
      printf(">> ");
      scanf("%c", &temp);
      scanf("%[^\n]", &s);
      textBoxChanged = 1;
      editTextBoxText(currentTextBox - 1, s);
    };
  } else {
    textBoxChanged = 0;
    currentTextBox = 0;
    scanf("%c", &c);
  };
};
