# Blockchain C++ Container

## Integration

Simply include the `blockchain.h` header.

```cpp
#include "blockchain.h"
```

The examples below are using the namespace `bc`:

```cpp
using namespace bc;
```

## Creating a blockchain

Creating a blockchain of strings with "Hello, World!" in its genesis block:

```cpp
    blockchain<std::string> bc("Hello, World!");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;
```

## Pushing new blocks/transactions

The usual `push_back` function can be used to insert new blocks:

```cpp
    bc.push_back("A sent B a letter");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;

    bc.push_back("B sent C a post card");
    std::cout << bc.back().block_hash << ": " << bc.back().transaction << std::endl;
```

## Iterating the block chain

You can use:
 
* "for-each" loops

```cpp
    for (block<std::string> &b : bc) {
        std::cout << b.block_hash << ": " << b.transaction << std::endl;
    }
```

* iterators

```cpp
    for (blockchain<std::string>::iterator iter = bc.begin(); iter != bc.end(); ++iter) {
        std::cout << iter->block_hash << ": " << iter->transaction << std::endl;
    }
```

* indexed loops

```cpp
    for (int i = 0; i < bc.size(); i++) {
        std::cout << bc[i].block_hash << ": " << bc[i].transaction << std::endl;
    }
```

## Checking hashes

The function `check_hash` iterates the blockchain to see if there's any inconsistency with the hashes. 

```cpp
    if (bc.check_hash()){
        std::cout << "Blockchain hashes are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes are not consistent" << std::endl;
    }
```

The function `check_hash`, besides checking the hashes, recalculates the transaction hashes to make sure this hasn't been altered too.

```cpp
    if (bc.check()){
        std::cout << "Blockchain hashes and transactions are consistent" << std::endl;
    } else {
        std::cout << "Blockchain hashes and transactions are not consistent" << std::endl;
    }
```

## "Hacking" the blockchain

Someone can try to hash the block chain with:

```cpp
    // Trying to "hack" the blockchain
    bc[0].transaction = "Hello moon";
```

The functions `check_hash` and `check` described above would then return false because the chain has been invalidated.