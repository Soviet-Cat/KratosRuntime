#include "kratos_platform.h"
#include <iostream>

using namespace kratos;

int main() {
    platform::Window window = platform::WindowManager::createWindow();
    std::cout << platform::WindowManager::hasWindow(window) << "\n";
    std::cout << platform::WindowManager::isValid(window) << "\n";

    system("pause");

    platform::WindowManager::destroyWindow(window);
    std::cout << platform::WindowManager::hasWindow(window) << "\n";
    std::cout << platform::WindowManager::isValid(window) << "\n";
    return 0; 
}