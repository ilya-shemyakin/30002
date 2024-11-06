//printMenu.cpp

                /*
---- Реализация функционала меню ----
                */

#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <conio.h>

#include "PrintMenu.h"
#include "Colors.h"

namespace printmenu {
  // Реализация кручения "\" "|" "/" "-":
  void spinningCursor(std::atomic<bool>& running) {
    const char spinner[] = { '|', '/', '-', '\\' };
    const int num_frames = sizeof(spinner) / sizeof(spinner[0]);

    while (running) {
      for (int i = 0; i < num_frames; ++i) {
        if (!running) break;
        std::cout << "\r" << YELLOW << "[" << spinner[i] << "] Waiting..";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }
    std::cout << "\rDone!        " << std::endl;
  }

  // Функция отслеживающая до какого момента кручение продолжается:
  void runSpinnerUntilInput() {
    std::atomic<bool> running(true);

    std::thread spinnerThread(spinningCursor, std::ref(running));
    std::cout << std::endl;
    while (!_kbhit()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    running = false;
    spinnerThread.join();
  }

  // Вывод надписи "KURSACH":
  void kursachOut()
  {
    std::cout << std::setw(10) << YELLOW << ".____  __.____ _____________  _________   _____  _________   ___ ___\n";
    std::cout << std::setw(10) << YELLOW << "|    |/ _|    |   \\______   \\/   _____/  /  _  \\ \\_   ___ \\ /   |   \\\n";
    std::cout << std::setw(10) << YELLOW << "|      < |    |   /|       _/\\_____  \\  /  /_\\  \\/    \\  \\//    ~    \\\n";
    std::cout << std::setw(10) << YELLOW << "|    |  \\|    |  / |    |   \\/        \\/    |    \\     \\___\\    Y    /\n";
    std::cout << std::setw(10) << YELLOW << "|____|__ \\______/  |____|_  /_______  /\\____|__  /\\______  /\\___|_  / \n";
    std::cout << std::setw(10) << YELLOW << "        \\/                \\/        \\/         \\/        \\/       \\/  \n\n";

    std::cout << std::setw(34) << YELLOW << "Frequency Dictionary\n";
    std::cout << std::setw(28) << WHITE << "by Fedunov Vladimir 5130904/30002\n";
    std::cout << std::setw(39) << WHITE << "2024 SPBSTU\n\n";

  }
}
