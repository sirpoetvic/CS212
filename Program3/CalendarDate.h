#include <iostream>
#include <string>
using namespace std;
class CalendarDate {
private:
    int month, day, year;
    string monthStrings[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

public:
    CalendarDate(int m, int d, int y) {month = m; day = d; year = y;}
    
    bool operator<(const CalendarDate& other) const {
        if (year != other.year) return year < other.year;
        else if (month != other.month) return month < other.month;
        else return day < other.day;
    }

    string ToString() { return to_string(month) + "/" + to_string(day) + "/" + to_string(year); }

    friend ostream& operator<<(ostream& os, const CalendarDate& date)
    {
    string month_string;
        switch(date.month) {
            case 1: month_string = "January"; break;
            case 2: month_string = "February"; break;
            case 3: month_string = "March"; break;
            case 4: month_string = "April"; break;
            case 5: month_string = "May"; break;
            case 6: month_string = "June"; break;
            case 7: month_string = "July"; break;
            case 8: month_string = "August"; break;
            case 9: month_string = "September"; break;
            case 10: month_string = "October"; break;
            case 11: month_string = "November"; break;
            case 12: month_string = "December"; break;
        }

        return os << month_string << " " << to_string(date.day) << ", " << to_string(date.year);
    }

    // prefix ++ operator
    const CalendarDate& operator++() {
        ++(this->year);
        return *this;
    }

    // postfix ++ operator
    const CalendarDate operator++(int) {
        CalendarDate temp(*this);
        ++(this->year);
        return temp;
    }
};