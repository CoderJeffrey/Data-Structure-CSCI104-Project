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
    // set the seed
    srand(time(0));
    double avg_probe_rate = 0.0;
    double total_probe_rate = 0.0;
    int trails = 1000;

    // we have 1000 trails so that the number would be more precise
    for (size_t i = 0; i < trails; i++) {
        int probe = 0;
        int temp_p = 0;
        // in every trial, create a new Hashtable of size 199
        Hashtable<int> h(true, 199);
        int h_size = 199;

        double probe_rate = 0.0;
        // since the size is 199 we insert 199 items
        for (int i = 0; i < h_size; i++) {
            // temp_p is the number of probes for every item
            temp_p = 0;
            string rand_s;

            // use different iteration number to create string of different length
            if (i % 6 == 0)
                rand_s = generate_random(11);
            if (i % 6 == 1)
                rand_s = generate_random(12);
            if (i % 6 == 2)
                rand_s = generate_random(13);
            if (i % 6 == 3)
                rand_s = generate_random(14);
            if (i % 6 == 4)
                rand_s = generate_random(15);
            if (i % 6 == 5)
                rand_s = generate_random(16);
            temp_p = h.add(rand_s, 13);

            // temp_p was added to the number of probe
            probe += temp_p;
        }

        // find the rate of probe by divide the total number of probes by the size of hashtable
        probe_rate = (double)probe / h_size;
        total_probe_rate += probe_rate;
    }

    // find the average probe rate for total number of trails
    avg_probe_rate = (double)total_probe_rate / trails;
    cout << "Average probe rate: " << avg_probe_rate << endl;
    return 0;
}