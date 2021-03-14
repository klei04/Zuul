//Header for Command class

#include <iostream>
#include <cstring>
#include <vector>

#pragma once

using namespace std;

class Command {
 private:
  char commandWord[20];
  char secondWord[20];
 public:
  Command(char* firstWord, char* secondWord);
  char* getCommandWord();
  char* getSecondWord();
  bool isUnknown();
  bool hasSecondWord();
};
