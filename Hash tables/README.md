How to compile my code: type `make`  
Then call the executables:  
1. the executable birthday is my answer for the Birthday Paradox question in Q2  
2. the executable probe is my answer for the Probe Rate question in Q2  

  
In this program, I mainly have the following functions  
* Hashtable(bool debug = false, unsigned int size = 11); -> initialize a Hash table  
* int add(std::string k, const T& val); -> add items to the hash table  
* const T& lookup(std::string k); -> lookup whether  a specific item/ element is in the hash table  
* void reportAll(std::ostream&) const; -> print out all values of the hash table  
* int hash(std::string k) const; -> a function returns a value within the size of the hash table based on the input of a string  
* ~Hashtable(); -> destructor  

Meanwhile, in order to achieve the hash function, I also have parse_six private helper function that helps to calculate the values of any string of six characters or less.  The calculation is based on the following formula: 27^5 a1 + 27^4 a2 + 27^3 a3 + 27^2 a4 + 27 a5 + a6  

My result for Data Collection:   

1.  Confirm the Birthday Paradox: with the initial size of 365, I found out that 50.53% of the time there would bn the first probe if I insert 23 things or less  
    *  I run the test 10000 times, so that the data would be more precise and I set the size of the Hash table to 365 so that it correponds to the day of a year

    * I use a random helper function to generate pseudorandom random strings with an input of string length n
    Then based on difference times the program iterates, I create random strings of different sizes
    
2. The average probe rate: after inserting n elements into the Hash table with size 199(prime) in 1000 trials (Large number of trails ensure the robustness of the data) And I found out that the average probes was around 0.623 * n, a bit smaller than the 2n/3. For this program, I also use  same method in Birthday Paradox to create random strings. 