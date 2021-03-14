//This is a Zuul game, where the user can move around various rooms.
//The player can pick up items and drop items.
//The goal is to collect all 5 robot chips and bring them to the robot lab.
//Author: Kevin Lei
//Date: March 14, 2021
//Credits: Borrowed much of the code from the "World of Zuul" Java application.
//"World of Zuul" was created by Michael Kolling and David J. Barnes

//Main Class

#include <iostream>
#include <cstring>
#include <vector>
#include "Command.h"
#include "CommandWords.h"
#include "Item.h"
#include "Parser.h"
#include "Room.h" 

using namespace std;


//Function prototypes
void createRooms(vector<Room*>* &rooms, Room* &currentRoom);
void printWelcome();
bool processCommand(Command command, vector<Item*>* &inventory, Room* &currentRoom, Parser* parser);
bool quit(Command command);
void printHelp(Parser* parser);
void printInventory(vector<Item*>* inventory);
void dropItem(Command command, vector<Item*>* &inventory, Room* &currentRoom);
void getItem(Command command, vector<Item*>* &inventory, Room* &currentRoom);
bool goRoom(Command command, Room* &currentRoom, vector<Item*>* inventory); 

//Main Function
int main() {
  Room* currentRoom;
  vector<Room*>* rooms = new vector<Room*>();
  vector<Item*>* inventory = new vector<Item*>();
  Parser* parser = new Parser();

  createRooms(rooms, currentRoom);

  printWelcome();
  cout << currentRoom->getRoomDetails() << endl;

  //Game continues as long as finished is false
  bool finished = false;
  while (!finished) {
    Command command = parser->getCommand();
    finished = processCommand(command, inventory, currentRoom, parser);
    //cout << finished << endl;


  }
  cout << "Thanks for playing. Goodbye." << endl;
}

//Function to print welcome message.
void printWelcome() {
  cout << "Welcome to Robot Adventure!" << endl;
  cout << "In Robot Adventure, your mission is to collect all the lost robot chips." << endl << "Bring them back to the robot laboratory" << endl;
  cout << "Type 'help' if you need help." << endl << endl;
}

//Function to create all rooms and their exits, initialize objects and their locations
void createRooms(vector<Room*>* &rooms, Room* &currentRoom) {
  Room* outside = new Room((char*)("outside the main entrance of the university"));
  Room* theatre = new Room((char*)("in a lecture theatre"));
  Room* pub = new Room((char*)("in the campus pub"));
  Room* lab = new Room((char*)("in a computing lab"));
  Room* office = new Room((char*)("in the computing admin office"));
  Room* onetwenty = new Room((char*)("in the coolest place in the world"));
  Room* bathroom = new Room((char*)("in the bathroom"));
  Room* robotlab = new Room((char*)("in the robot lab"));
  Room* courtyard = new Room((char*)("in the courtyard"));
  Room* library = new Room((char*)("in the library"));
  Room* security = new Room((char*)("in the campus security office"));
  Room* closet = new Room((char*)("in the janitor's closet"));
  Room* parking = new Room((char*)("in the parking lot"));
  Room* english = new Room((char*)("in the English room"));
  Room* locker = new Room((char*)("in the locker room"));
  Room* gym = new Room((char*)("in the gym"));
  Room* field = new Room((char*)("on the field"));

  outside->setExit((char*)("east"), theatre);
  outside->setExit((char*)("south"), lab);
  outside->setExit((char*)("west"), pub);
  outside->setExit((char*)("north"), onetwenty);
        
  theatre->setExit((char*)("west"), outside);
  theatre->setExit((char*)("east"), courtyard);
  theatre->setExit((char*)("north"), security);

  pub->setExit((char*)("east"), outside);
  pub->setExit((char*)("south"), locker);
  pub->setExit((char*)("west"), gym);

  lab->setExit((char*)("north"), outside);
  lab->setExit((char*)("east"), office);
  lab->setExit((char*)("south"), bathroom);

  office->setExit((char*)("west"), lab);
        
  onetwenty->setExit((char*)("south"), outside);
  onetwenty->setExit((char*)("north"), closet);
  onetwenty->setExit((char*)("west"), english);
        
  bathroom->setExit((char*)("north"), lab);
  bathroom->setExit((char*)("south"), robotlab);
        
  robotlab->setExit((char*)("north"), bathroom);
        
  courtyard->setExit((char*)("west"), theatre);
  courtyard->setExit((char*)("east"), library);
        
  library->setExit((char*)("west"), courtyard);
        
  security->setExit((char*)("south"), theatre);
        
  closet->setExit((char*)("south"), onetwenty);
  closet->setExit((char*)("north"), parking);
        
  parking->setExit((char*)("south"), closet);
        
  english->setExit((char*)("east"), onetwenty);
        
  locker->setExit((char*)("north"), pub);
        
  gym->setExit((char*)("east"), pub);
  gym->setExit((char*)("west"), field);
        
  field->setExit((char*)("east"), gym);

        currentRoom = outside;  // start game outside
        
onetwenty->addItem(new Item((char*)("RobotChip1")));
field->addItem(new Item((char*)("RobotChip2")));
pub->addItem(new Item((char*)("RobotChip3")));
office->addItem(new Item((char*)("RobotChip4")));
security->addItem(new Item((char*)("RobotChip5")));

	rooms->push_back(outside);
	rooms->push_back(theatre);
	rooms->push_back(pub);
	rooms->push_back(lab);
	rooms->push_back(office);
	rooms->push_back(onetwenty);
	rooms->push_back(bathroom);
	rooms->push_back(robotlab);
	rooms->push_back(courtyard);
	rooms->push_back(library);
	rooms->push_back(security);
	rooms->push_back(closet);
	rooms->push_back(parking);
	rooms->push_back(english);
	rooms->push_back(locker);
	rooms->push_back(gym);
	rooms->push_back(field);
}

