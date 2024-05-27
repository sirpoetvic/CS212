/*
Program to test the iterator, from zyDE 9.4.1

Original code from:
Roman Lysecky / Professor of Electrical and Computer Engineering / Univ. of Arizona
Frank Vahid / Professor of Computer Science and Engineering / Univ. of California

Modified by W.P. Iverson, for Bellevue College CS212 course
April 2024
*/


#include <iostream>
#include <string>
#include <set>
#include "Set.h"
using namespace std;

void ShowSet(const Set& set, const string& setName) {
    cout << setName << ": " << endl;
    for (int element : set) {
        cout << element << " ";
    }
    cout << endl;
}

int main() {
    int setAElements[] = { 53, -64, 19, 67, -24, 90 };

    Set setA, setB;
    for (int element : setAElements) {
        setA.Add(element);
    }
    ShowSet(setA, "Set A, initially");

    cout << "\nNow iterate through setA, adding sometimes:" << endl;
    for (int element : setA) {
        cout << element << " ";
        if (element > 0) setA.Add(-element);
    }
    cout << endl;

    ShowSet(setA, "\nSet A, later");

}