#include <iostream>
#include <string>
using namespace std;
class CalendarDate {
private:
    int month, day, year;

public:
    CalendarDate(int m, int d, int y) {month = m; day = d; year = y;}
    
    bool operator<(const CalendarDate& other) const {
        if (year != other.year) return year < other.year;
        else if (month != other.month) return month < other.month;
        else return day < other.day;
    }

    string ToString() { return (to_string(month) + "/" + to_string(day) + "/" + to_string(year)); }

    friend ostream& operator<<(ostream& os, const CalendarDate& date)
    {
        string monthStrings[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        return os << monthStrings[date.month-1] << " " << to_string(date.day) << ", " << to_string(date.year);
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

    int hashCode() {
        return day + 31*month + 366*year;
    }
};