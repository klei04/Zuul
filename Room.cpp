//Room class

#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <cstddef>

#include "Room.h"

using namespace std;

//Constructor
Room::Room(char* newRoomName) {
  strcpy(roomName, newRoomName);
  exits = new unordered_map<char*, Room*>();
  items = new vector<Item*>();
}

//Function to set an exit for the room
void Room::setExit(char* direction, Room* adjacentRoom) {
  exits->insert(make_pair(direction, adjacentRoom));
}

//Getter for roomName
char* Room::getRoomName() {
  return roomName;
}

//Getter for roomDetails: name, exits, items
char* Room::getRoomDetails() {
  char* roomDescription = new char[1000];
  strcpy(roomDescription, "You are ");
  strcat(roomDescription, roomName);
  strcat(roomDescription, "\n");
  strcat(roomDescription, getExitString());

  return roomDescription;
}

//Getter for exitString: exits, items
char* Room::getExitString() {
  char* exitString = new char[500];
  strcpy(exitString, "Exits:");
  for (unordered_map<char*, Room*>::iterator it = exits->begin(); it != exits->end(); it++) {
    strcat(exitString, " ");
    strcat(exitString, it->first);
  }

  strcat(exitString, "\nItems in the room:");
  strcat(exitString, getRoomItems());

  return exitString;
}

//Getter for roomItems
char* Room::getRoomItems() {
  char* roomItems = new char[300];

  if (items->size() == 0) {
    strcpy(roomItems, " Nothing");
  } else {
    for (vector<Item*>::iterator it = items->begin(); it != items->end(); it++) {
      strcat(roomItems, " ");
      strcat(roomItems, (*it)->getItemName());
    }
  }

  return roomItems;
}

//Getter for room exits
Room* Room::getExit(char* direction) {
  unordered_map<char*, Room*>::const_iterator it = exits->find(direction);
  if (it == exits->end()) {
    return NULL;
  } else {
    return it->second;
  }
}

//Function to find an item using index
Item* Room::getItem(int index) {
  return items->at(index);
}

//Function to find an item using the itemName
Item* Room::getItem(char* itemName1) {

  for (int i = 0; i < items->size(); i++) {
    if (strcmp(items->at(i)->getItemName(), itemName1) == 0) {
      return items->at(i);
    }
  }

  return NULL;
}

//Function to add item to the room
void Room::addItem(Item* newItem) {
  items->push_back(newItem);

}

//Function to remove item from the room
void Room::removeItem(char* itemName1) {
  for (int i = 0; i < items->size(); i++) {
     if (strcmp(items->at(i)->getItemName(), itemName1) == 0) {
       items->erase(items->begin()+i);
       break;
     } 
  }
}
