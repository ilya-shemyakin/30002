// printMenu.h

              /*
---- Описание функционала меню ----
              */

#ifndef PRINT_MENU_H
#define PRINT_MENU_H
namespace printmenu {
  void spinningCursor(std::atomic<bool>& running);
  void runSpinnerUntilInput();
  void kursachOut();
  void printMenu();
}
#endif 