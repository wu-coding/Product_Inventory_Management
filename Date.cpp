#include <iostream>
#include "Date.h"

using std::endl;

namespace AMA {

  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }
  Date::Date() : day(0), month(0), year(0), error(NO_ERROR), compare(0)
  {  }

  Date::Date(int passYear, int passMonth , int passDay)
  {
    bool yearValid = ( min_year < passYear && passYear < max_year);
    bool monthValid = ( 1 <= passMonth && passMonth <= 12);
    bool dayValid = ( 1 < passDay && passDay < mdays(passMonth, passYear));
    if (yearValid && monthValid && dayValid)  {
      day = passDay;
      month = passMonth;
      year = passYear;
      error = NO_ERROR;
      compare = passYear * 372 + passMonth * 13 + passDay;
    } 
    else {
      *this = Date();
    }
  }

  int Date:: errCode() const
  {
    return error;
  }

  void Date::errCode(int errorCode)
  {
    error = errorCode;
  }
  bool Date::isEmpty() const
  {
    return (year == 0 && month ==0 && day == 0) ? true : false;    
  }

  bool Date::operator==(const Date &rhs) const
  {
    if ( isEmpty() || rhs.isEmpty() || compare != rhs.compare)
    {
      return false;
    } else {
      return true;
    }
  }
  bool Date::operator!=(const Date &rhs) const
  {
    if ( isEmpty() || rhs.isEmpty() || compare == rhs.compare)
    {
      return false;
    } else {
      return true;
    }
  }
  bool Date::operator<(const Date &rhs) const
  {
    if ( isEmpty() || rhs.isEmpty() || compare > rhs.compare)
    {
      return false;
    } else {
      return true;
    }
  }
  bool Date::operator>(const Date &rhs) const
  {
    if ( isEmpty() || rhs.isEmpty() || compare < rhs.compare)
    {
      return false;
    } else {  
      return true;
    }
  }
  bool Date::operator<=(const Date &rhs) const
  {

    if ( isEmpty() || rhs.isEmpty() || (compare > rhs.compare && compare != rhs.compare))
    {
      return false;
    } else {  
      return true;
    }
  }

  bool Date::operator>=(const Date &rhs) const
  {
    if ( isEmpty() || rhs.isEmpty() || (compare < rhs.compare && compare != rhs.compare))
    {
      return false;
    } else {  
      return true;
    }
  }

  bool Date::bad()
  {
    return (error != 0)? true : false;
  }

  std::istream& Date::read(std::istream& istr)
  {
    int tempYear, tempMonth, tempDay;
    istr >> tempYear;
    istr.ignore();
    istr >> tempMonth;
    istr.ignore();
    istr >> tempDay;
    if (istr.fail())
    {
      errCode(CIN_FAILED);
    } else  {
      if (min_year > tempYear || tempYear > max_year)
      {
      errCode(YEAR_ERROR);
      }
      else if (tempMonth < 1 || tempMonth > 12)
      { 
        errCode(MON_ERROR);
      }
      else if (1 > tempDay || tempDay > mdays(tempMonth, tempYear))
      {
        errCode(DAY_ERROR);
      }
      else {
        year = tempYear;
        month = tempMonth;
        day = tempDay;
        compare = tempYear * 372 + tempMonth * 13 +tempDay;
      } 
    }  
    return istr;
  }

  std::ostream& Date::write(std::ostream& ostr) const
  {
    ostr.fill('0');
    ostr << year << "/";
    ostr.width(2);
    ostr << month << "/";
    ostr.width(2);
    ostr << day;
    return ostr;
  }

  std::istream& operator>>(std::istream& ist, Date& rhs)
  {
    return rhs.read(ist);
  }
  std::ostream& operator<<(std::ostream& ost, const Date& rhs)
  {
    return rhs.write(ost);
  }
}
