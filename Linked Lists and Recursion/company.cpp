#include "company.hpp"

#include <iostream>
using namespace std;

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];

    for (int i = 0; i < numCompanies; ++i) {
        companies[i] = new Company();
    }
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    // your implementation goes here
    for (int i = 0; i < numCompanies; i++) {
        // delete all the parent Companies

        while (find_the_largest_cmp(i)->merge1 != nullptr) {
            split(i);
        }

        delete companies[i];
    }
    delete[] companies;
}

/** Merges the largest companies containing students i and j.
 *
 * Generates a new Company object which will become the parent company of
 * the largest companies currently containing students i and j. If i and j
 * already belong to the same company (or are the same), merge doesn't do
 * anything. If either i or j are out of range, merge doesn't do anything.
 */

void CompanyTracker::merge(int i, int j) {
    // your implementation goes here

    // 1st Edge Case, if i or j is out of line then skip
    if (i < 0 || j < 0 || i >= numCompanies || j >= numCompanies) {
        return;
    }
    // 2nd Edge Case - if in the same company, skip
    if (find_the_largest_cmp(i) == find_the_largest_cmp(j)) {
        return;
    }

    // Create a New Company Object
    Company* created_cmp = new Company(find_the_largest_cmp(i), find_the_largest_cmp(j));
    find_the_largest_cmp(i)->parent = created_cmp;
    find_the_largest_cmp(j)->parent = created_cmp;
}

void CompanyTracker::split(int i) {
    // 1st Edge Case - if i is out of range
    if (i < 0 || i >= numCompanies) {
        return;
    }
    // 2nd Edge Case if i is only 1-person company
    if (find_the_largest_cmp(i)->merge1 == nullptr) {
        return;
    }

    // your implementation goes here
    Company* i_cmp = find_the_largest_cmp(i);
    i_cmp->merge1->parent = nullptr;
    i_cmp->merge2->parent = nullptr;
    // Delete the largetst_cmp_Merge1????
    delete i_cmp;
}

bool CompanyTracker::inSameCompany(int i, int j) {
    // your implementation goes here
    // 1st Edge Case
    if (i < 0 || j < 0 || i >= numCompanies || j >= numCompanies) {
        return false;
    }

    if (find_the_largest_cmp(i) == find_the_largest_cmp(j)) {
        return true;
    } else {
        return false;
    }
}

Company* CompanyTracker::find_the_largest_cmp(int i) {
    // iteration to find the largest cap
    Company* company_index_rep = companies[i];
    while (company_index_rep->parent) {
        company_index_rep = company_index_rep->parent;
    }
    return company_index_rep;
}
