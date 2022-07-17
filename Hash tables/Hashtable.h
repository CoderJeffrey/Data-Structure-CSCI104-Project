#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

template<class T>

class Hashtable {
private:
    void resize();
    T garbage;
    double load_fac = 0.0;
    bool debug;
    int size = 0;
    int stored_elements = 0;
    int r1, r2, r3, r4, r5;
    std::vector<T> values;
    std::vector<std::string> names;

    // helper function to turn any stirng less than or equal to 6 characters into a number
    long long parse_six(std::string temp) const;

public:
    Hashtable(bool debug = false, unsigned int size = 11);
    int add(std::string k, const T& val);
    const T& lookup(std::string k);
    void reportAll(std::ostream&) const;
    int hash(std::string k) const;
    ~Hashtable();
};

template<class T>
int Hashtable<T>::hash(std::string k) const {
    // Three Cases: 1. less than 6 letters 2. exactly 6 letters 3. more than 6 letters
    long long hash_value = 0;
    long long hash_sequence[5];
    long long number_leading_zero = 0;

    // based on the length of stirng we can know how many zeros would be put in the hash_sequence[5]
    number_leading_zero = 5 - ceil((double)k.length() / 6.0);

    // number_read_value represents how many numbers are with value rather than 0
    long long number_read_value = 5 - number_leading_zero;

    for (long long i = 0; i < number_leading_zero; i++) {
        // set the number_leading_zero places into 0
        hash_sequence[i] = 0;
    }

    long long last_pos = 4;
    // set values from the last position
    for (long long p = last_pos; p >= number_leading_zero; p--) {
        if (k.length() <= 6) {
            long long hash_temp = parse_six(k);
            hash_sequence[p] = hash_temp;
            break;
        }

        // every time remove the last 6 letters
        std::string temp = k.substr(k.length() - 6, 6);
        k.erase(k.end() - 6, k.end());
        long long hash_temp = parse_six(temp);
        hash_sequence[p] = hash_temp;
    }

    // calculate hash value
    for (int g = 0; g < 5; g++) {
        if (g == 0)
            hash_value += r1 * hash_sequence[g];
        else if (g == 1)
            hash_value += r2 * hash_sequence[g];
        else if (g == 2)
            hash_value += r3 * hash_sequence[g];
        else if (g == 3)
            hash_value += r4 * hash_sequence[g];
        else if (g == 4)
            hash_value += r5 * hash_sequence[g];
    }
    hash_value %= this->size;
    return hash_value;
}

template<class T>
long long Hashtable<T>::parse_six(std::string k) const {
    long long final_value = 0;
    long long leng = k.length();
    int number_zero = 6 - leng;
    // return the power of 27 for first integer
    // for example if string k has 6 letters, thus, number zero is 0, and a1 times 27 to the power of 5 = (5-0)
    // for example if string k has 3 letters, like abc, then a1 a2 a3 set to 0, and the a4 times 27 to the power of 2 =
    // (5-3)
    int first_power = 5 - number_zero;

    for (int i = 0; i < k.length(); i++) {
        char c = k[i];
        int value = (int)c - 96;
        final_value += (pow(27, first_power) * value);
        // next number times 1 less the power of 27 of this item
        first_power--;
    }

    return final_value;
}

template<class T>
Hashtable<T>::Hashtable(bool debug, unsigned int size) {
    this->size = size;
    this->debug = debug;

    // change the size for vector values and names
    values.resize(this->size);
    names.resize(this->size);

    // debug mode and without debug mode
    if (debug == true) {
        r1 = 983132572;
        r2 = 1468777056;
        r3 = 552714139;
        r4 = 984953261;
        r5 = 261934300;
    } else {
        r1 = rand() % size;
        r2 = rand() % size;
        r3 = rand() % size;
        r4 = rand() % size;
        r5 = rand() % size;
    }
}

template<class T>
Hashtable<T>::~Hashtable() {}

template<class T>
void Hashtable<T>::resize() {
    std::vector<int> size_list
            = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
    // increase size to the next larger value in the size list
    for (int i = 0; i < size_list.size(); i++) {
        if (size_list[i] > this->size) {
            this->size = size_list[i];
            break;
        }
    }

    // reset the stored elemtents and load fac to zero since now is an empty enlarged table
    stored_elements = 0;
    load_fac = 0.0;

    // rehash all the elements in the array
    // have two vectors to store elements in previous names and values vectors
    std::vector<std::string> temp_names(names.size());
    std::vector<T> temp_values(values.size());
    for (int k = 0; k < names.size(); k++) {
        if (!names[k].empty()) {
            temp_names[k] = names[k];
            temp_values[k] = values[k];
        }
    }

    // clear the values in vector values and names and resize the vectors
    values.clear();
    values.resize(this->size);
    names.clear();
    names.resize(this->size);

    // add all previous elemtents into the new hash table
    for (int k = 0; k < temp_names.size(); k++) {
        if (!temp_names[k].empty()) {
            add(temp_names[k], temp_values[k]);
        }
    }
}

template<class T>
int Hashtable<T>::add(std::string k, const T& val) {
    // if the load factor above 0.5 then we need to resize the hashtable, or else, high chance of collision
    if (load_fac > 0.5) {
        resize();
    }

    // set initial vallues
    int probes = 0;
    bool k_exist = false;
    int pos = hash(k);
    int temp_pos = pos;
    while (!names[temp_pos].empty()) {
        // if string k already exists then we do nothing
        if (names[temp_pos] == k) {
            k_exist = true;
            break;
        }
        // quadratic probing
        temp_pos = pos + pow((probes + 1), 2);

        // in case the temp pos get out of bound
        temp_pos = temp_pos % this->size;
        probes++;
    }

    // if k already in the hastable, quit the function
    if (k_exist) {

        // no probes required return 0
        return 0;
    }
    // if k is not in the hashtable, insert the values and names of k into corresponding vectors
    else {
        names[temp_pos] = k;
        values[temp_pos] = val;
        stored_elements++;
        load_fac = (double)stored_elements / this->size;
        return probes;
    }

    return 1;
}

template<class T>
// lookup whether k is in the hashtable
const T& Hashtable<T>::lookup(std::string k) {
    int pos = hash(k);
    int probes = 0;
    int temp_pos = pos;
    while (!names[temp_pos].empty()) {
        // if k is in the hasntable return the values attached to the string k
        if (names[temp_pos] == k) {
            return values[temp_pos];
            break;
        }
        temp_pos = pos + pow((probes + 1), 2);
        temp_pos = temp_pos % this->size;
        // if we find the position place to be empty then we add the string K and its value to the hash table
        probes++;
    }

    // After the loop the lookup doesn' find anything, then we return a garbage value of T
    return garbage;
}

template<class T>
// loop trough the hashtable and print out every (key,value) pair
void Hashtable<T>::reportAll(std::ostream& t) const {
    for (int i = 0; i < this->size; i++) {
        // output (key,value) pair if there is value
        if (!names[i].empty()) {
            t << names[i] << " " << values[i] << std::endl;
        }
    }
}
