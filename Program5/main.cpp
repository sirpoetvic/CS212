#include <iostream>
#include <string>
#include <vector>
#include "ChainingHashTable.h"
#include "CalendarDate.h"
using namespace std;

int main() {
   CalendarDate dates[] = {
        CalendarDate(3,13,1976),
        CalendarDate(2,29,1276),
        CalendarDate(5,15,1570),
        CalendarDate(7,1,2684),
        CalendarDate(11,30,2450),
        CalendarDate(12,23,1230),
    };

   const int initialCapacity = 11;

   // Initialize the Chaining Hash Table
   ChainingHashTable<int,CalendarDate>* table = new ChainingHashTable<int,CalendarDate>(initialCapacity);

   // Hash and insert the keys and values
   for (int i = 0; i < size(dates); i++) {
    // insert a hashed CalendarDate (int), and CalendarDate as value
    table->Insert((dates[i].hashCode()), dates[i]);
   }

   // Print out the table
    table->PrintTable(cout);
}