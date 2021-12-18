#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {

  const int min_year = 2000;
  const int max_year = 2030;

  class Date {
    int day;
    int month;
    int year;
    int error;
    int compare;

    public:
    int mdays(int, int)const;
    Date();
    Date(int, int, int);
    void errCode(int errorCode);
    int errCode() const;
    bool isEmpty() const;
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;
    bool bad();

    std::istream& read(std::istream& istr);
    std::ostream& write(std::ostream& ostr) const;

  };

  std::istream& operator>>(std::istream& ist, Date& rhs);
  std::ostream& operator<<(std::ostream& ost, const Date& rhs);



}
#endif
