#include <algorithm>
#include <iostream>
#include <sstream>
#include "CalendarDate.h"
using namespace std;

/*
 * Victor Wong
 * Spring 2024, CS212, William Iverson
 * 04/15/2024
 * Program 3
 * Calendar Date Data Structure
 */

bool CompareDateItems(const CalendarDate& a, const CalendarDate& b) {
   return a < b;
}

int main() {
    // Create and sort an array of dates
    CalendarDate dates[] = {
        CalendarDate(12, 25, 2024),
        CalendarDate(11, 15, 1250),
        CalendarDate(12, 17, 1500),
        CalendarDate(12, 17, 1100),
        CalendarDate(10, 12, 2050),
        CalendarDate(10, 13, 2040)
    };
    int dateSize = sizeof(dates) / sizeof(dates[0]);
    cout << "Unsorted CalendarDate array:" << endl;
    for (int i = 0; i < dateSize; i++) {
        cout << dates[i].ToString() << endl; // let's have ToString return short date
    }

    sort(begin(dates), end(dates), CompareDateItems); // as in zyBook
    sort(&dates[0], &dates[dateSize]); // see cplusplus.com/reference/algorithm/sort/

    cout << "SORTED CalendarDate array:" << endl;
    for (int i = 0; i < dateSize; i++) {
        cout << dates[i].ToString() << endl;
    }

    // More operator overloads:
    CalendarDate test(4, 2, 2024);
    cout << "Working with April 2, 2024 right now" << endl;
    cout << test << endl; // let's stream the long date format
    cout << test++ << endl; // use for output, then increment year
    cout << ++test << endl; // increment year, then use for output
}