#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

void per_helper(string in, vector<string>& out, string sin_output) {
    int in_size = in.size();
    if (in_size == 0) {
        // cout<< sin_output <<endl;
        out.push_back(sin_output);
        // cout<<"out_size: "<< out.size() << endl;
    } else {
        for (int i = 0; i < in_size; i++) {
            per_helper(in.substr(0, i) + in.substr(i + 1), out, sin_output + in.substr(i, 1));
        }
    }
}
void permutations(std::string in) {
    vector<string> all_string;
    per_helper(in, all_string, "");

    for (int i = 0; i < (int)all_string.size(); i++) {
        cout << all_string[i] << endl;
    }
}

// int main(int argc, char* argv[]) {
//     string str = "UAS";
//     vector<string> all_string;
//     permutations(str);
//     return 0;
// }