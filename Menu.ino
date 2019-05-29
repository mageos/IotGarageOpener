#include "Menu.h"

void printMenu()
{
  Serial.println("  Main Menu ");
  Serial.println("=========================================");
  Serial.println(" 1. Print Network Address");
  Serial.println(" 2. Turn on Green LED");
  Serial.println(" 3. Turn on Red LED");
  Serial.println(" 4. Turn off Green LED");
  Serial.println(" 5. Turn off Red LED");
  
  //dataHandler = &processMenu;
}

Menu::Menu(const String& title)
{
  _options = std::vector<MenuOption>();
}

void Menu::print(Print& dest)
{
    dest.println(" Menu");
    dest.println("=============");
    for (std::vector<MenuOption>::iterator it = _options.begin(); it != _options.end(); ++it)
    {      
    }
}

void Menu::addOption(const String& option, const String& message, MENU_ACTION action)
{
  //_options.insert(MenuOption(option, message, action));
}

void MenuOption::print(const Print& dest)
{  
}

void MenuOption::Invoke()
{  
}