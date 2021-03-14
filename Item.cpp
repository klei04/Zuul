//Item class

#include <iostream>
#include <cstring>
#include <vector>

#include "Item.h"

using namespace std;

//Constructor
Item::Item(char* newItemName) {
  strcpy(itemName, newItemName);
}

//Getter for itemName
char* Item::getItemName() {
  return itemName;
}
