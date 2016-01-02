#include <iostream>
#include <cstring>

int main(void) {
    char data[] = "12345678";
    std::memcpy(data + 3, data, 3);
    std::cout << data << std::endl;
    std::memcpy(data + 3, data, 4);
    std::cout << data << std::endl;
    return 0;
}