//Function that processes the user's command and employs the specific function
bool processCommand(Command command, vector<Item*>* &inventory, Room* &currentRoom, Parser* parser) 
    {
        bool wantToQuit = false;

	//Runs if user inputs unknown command
        if(command.isUnknown()) {
	  cout << "I don't know what you mean..." << endl;
            return false;
        }

        char commandWord[20];
	strcpy(commandWord, command.getCommandWord());

	//Checks for specific commands and calls the function
        if (strcmp(commandWord, "help") == 0) {
            printHelp(parser);
        }
        else if (strcmp(commandWord, "go") == 0) {
	  wantToQuit = goRoom(command, currentRoom, inventory);
        }
        else if (strcmp(commandWord, "quit") == 0) {
            wantToQuit = quit(command);
        }
        
        else if (strcmp(commandWord, "inventory") == 0) {
	  printInventory(inventory);
        }
        
        else if (strcmp(commandWord, "get") == 0) {
	  getItem(command, inventory, currentRoom);
        }
        
        else if (strcmp(commandWord, "drop") == 0) {
	  dropItem(command, inventory, currentRoom);
        }
        return wantToQuit;
    }

    //Function to drop an item from the inventory into a room
void dropItem(Command command, vector<Item*>* &inventory, Room* &currentRoom) 
    {
      //Runs if user does not specify item
        if(!command.hasSecondWord()) {
	  cout << "Drop what?" << endl;
            return;
        }

        char item[100];
	strcpy(item, command.getSecondWord());

	//Locates item in the inventory
        Item* newItem = NULL;
        int index = 0;
        for (int i = 0; i < inventory->size(); i++) {
	  if (strcmp(item, inventory->at(i)->getItemName()) == 0) {
	    newItem = inventory->at(i);
	    index = i;
	    break;
            //currentRoom->addItem(newItem);
            //cout << "Dropped " << item << endl;
	  }
        }

	if (newItem == NULL) {	//Runs if item is not found in inventory
	  cout << "No such item in your inventory." << endl;
	} else {  //Item is added to room and removed from inventory
	  currentRoom->addItem(newItem);
          cout << "Dropped " << item << endl;
	  inventory->erase(inventory->begin() + index);
	}
    }
    
    
