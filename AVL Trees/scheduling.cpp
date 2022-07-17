
#include "avlbst.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// helper function that insert every course into an appropriate time slot, such that no student are taking two exams at
// the same time
bool scheduler(
        vector<pair<int, vector<int>>>& current,
        AVLTree<int, int>& slot_match,
        int timeslots,
        AVLTree<int, int>::iterator& it);
// helper function that finds whether the course is eligible to put in the timeslot
bool course_available_slot(
        int course_id, int timeslot, vector<pair<int, vector<int>>>& current, AVLTree<int, int>& slot_match);
// helper function that fills the course with possible courses to collide
void fillup_collide(vector<pair<int, vector<int>>>& current, int student_num, istream& file);

// helper function that places every class into the correct time slot
bool scheduler(
        vector<pair<int, vector<int>>>& current,
        AVLTree<int, int>& slot_match,
        int timeslots,
        AVLTree<int, int>::iterator& it) {
    // Base Case 1: everything in our code is mapped to a timeslot other than 0, then it works
    if (it == slot_match.end()) {
        return true;
    }

    // iterate through all the timeslots to find out whether our class can fit in
    for (int s = 1; s <= timeslots; s++) {
        // true case: the course is eligible to place in the time slot
        if (course_available_slot(it->first, s, current, slot_match)) {
            // change the course's timeslot to s
            it->second = s;
            AVLTree<int, int>::iterator it_temp = it;
            if (scheduler(current, slot_match, timeslots, ++it)) {
                return true;
            }
            // reset back the iterator
            it = it_temp;
            // reset back the course corresponding timeslot
            it->second = 0;
        }
    }
    // if the course have no place to fit we return false
    return false;
}

// helper function that check whether a course is valid in a time slot
bool course_available_slot(
        int course_id, int timeslot, vector<pair<int, vector<int>>>& current, AVLTree<int, int>& slot_match) {
    bool available_or_not = true;
    int locate_course_pos = -1;
    for (size_t i = 0; i < current.size(); i++) {
        if (current.at(i).first == course_id) {
            locate_course_pos = i;
        }
    }

    if (locate_course_pos == -1) {
        // THe course is not in the exam RANGE
        return false;
    }

    AVLTree<int, int>::iterator temp_int;

    // for every node in collided course to see whether any of them are int the timeslot we want to insert
    for (long unsigned int p = 0; p < current.at(locate_course_pos).second.size(); p++) {
        // temp_int = slot_match.find(it->second.at(p));
        temp_int = slot_match.find(current.at(locate_course_pos).second.at(p));

        // if there a collision we simply return false
        if (temp_int->second == timeslot) {
            return false;
        }
    }

    return available_or_not;
}

// helper function that fills every course with other courses that may have a collision
// In another way of speaking, there are at least a student taking these courses same time, such that they can not be
// placed in the same time slot
void fillup_collide(vector<pair<int, vector<int>>>& current, int student_num, istream& file) {
    string line_temp = "";
    string name_temp = "";
    int course_temp = 0;

    int counting = 0;
    for (int i = 0; i < student_num; i++) {
        getline(file, line_temp);
        stringstream s(line_temp);
        // get the name of student
        s >> name_temp;
        vector<int> store_inline;

        while (s >> course_temp) {
            store_inline.push_back(course_temp);
            bool already_course = false;
            for (long unsigned int p = 0; p < current.size(); p++) {
                if (current.at(p).first == course_temp) {
                    already_course = true;
                    break;
                }
            }
            if (already_course == false) {
                // if there is no such a course, we create an empty vector to store any of its possible collided courses
                counting++;
                current.push_back(pair<int, vector<int>>(course_temp, vector<int>()));
            }
        }

        int position_first = -1;
        int position_second = -1;
        for (long unsigned int i = 0; i < store_inline.size() - 1; i++) {
            for (long unsigned int k = i + 1; k < store_inline.size(); k++) {
                position_first = -1;   // position where first course exists
                position_second = -1;  // position where second course exists

                for (long unsigned int p = 0; p < current.size(); p++) {
                    if (current.at(p).first == store_inline.at(i)) {
                        position_first = p;
                        break;
                    }
                }

                // Edge Case if the first course is not existed
                if (position_first == -1) {
                    // not in the course list we have, which is impossible, just to save sure
                    return;
                }

                // if we find that two course are taken by same student, and also the collided have not already been
                // added to the vector, the we push back the course
                if (find(current.at(position_first).second.begin(),
                         current.at(position_first).second.end(),
                         store_inline.at(k))
                    == current.at(position_first).second.end()) {
                    current.at(position_first).second.push_back(store_inline.at(k));
                }

                for (long unsigned int p = 0; p < current.size(); p++) {
                    if (current.at(p).first == store_inline.at(k)) {
                        position_second = p;
                        break;
                    }
                }

                // Edge Case if the first course is not existed
                if (position_second == -1) {
                    // not in the course list we have, which is impossible, just to save sure
                    return;
                }

                // if we find that two course are taken by same student, and also the collided have not already been
                // added to the vector, the we push back the course
                if (find(current.at(position_second).second.begin(),
                         current.at(position_second).second.end(),
                         store_inline.at(i))
                    == current.at(position_second).second.end()) {
                    current.at(position_second).second.push_back(store_inline.at(i));
                }
            }
        }

        // clear current student taken class temporary vector
        store_inline.clear();
    }
}

int main(int argc, char* argv[]) {
    string first_line = "";
    int exam_num = 0;
    int student_num = 0;
    int timeslots = 0;
    // get the input file
    ifstream file(argv[1]);

    getline(file, first_line);
    stringstream s(first_line);
    s >> exam_num;
    s >> student_num;
    s >> timeslots;

    // a new vector that maps the course code with other codes that may collide
    vector<pair<int, vector<int>>> collision_course;
    fillup_collide(collision_course, student_num, file);
    AVLTree<int, int> time_slot_match;

    // put every course into the AVLTree<int,int>into time_slot_match with the default time slot 0, meaning they have
    // been assigned to a specific time slot

    for (long unsigned int g = 0; g < collision_course.size(); g++) {
        time_slot_match.insert(pair<int, int>(collision_course.at(g).first, 0));
    }

    AVLTree<int, int>::iterator itr = time_slot_match.begin();
    bool finaloutput = scheduler(collision_course, time_slot_match, timeslots, itr);

    // if we find no available solution, we print out "No valid solution"
    if (finaloutput == false) {
        cout << "No valid solution." << endl;
        return 0;
    }

    // print every course with its time slot
    for (auto itr = time_slot_match.begin(); itr != time_slot_match.end(); ++itr) {
        cout << itr->first << " " << itr->second << endl;
    }

    return 1;
}
