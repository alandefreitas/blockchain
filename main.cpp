#include <iostream>
#include <string>

#include "blockchain.h"

using namespace bc;

int main() {
    // Genesis block
    blockchain<std::string> bc("Hello, World!");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;

    // Pushing transaction
    bc.push_back("A sent B a letter");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;

    bc.push_back("B sent C a post card");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;

    // Iterating the block chain
    // For-each loop
    std::cout << "Blockchain:" << std::endl;
    for (block<std::string> &b : bc) {
        std::cout << b.block_hash << ": " << b.transaction << std::endl;
    }

    // Iterators
    std::cout << "Blockchain:" << std::endl;
    for (blockchain<std::string>::iterator iter = bc.begin(); iter != bc.end(); ++iter) {
        std::cout << iter->block_hash << ": " << iter->transaction << std::endl;
    }

    // Indexed loops
    std::cout << "Blockchain:" << std::endl;
    for (int i = 0; i < bc.size(); i++) {
        std::cout << bc[i].block_hash << ": " << bc[i].transaction << std::endl;
    }

    // Checking hashes
    if (bc.check_hash()){
        std::cout << "Blockchain hashes are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes are not consistent" << std::endl;
    }

    // Checking hashes and transaction (recalculating hashes)
    if (bc.check()){
        std::cout << "Blockchain hashes and transactions are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes and transactions are not consistent" << std::endl;
    }

    // Trying to "hack" the blockchain
    bc[0].transaction = "Hello moon";

    // Checking hashes
    if (bc.check_hash()){
        std::cout << "Blockchain hashes are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes are not consistent" << std::endl;
    }

    // Checking hashes and transactions (recalculating hashes)
    if (bc.check()){
        std::cout << "Blockchain hashes and transactions are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes and transactions are not consistent" << std::endl;
    }



    return 0;
}