//Function to pick up an item from a room and add to inventory
void getItem(Command command, vector<Item*>* &inventory, Room* &currentRoom) 
    {
      if(!command.hasSecondWord()) { //Item not specified
	  cout << "Get what?" << endl;
            return;
        }

        char item[100];
	strcpy(item, command.getSecondWord());

        Item* newItem = currentRoom->getItem(item);

        if (newItem == NULL) //Runs if item is not found in room
	  cout << "That item is not here!" << endl;
        else { //Removes item from room and adds to inventory
            inventory->push_back(newItem);
            currentRoom->removeItem(item);
            cout << "Picked up " << item << endl;
        }
    }
    
    //Function to print inventory
    void printInventory(vector<Item*>* inventory) {
		char output[500] = "";
		for (int i = 0; i < inventory->size(); i++) {
		  strcat(output, inventory->at(i)->getItemName());
		  strcat(output, " ");
		}
		
		cout << "You are carrying:" << endl;
		if (inventory->size() == 0) {
		  cout << "nothing" << endl;
		  return;
		}
		cout << output << endl;
	}

    //Prints out goal of the game and helpful command words.
    void printHelp(Parser* parser) 
    {
      cout << "In Robot Adventure, your mission is to collect all the lost robot chips." << endl << "Bring them back to the robot laboratory" << endl << endl;
      cout << "Your command words are:" << endl;
        parser->showCommands();
    }

//Function to move into an adjacent room
bool goRoom(Command command, Room* &currentRoom, vector<Item*>* inventory) 
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
	  cout << "Go where?" << endl;
            return false;
        }

        char direction[10];
	strcpy(direction, command.getSecondWord());

        // Try to leave current room.
        Room* nextRoom = NULL;

	if (strcmp(direction, "north") == 0) {
    nextRoom = currentRoom->getExit((char*)("north"));
  }
  else if (strcmp(direction, "east") == 0) {
    nextRoom = currentRoom->getExit((char*)("east"));
  }
  else if (strcmp(direction, "south") == 0) {
    nextRoom = currentRoom->getExit((char*)("south"));
  }
  else if (strcmp(direction, "west") == 0) {
    nextRoom = currentRoom->getExit((char*)("west"));
  }

        if (nextRoom == NULL)
	  cout << "There is no door!" << endl;
        else {
            currentRoom = nextRoom;
            cout << currentRoom->getRoomDetails() << endl;

	    //Checks win condition: if current room is robot lab and all robot chips are in inventory
            if (strcmp(currentRoom->getRoomName(), "in the robot lab") == 0) {
	      for (int i = 0; i < inventory->size(); i++) {
		if (strcmp(inventory->at(i)->getItemName(), "RobotChip1") == 0) {
    					for (int i1 = 0; i1 < inventory->size(); i1++) {
    	    				if (strcmp(inventory->at(i1)->getItemName(), "RobotChip2") == 0) {
    	    					for (int i11 = 0; i11 < inventory->size(); i11++) {
    	    	    				if (strcmp(inventory->at(i11)->getItemName(), "RobotChip3") == 0) {
    	    	    					for (int i111 = 0; i111 < inventory->size(); i111++) {
    	    	    	    				if (strcmp(inventory->at(i111)->getItemName(), "RobotChip4") == 0) {
    	    	    	    					for (int i1111 = 0; i1111 < inventory->size(); i1111++) {
    	    	    	    	    				if (strcmp(inventory->at(i1111)->getItemName(), "RobotChip5") == 0) {
								  cout << "You win!" << endl;
    	    	    	    	    					return true;
    	    	    	    	    				}
    	    	    	    	    			}
    	    	    	    				}
    	    	    	    			}
    	    	    				}
    	    	    			}
    	    				}
    	    			}
    				}
    			}
        	}
        }
        return false;
    }

// Function to quit game
     bool quit(Command command) 
    {
        if(command.hasSecondWord()) {
	  cout << "Quit what?" << endl;
            return false;
        }
        else
            return true;  // signal that we want to quit
    }
