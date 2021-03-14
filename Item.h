//Header for Item class

#include <iostream>
#include <cstring>
#include <vector>

#pragma once

using namespace std;

class Item {
 private:
  char itemName[100];
 public:
  char* getItemName();
  Item(char* newItemName);
};

  
