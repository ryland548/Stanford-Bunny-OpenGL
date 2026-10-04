#include <iostream>
#include "inc/app.hpp"

int main() {
    App app;
    if (!app.run()) {
        std::cout << "Failed to execute.\n";
        return 1;
    }
    return 0;
}
