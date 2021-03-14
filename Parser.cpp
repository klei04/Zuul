//Parser class

#include <iostream>
#include <cstring>
#include <vector>

#include "Parser.h"

using namespace std;

//Constructor
Parser::Parser() {
  commands = CommandWords();
}

//Function to parse the command from a user input
Command Parser::getCommand() {
  char inputLine[100];
  vector<char*> words;

  cin.get(inputLine, 100);
  cin.get();

  char* ptr;
  ptr = strtok(inputLine, " ");

  while (ptr != NULL) {
    words.push_back(ptr);
    ptr = strtok(NULL, " ");
  }

  if (words.size() > 2 || words.size() < 1) {
    return Command(NULL, NULL);
  }
  else if (commands.isCommand(words[0])) {
    if (words.size() == 2) {
      return Command(words[0], words[1]);
    }
    else {
      return Command(words[0], NULL);
    }
  }
  else {
    return Command(NULL, NULL);
  }
}

//function to show all the possible commands
void Parser::showCommands() {
  commands.showAll();
}
