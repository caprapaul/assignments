Name: Capra Paul-Ovidiu

# Zombies Attack Their Victims

In this lesson we learn that the Ethereum blockchain is made up of accounts that have a balance and an address which uniquely identifies the account. We also learn about mappings that are basically a key-value data structure similar to dictionaries from other languages.

Going further we learn about one of the global variables available in Solidity, `msg.sender` that contains the address of the person or smart contract calling the current function. We then learn about `require` which makes the function throw an error if a condition is not true, similar to `assert` in C/C++. Solidity also features other characteristics similar to other languages like contract inheritance (similar to class inheritance), importing code files, `if` statements, multiple return types. One particularly interesting aspect about Solidity is the `external` function visibility which makes the function **only** accessible from outside the contract. 

To interact with other contracts on the blockchain, we need to define an interface. Interfaces declare the functions we want to interact with, without defining their bodies. We then need the contract's address to call exposed functions on that contract.