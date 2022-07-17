#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

// Modular Exponentiation Algorithm
void Decryption(string firstfile, string secondfile, long long p, long long q);
void Encryption(string filename, long long n, string message);
long long Modular_exp(long long M, long long e, long long n);
long long euclidean(long long p, long long q);
long long extended_euclidean(long long p, long long q);
void order_execute(string test, long long p, long long q);
void exit_prog();

//dead with the order that user input
void order_execute(string input, long long p, long long q) {
    //Exit Case
    if (input == "EXIT")
        exit_prog();

    //ENCRYPT Message
    else if (input == "ENCRYPT") {
        string filename, message="",temp;
        long long n;
        cin >> filename;
        cin >> n;
        getline(cin,message);
        //remove first 0's 
        while(message[0]==' ')
        {
            message.erase(0,1);
        }
        Encryption(filename, n, message);
    } else if (input == "DECRYPT") {  // DECRYPT Numbers to MESSAge
        string firstfile, secondfile;
        cin >> firstfile;
        cin >> secondfile;
        Decryption(firstfile, secondfile, p, q);
    } else {
        cout << "THE INVALID MESSAGE" << endl;
        exit_prog();
    }
}

// return log of any number in the base of 100
long long log_a_base_100(long long a) { return log(a) / log(100); }

void Encryption(string filename, long long n, string message) {
    ofstream ofile(filename, fstream::trunc);


    long long e = 65537;
    //Return Error Message once the N Value is wrong
    if (n < 27) {
        cout << "N Value is BELOW 27! ERROR!" << endl;
        exit_prog();
    }
    long long x = floor(1 + log_a_base_100(n / 27));
    long long size_message = message.size();
    long long last_pos = 0, M = 0, C = 0;
    long long temp = 0;
    //ENCRYPT every x characters in each turn
    while (size_message > 0) {
        M = 0;
        for (long i = last_pos; i < x + last_pos; i++) {
            M = M * 100;
            if (i >= message.size())
                temp = 0;
            //Edge Case for web space
            else if (message[i] == ' ')
                temp = 0;
            else {
                temp = message[i] - 96;
            }
            M += temp;
        }
        last_pos += x;
        size_message -= x;
        //Calculate the C Value
        C = Modular_exp(M, e, n);
        ofile << C << " ";
    }

    ofile.close();
}

//use to find the digits of long numbers
long long get_digit_length(long long digits)
{
    long long leng=0;
    while(digits)
    {
        digits/=10;
        leng++;
    }
    return leng;
}

void Decryption(string firstfile, string secondfile, long long p, long long q) {
    ifstream ifile(firstfile);
    ofstream ofile(secondfile);

    long long n = p * q;
    long long x = floor(1 + log_a_base_100(n / 27));
    // find out possible 0's in every string of M
    long long number_of_digits = 2 * x;
    long long number_of_zero_in_start = 0;
    // decryption key
    long long d, C = 0, M = 0;
    long long e = 65537;
    // The least common multiple of p-1 and q-1 = (p-1) * (q-1) / gcd(p-1,q-1)
    long long L = 0;
    long long gcd = 0; 
    // find the gcd of p-1 and q-1 to solve for the the least common multiple
    gcd = euclidean(p - 1, q - 1);
    L = ((p - 1) * (q - 1)) / gcd;

    // if L is below 65537, output an error message and gratefully terminate
    if (L <= e) {
        cout << "L value is BELOW OR EQUAL TO E(65537)! NOT ENOUGH!" << endl;
        exit_prog();
    }

    d = extended_euclidean(e, L);
    string message_total;
    while (ifile >> C) {
        number_of_zero_in_start = 0;
        // DECRYPT C to M
        M = Modular_exp(C, d, n);
        long long digits_nonzero = get_digit_length(M);
        number_of_zero_in_start = (number_of_digits - digits_nonzero)/2;
        char temp_st[100];
        long long counter = 0;
        char t;
        long long temper = 0;
        while (M != 0) {
            temper = M % 100;
            // EDGE Case: temper == 0 , the character is space
            if (temper == 0)
                t = ' ';
            // Since 97 in long is 'a' in char, by mapping long value 1 to 'a', we need to add 96
            else {
                t = (char)(temper + 96);
            }
            temp_st[counter] = t;
            M /= 100;
            counter++;
        }

        //fill in the 0s in the start
        for(int i=0;i<number_of_zero_in_start;i++)
        {
            message_total+=' ';
        }
        // output the C-String in the reverse order
        for (long i = counter - 1; i >= 0; i--) {
            message_total+=temp_st[i];
        }
    }
    ofile << message_total;
    //Close file
    ifile.close();
    ofile.close();
}

long long Modular_exp(long long M, long long e, long long n) {
    long long C = 1;
    long long power = M % n;
    long i = 0;
    long long binary[100];
    // Switch e to binary form
    for (i = 0; e > 0; i++) {
        binary[i] = e % 2;
        e = e / 2;
    }

    for (long k = 0; k < i; k++) {
        if (binary[k] == 1) {
            C = (C * power) % n;
        }
        power = (power * power) % n;
    }
    return C;
}

// EXIT FUNCTION TO gracefully terminate the program
void exit_prog() {
    cout << "YOUR Program is Over" << endl;
    exit(0);
}

// Find the greatest common divisor of p and q
long long euclidean(long long p, long long q) {
    long long old_r = p, r = q;
    long long temp, gcd = 1;
    long long quo;

    while (r != 0) {
        quo = floor(old_r / r);
        temp = r;
        r = old_r - quo * r;
        old_r = temp;
    }
    gcd = old_r;
    return gcd;
}

//find the d in Bézout's identity
long long extended_euclidean(long long e, long long L) {
    // return the decryption key
    long long d = 0;
    long long t = 1, old_t = 0;
    long long r = e, old_r = L;
    long long quo = 0, temp = 0;

    while (r != 0) {
        // gcd
        quo = floor(old_r / r);
        temp = r;
        r = old_r - quo * r;
        old_r = temp;
        // find the d
        temp = t;
        t = old_t - quo * t;
        old_t = temp;
    }

    //Edge Case: bad choice of p and q
    if (old_r != 1) {
        cout << "INAPPROPRIATE CHOOSE OF P AND Q!" << endl;
        exit_prog();
    }
    d = old_t;
    return d;
}

int main(int argc, char* argv[]) {
    //Take two big primes p and q
    long long p, q;
    p = (long long)atoi(argv[1]);
    q = (long long)atoi(argv[2]);

    string first;
    //Execute orders
    while (cin >> first) {
        order_execute(first, p, q);
    }

    return 0;
}