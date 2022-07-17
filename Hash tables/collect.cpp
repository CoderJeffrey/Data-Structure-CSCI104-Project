#include "Hashtable.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// helper function to return a random string of length:  len
std::string generate_random(const int len) {
    string str_all = "abcdefghijklmnopqrstuvwxyz";
    std::string final_output = "";

    // every character is randomized
    for (int i = 0; i < len; ++i) {
        final_output += str_all[rand() % (str_all.length() - 1)];
    }

    return final_output;
}

int main(int argc, char* argv[]) {
    // set seed
    srand(time(NULL));

    int times_under23 = 0;
    double rate_under_23 = 0.0;
    int size_hash_table = 365;

    // set the number of trails
    int number_trails = 10000;

    // loop through every trail
    for (int i = 0; i < number_trails; i++) {
        // every trial we create a new Hashtable of size 365
        Hashtable<int> birthday(true, 365);
        int number_people = 1;
        while (number_people <= 366) {
            int first = 13;
            string rand_s;

            // use different iteration number to create string of different length
            if (number_people % 6 == 0)
                rand_s = generate_random(11);
            if (number_people % 6 == 1)
                rand_s = generate_random(12);
            if (number_people % 6 == 2)
                rand_s = generate_random(13);
            if (number_people % 6 == 3)
                rand_s = generate_random(14);
            if (number_people % 6 == 4)
                rand_s = generate_random(15);
            if (number_people % 6 == 5)
                rand_s = generate_random(16);

            int k = birthday.add(rand_s, first);

            // judge whether the first probe occurs
            if (k >= 1) {
                // if number of people is now under or equal to 23, we add one more times to the times_under23
                if (number_people <= 23) {
                    times_under23++;
                }
                break;
            }
            // if resize happens, then the program terminates
            if(number_people > (365/2))
            {
                break;
            }

            number_people++;
        }
    }
    // based on the times people have at least one probe occurs and total number of trials found out the rate under 23
    rate_under_23 = (double)times_under23 / number_trails;
    cout << "The possibility for at least two people among 23 people shared a same birthday is: " << rate_under_23
         << endl;
}