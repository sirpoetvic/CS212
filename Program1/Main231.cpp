// Code for CS212 first assignment, April 2024
// W.P. Iverson, instructor
// 
#include "Example231.h"

// Main program to test both search functions
int main() {
    int numbers[] = { 2, 4, 7, 10, 11, 32, 45, 87 };
    int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
    cout << "NUMBERS: [" << numbers[0];
    for (int i = 1; i < numbersSize; i++) {
        cout << ", " << numbers[i];
    }
    cout << "]" << endl;

    // Prompt for an integer to search for
    cout << "Enter an integer value: ";
    int key = 0;
    cin >> key;
    cout << endl;

    int comparisons = 0;
    int keyIndex = LinearSearch(numbers, numbersSize, key, comparisons);
    if (keyIndex == -1) {
        cout << "Linear search: " << key << " was not found with ";
        cout << comparisons << " comparisons." << endl;
    }
    else {
        cout << "Linear search: Found " << key << " at index " << keyIndex;
        cout << " with " << comparisons << " comparisons." << endl;
    }

    keyIndex = BinarySearch(numbers, numbersSize, key, comparisons);
    if (keyIndex == -1) {
        cout << "Binary search: " << key << " was not found with ";
        cout << comparisons << " comparisons." << endl;
    }
    else {
        cout << "Binary search: Found " << key << " at index " << keyIndex;
        cout << " with " << comparisons << " comparisons." << endl;
    }
}