#include <iostream>

int main() {
    std::string target;
    std::cout << "Who should we say hello to?: ";
    std::cin >> target;
    std::cout << "Hello " << target << "!" << std::endl;

    return 0;
}