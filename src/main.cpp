#include "dotenv.h"
#include <iostream>

int main() {
    dotenv::init("../.env");

    std::cout << "Environment variable TEST_VAR: " << dotenv::getenv("TEST_VAR") << std::endl;

    return 0;
}