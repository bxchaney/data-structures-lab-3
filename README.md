# ChaneyBLab3

## Configuration Info

Operating System: Ubuntu 22.04

C++ Compiler: g++ 11.3.0

IDE: Visual Studio Code version 1.75.1 with the most recent version of the C/C++ extension pack.

Build System: CMake 3.40

I have included my compiled executable in the top directory of this zip, it will not be overwritten when you build from source using the Makefile configuration.

## How to Build

- Assuming the user has access to GNU make. The Makefile configuration assumes that the user is in a Unix-like environment with access to the mkdir and rm commands.
- In the directory containing Makefile, run the command run `make`. This will created the directories ./build/objects and ./build/apps . ./build/objects will contain the unlinked, compiled object files used to make the program and ./build/apps will contain the final linked executable. Then, you should see the following commands as the executable is built: 

    `g++ -pedantic-errors -Wall -Wextra -Werror -Iinclude/ -c src/char_list.cpp -MMD -o build/objects/src/char_list.o`

    `g++ -pedantic-errors -Wall -Wextra -Werror -Iinclude/ -c src/converter.cpp -MMD -o build/objects/src/converter.o`

    `g++ -pedantic-errors -Wall -Wextra -Werror -Iinclude/ -c src/main.cpp -MMD -o build/objects/src/main.o`

    `g++ -pedantic-errors -Wall -Wextra -Werror -o ./build/apps/lab2.exe build/objects/src/char_list.o build/objects/src/converter.o build/objects/src/main.o -L/usr/lib -lstdc++ -lm`

- The compiled executable should now be ready at ./build/apps/lab2.exe !

## How to Run

- Once the executable is built we can run the required input by calling `./build/apps/lab2.exe Required\ Input.txt Required\ Output.txt` from the command line.
- We can run additional input by calling `./build/apps/lab2.exe Additional\ Input.txt Additional\ Output.txt`
- If you add `-r` after the output file name, then the program will process the input values as postfix and attempt to convert them to prefix. For example, try calling `./build/apps/lab2.exe  Postfix\ Input.txt Postfix\ Output.txt -r` ! 