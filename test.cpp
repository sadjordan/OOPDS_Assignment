#include <iostream>
#include <string>

int main() {
    std::string str = "string";
    
    if (str[1] == 't') {
        std::cout << "True!" << std::endl;
    } else {
        std::cout << "False!" << std::endl;
    }

    return 0;
}