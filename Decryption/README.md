In this program, I mainly construct programs, including following functions

`void Decryption(string firstfile, string secondfile, long long p, long long q);` - taken in the long long int in input file, and transfer them back to string of letters and spaces into output file
    - Specific rules: 00 means space, while 01 means 'a', 02 means 'b', and so on (26 means 'z')
    - I Use ASCII values to solve the transfomration

`void Encryption(string filename, long long n, string message);` - turn user's message into two long long int, and change them to C with Modular_exp()

`long long Modular_exp(long long M, long long e, long long n);` - found the mol of large numbers

`long long euclidean(long long p, long long q);` - return the greatest common devisor of two numbers

`long long extended_euclidean(long long p, long long q);` - return the d in Bézout's identity

`void order_execute(string test,long long p, long long q);` - take in user's input, and based on the input to determine which function to use

`void exit_prog();` - gracefully terminate the program

As a summary, I took in a message (string) and first decrypt into numbers and then transferred back to strings

Besides the main RSA_Algorithm.cpp file, I also created a Makefile for easy compilation
- Simply type "make", the executable rsa would be created and user can type in another commands for encryption of decryption of message
