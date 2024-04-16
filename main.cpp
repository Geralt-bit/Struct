#include <bits/stdc++.h>
using namespace std;

struct Date {
    int day;
    int month;
    int year;

    bool isValidDate() const {
        if (year < 0 or month < 1 or month > 12 or day < 1 or day > 31)
            return false;
        if ((month == 4 or month == 6 or month == 9 or month == 11) and day > 30)
            return false;
        if (month == 2) {
            if ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)) {
                if (day > 29)
                    return false;
            }
            else {
                if (day > 28)
                    return false;
            }
        }
        return true;
    }

    void newDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    string getDayOfWeek() const {
        static string days[7] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

        int d = day;
        int m = month;
        int LasTwo = year % 100;
        int FirsTwo = year / 100;

        int h = (d + 13 * (m + 1) / 5 + LasTwo + LasTwo / 4 + FirsTwo / 4 + 5 * FirsTwo) % 7;

        return days[h];
    }

    int calculateDifference(const Date& date) const {
        long int date1 = year * 365 + day;
        for (int i = 0; i < month - 1; i++) {
            if (i == 1) {
                if ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)) {
                    date1 += 29;
                }
                else {
                    date1 += 28;
                }
            }
            else if (i == 3 or i == 5 or i == 8 or i == 10) {
                date1 += 30;
            }
            else {
                date1 += 31;
            }
        }

        long int date2 = date.year * 365 + date.day;
        for (int i = 0; i < date.month - 1; ++i) {
            if (i == 1) {
                if ((date.year % 4 == 0 and date.year % 100 != 0) or (date.year % 400 == 0)) {
                    date2 += 29;
                }
                else {
                    date2 += 28;
                }
            }
            else if (i == 3 or i == 5 or i == 8 or i == 10) {
                date2 += 30;
            }
            else {
                date2 += 31;
            }
        }

        return abs(date1 - date2);
    }

    void printDate() const {
        static string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
        cout << months[month - 1] << " " << day << ", " << year << endl;
    }

    bool operator<(const Date& date) const {
        if (year != date.year)
            return year < date.year;
        if (month != date.month)
            return month < date.month;
        return day < date.day;
    }
};

int main() {
    vector<Date> dates;
    char choice;
    do {
        int day, month, year;
        cout << "Enter day, month, and year (separated by spaces): ";
        cin >> day >> month >> year;

        Date newDate;
        newDate.newDate(day, month, year);
        if (newDate.isValidDate()) {
            dates.push_back(newDate);
            cout << "Date added successfully." << endl;
        }
        else {
            cout << "Invalid date. Please enter a valid date." << endl;
        }

        cout << "Do you want to enter another date? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    if (dates.size() >= 2) {
        // Sorting the dates
        sort(dates.begin(), dates.end());

        // Displaying the sorted dates
        cout << "\nSorted Dates:" << endl;
        for (const auto& date : dates) {
            date.printDate();
        }

        // Calculate difference between the first two dates
        int difference = dates[0].calculateDifference(dates[1]);
        cout << "Difference between the first two dates: " << difference << " days" << endl;
    }
    else {
        cout << "Please enter at least two valid dates to calculate the difference." << endl;
    }

    return 0;
}
