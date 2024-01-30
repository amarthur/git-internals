#include "cli.hpp"

#include <iostream>

#include "data.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./ugit"
                  << " [not implemented]" << std::endl;
        return 1;
    }

    if (argv[1] == std::string("init")) {
        init();
    } else if (argv[1] == std::string("hash-object")) {
        hashObject(std::string(argv[2]));
    } else if (argv[1] == std::string("cat-file")) {
        catFile(std::string(argv[2]));
    }

    return 0;
}

void init() {
    Data::init();
    std::cout << "Initialized ugit repository." << std::endl;
}

void hashObject(const std::string& filePath) {
    std::cout << Data::hashObject(filePath) << std::endl;
}

void catFile(const std::string& oid) { Data::getObject(oid, ""); }