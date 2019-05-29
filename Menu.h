#ifndef Menu_h
#define Menu_h

typedef void (*MENU_ACTION)();

using namespace std;

class MenuOption
{
    public:
      MenuOption(const String& choice, const String& label, MENU_ACTION action);
      void print(const Print& dest);
      void Invoke();
    
};

class Menu {
    public:
        Menu(const String& title);
        void print(Print& dest);
        void addOption(const String& choice, const String& label, MENU_ACTION action);

    private:
        String _title;
        std::vector<MenuOption> _options;
};

extern void printMenu();

#endif