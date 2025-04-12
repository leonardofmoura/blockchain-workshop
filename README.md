# Decoding the Blockchain: Cryptography and the Power of Proof

**Setup Instructions:** https://logicand.com/lectures/blockchain-workshop/

## Dependencies

Our development environment depends on the following packages:

- `cmake`: C++ build system
- `build-essential`: Set of basic tools for compilation, includes the `gcc` compiler.
- `libsodium`: Powerful cryptographic library with a simple API
- `pkg-config`: Package compiler and linker, used to link `libsodium`

### Native Install

In most Linux distributions all the dependencies can be installed via a package manager.

For debian-based distributions:

```bash {linenos=false}
sudo apt install cmake build-essential pkg-config libsodium-dev
```

For arch-based distributions:

```bash {linenos=false}
sudo pacman -S cmake base-devel pkgconf libsodium
```

### Docker Container

You can use the provided `Dockerfile` to compile the exercises. You start 
by building the container:

```bash {linenos=false}
docker build -t blockchain-workshop .
```

And run it, creating a volume in your current directory (will be useful to edit code in your editor, and compile in the container). In this example, we map our current directory to `/test` in the container:


```sh {linenos=false}
docker run -it -v `pwd`:/test blockchain-workshop
```

### Testing the Setup 

To test the setup, we will use a simple program to get the `sha256` hash of 
the `hello world!` string using `libsodium` and print the result to the screen. That example is in the directory `0-setup/`.

To run the example you have to go inside the `0-setup/` directory and run `cmake`:

```bash {linenos=false}
cmake -S . -B build
```

Then, you can compile the contents of `./build`:

```bash {linenos=false}
cmake --build build
```

If your setup is correct, the program should compile without errors and you should be able to execute it:

```bash {linenos=false}
./build/test-setup
```

After executing, you should be able to see the following output:

```sh {linenos=false}
hash:  7509e5bda0c762d2bac7f90d758b5b2263fa01ccbc542ab5e3df163be08e6ca9
```

## Compilation

All tasks are compiled using the `CMakeLists.txt` in the root of the repository. You can compile using the same `cmake` setup as previously:


```bash {linenos=false}
cmake -S . -B build
```
Followed by:

```bash {linenos=false}
cmake --build build
```
Then you can run the program for the task you are working in by running
the respective task inside the `build/` directory:

```bash {linenos=false}
./build/<task_directory>/<executable_name>
```

## Tasks

### Task 1 - Cryptography

The files for task one are inside `1-cryptography`. The steps are the following:

1. Use Blake2b to hash the string: “Blockchain is cool!”
2. Create a ed2559 keypair
3. Sign the message “ENEI 2025”
4. Verify the signature
5. Try again with a different key/message and see the verification failing

### Task 2.1 - Simple Block 

The files for task one are inside `2.1-simple-block`. The steps are the following:

1. Implement a SimpleBlock class including
    - The hash of the block
    - The hash of the parent 
    - A string of data
2. Create a simple blockchain by chaining those blocks

### Task 2.2 - Simple Cyptocurrency

The files for task one are inside `2.2-blockchain` and you should edit the `2.2-blockchain/block-test` file. The steps are the following:

1. Create a Genesis Block
2. Create your two wallets
3. Add a coinbase transaction to the block
4. Mine it
5. Create a Second Block
6. Send coins to the second wallet
7. Add a coinbase transaction to the second block
8. Mine the block
9. See the resulting blockchain

### Task 2.3 - Simple Cryptocurrency Node

The files for task one are inside `2.2-blockchain` and you should edit the `2.2-blockchain/node-test` file. The steps are the following:

1. Create a node
2. Create another wallet
3. Create a genesis block and mine it
4. Send money to the second wallet
5. Mine the second block
6. Check the balances of both wallets


