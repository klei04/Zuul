//Header for Room class

#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>

#include "Item.h"

#pragma once

using namespace std;

class Room {
 private:
  char roomName[100];
  vector<Item*>* items;
  char* getExitString(); //

 public:
  Room(char* newRoomName); //
  unordered_map<char*, Room*>* exits;
  void setExit(char* direction, Room* adjacentRoom); //
  char* getRoomName(); //
  char* getRoomDetails(); //
  Room* getExit(char* direction);
  char* getRoomItems();
  Item* getItem(int index);
  Item* getItem(char* itemName1);
  void addItem(Item* newItem);
  void removeItem(char* itemName1);
};
