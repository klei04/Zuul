//Header for Parser class

#include <iostream>
#include <cstring>
#include <vector>

#include "Command.h"
#include "CommandWords.h"

#pragma once

using namespace std;

class Parser {
 private:
  CommandWords commands;
 public:
  Parser();
  Command getCommand();
  void showCommands();
};
