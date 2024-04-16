// Code for CS212 first assignment, April 2024
// W.P. Iverson, instructor
// 
// function implementations

int LinearSearch(int* numbers, int numbersSize, int key, int& comparisons) {
    // Added parameter to hold total number of comparisons.
    comparisons = 0;

    for (int i = 0; i < numbersSize; i++) {
        comparisons++;
        if (numbers[i] == key) {
            return i;
        }
    }
    return -1; // not found
}


int BinarySearch(int* numbers, int numbersSize, int key, int& comparisons) {
    // Added parameter to hold total number of comparisons.
    comparisons = 0;

    // Variables to hold the low and high indices of the area being searched. 
    // Starts with entire range.
    int low = 0;
    int high = numbersSize - 1;

    // Loop until "low" passes "high"
    while (high >= low) {
        // Calculate the middle index
        int mid = (high + low) / 2;

        // Cut the range to either the left or right half,
        // unless numbers[mid] is the key
        comparisons++;
        if (numbers[mid] < key) {
            low = mid + 1;
        }
        else if (numbers[mid] > key) {
            high = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1; // not found
}
