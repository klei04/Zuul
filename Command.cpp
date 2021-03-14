//Command class

#include <iostream>
#include <cstring>
#include <vector>

#include "Command.h"

using namespace std;

//Constructor
Command::Command(char* firstWord, char* secondWord1) {
  strcpy(commandWord, "");
  if (firstWord != NULL){
    strcpy(commandWord, firstWord);}
  strcpy(secondWord, "");
  if (secondWord1 != NULL){
    strcpy(secondWord, secondWord1);}
}

//Getter for the command word (first word)
char* Command::getCommandWord() {
  return commandWord;
}

//Getter for the second word
char* Command::getSecondWord() {
  return secondWord;
}

//Function to check if the command word exists
bool Command::isUnknown() {
  return (strcmp(commandWord, "") == 0);
}

//Function to check if there is a second word in the command
bool Command::hasSecondWord() {
  return (strcmp(secondWord,"") != 0);
}
