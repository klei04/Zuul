//CommandWords class

#include <iostream>
#include <cstring>
#include <vector>

#include "CommandWords.h"

using namespace std;

//Checks is a phrase is a valid command word
bool CommandWords::isCommand(char* aString) {
  for (int i = 0; i < 6; i++) {
    if (strcmp(aString, validCommands[i]) == 0) {
      return true;
    }
  }
  return false;
}

//Shows all valid commands
void CommandWords::showAll() {
  for (int i = 0; i < 6; i++) {
    cout << validCommands[i] << " ";
  }
  cout << endl;
}
