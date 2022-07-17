#include "company.cpp"
#include <iostream>

using namespace std;

int main() {
    CompanyTracker* cmp_test = new CompanyTracker(10);  // 0-9
    // General Testing
    // Merge-Testing
    cmp_test->merge(1, 2);
    cmp_test->merge(3, 4);
    cmp_test->merge(1, 3);

    // Since 1,2,3,4 in the same company after the merges, so it should not return IN the Same Company
    if (cmp_test->inSameCompany(1, 2))
        cerr << "1 and 2 in the same company" << endl;
    else
        cerr << "1 and 2 are NOT in the same company" << endl;
    if (cmp_test->inSameCompany(3, 4))
        cerr << "3 and 4 in the same company" << endl;
    else
        cerr << "3 and 4 are NOT in the same company" << endl;
    if (cmp_test->inSameCompany(1, 4))
        cerr << "1 and 4 in the same company" << endl;
    else
        cerr << "1 and 4 are NOT in the same company" << endl;

    // Split_Testing
    cmp_test->split(3);
    // After split 1,3 not in same company, so it ought to return NOT in Same Company
    if (cmp_test->inSameCompany(1, 3))
        cerr << "1 and 3 in the same company" << endl;
    else
        cerr << "1 and 3 are NOT in the same company" << endl;

    cmp_test->split(2);
    // After split 1,2 not in same company, so it ought to return NOT in Same Company
    if (cmp_test->inSameCompany(1, 2))
        cerr << "1 and 2 in the same company" << endl;
    else
        cerr << "1 and 2 are NOT in the same company" << endl;

    // Edge Case Testing
    // 1st Case, Merge, out of range <0 or >numCompanies
    cmp_test->merge(8, -1);
    // Since -1 is out of range, they can't merge, return false, NOT in the same company
    if (cmp_test->inSameCompany(8, -1))
        cerr << "8 and -1 are in the same company" << endl;
    else
        cerr << "8 and -1 are NOT in the same company" << endl;

    cmp_test->merge(8, 11);
    // Since 11 is out of range, they can't merge, return false, NOT in the same company
    if (cmp_test->inSameCompany(8, 11))
        cerr << "8 and 11 are in the same company" << endl;
    else
        cerr << "8 and 11 are NOT in the same company" << endl;

    // 2nd Case, Merge, 1 and 1 in same company, thus, they CAN'T MERGE
    cmp_test->merge(1, 1);
    if (cmp_test->inSameCompany(1, 1))
        cerr << "company[1] didn't merge" << endl;
    else
        cerr << "company[1] merge" << endl;

    cerr << "---------------------------------------- \n End of the Testing" << endl;

    delete cmp_test;
    return 0;
}
