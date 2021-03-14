//Header for CommandWords class

#include <iostream>
#include <cstring>
#include <vector>

#pragma once

using namespace std;

class CommandWords {
 private:
  char* validCommands[6] = {(char*)("go"), (char*)("quit"), (char*)("help"), (char*)("inventory"), (char*)("get"), (char*)("drop")};
 public:
  bool isCommand(char* aString);
  void showAll();
};
