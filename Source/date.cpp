#include"../header/date.h"
namespace date {
    clsDate::clsDate(int day , int month , int year){
            this->handleFormat(day,month,year,date::clsDate::format(day,month,year));

        }
    clsDate::clsDate(){
        time_t now = time(nullptr);
        struct tm *local_time = localtime(&now);
        this->date1._day = local_time->tm_mday;
        this->date1._month = local_time->tm_mon +1 ;
        this->date1._year = local_time->tm_year +1900;
        }
    clsDate::clsDate(int dayOfYear , int year){
        tm date = {};
        date.tm_year = year - 1900;
        date.tm_mon = 0;  // January
        date.tm_mday = dayOfYear;

        mktime(&date);

        this->date1._day = date.tm_mday;
        this->date1._month = date.tm_mon + 1;
        this->date1._year = date.tm_year + 1900;
    }
    clsDate::clsDate(const string& sDate) {
        vector<string> dt;
        string word;

        for (char c : sDate) {
            if (isdigit(c)) {
                word += c;
            } else if ((c == '/' || c == '-') && !word.empty()) {
                dt.push_back(word);
                word.clear();
            }

        }

        if (!word.empty()) {
            dt.push_back(word);
        }

        if (dt.size() != 3) {
            throw invalid_argument("Invalid date format. Expected: DD/MM/YYYY or DD-MM-YYYY");
        }

        try {
            int day = stoi(dt[0]);
            int month = stoi(dt[1]);
            int year = stoi(dt[2]);

            if (day <= 0 || month <= 0 || year <= 0) {
                throw invalid_argument("Date values must be positive");
            }

            this->handleFormat(day, month, year, date::clsDate::format(day, month, year));
        } catch (const invalid_argument& e) {
            throw;
        } catch (...) {
            throw invalid_argument("Failed to parse date values");
        }
    }

    [[maybe_unused]] void clsDate::setDay(int day){
        this->date1._day = day ;
    }
    [[maybe_unused]] void clsDate::setMonth(int month){
        this->date1._month = month ;
    }
    [[maybe_unused]] void clsDate::setYear (int year){
        this->date1._year = year ;
    }

    [[maybe_unused]] void clsDate::setStDate(int day , int month , int year){
        this->handleFormat(day,month,year,date::clsDate::format(day,month,year));
    }

    [[maybe_unused]] int clsDate::getDay() const{
        return this->date1._day;
    }

    [[maybe_unused]] int clsDate::getMonth() const{
        return this->date1._month;
    }

    [[maybe_unused]] int clsDate::getYear() const{
        return this->date1._year ;
    }
    [[maybe_unused]] void clsDate::printDate() const{
            cout << "the Date with Format DMY \n is :";
            cout << this->date1._day << "/" << this->date1._month << "/" << this->date1._year << endl ;
        }

    [[maybe_unused]] void clsDate::Print(int day , int month , int year){
        clsDate date(day,month, year);
        date.printDate();
    }
    [[maybe_unused]] void clsDate::PrintMonthCalendar(){
        cout<<"    ===== "<<date::clsDate::getShortMonthName(this->date1._month)<<" " << this->date1._year <<" =====" <<endl ;
        cout << "----------------------------"<< endl ;
        string getNameDayInWeek;
        int endDayInMonth = date::clsDate::getDaysInMonth(this->date1._month ,this->date1._year) ;
        string line = this->calculateSpace();
        for (int i = 0 ; i<=6 ; i++){
            getNameDayInWeek +=  date::clsDate::getShortDayName(i)+" " ;
        }
        cout << getNameDayInWeek<<endl ;
        for (int i = 1 ; i <= endDayInMonth ; i++ ){
            if (i < 10){
               line +=  to_string(i) + "   " ;
            }
            else {
                line +=  to_string(i) + "  " ;
              }
            if (line.length() >= getNameDayInWeek.length()){
                cout << line ;
                cout << endl ;
                line = "" ;
            }
        }
        if (!line.empty()){
            cout << line ;

        }
        cout << endl ;

    }

    [[maybe_unused]]  void clsDate::PrintMonthCalendar(int month , int year){
        clsDate date (1 , month ,year);
        date.PrintMonthCalendar();
    }

    [[maybe_unused]]  void clsDate::PrintYearCalendar() const{
        clsDate date ( 15 ,1 ,this->date1._year);
        for (int i = 1 ; i <= 12 ; i++){
            date.setMonth(i);
            date.PrintMonthCalendar();
        }
        
    }

    [[maybe_unused]]  void clsDate::PrintYearCalendar(int year){
        clsDate date ( 15 ,1 ,year);
            for (int i = 1 ; i <= 12 ; i++){
            date.setMonth(i);
            date.PrintMonthCalendar();
        }
    }

    [[maybe_unused]] string clsDate::DateToString() const{
        string sDate = to_string(date1._day) + "/" + to_string(date1._month) + "/" +to_string(date1._year);
        return sDate ;
    }

    [[maybe_unused]] string clsDate::DateToString(const clsDate& date){
        string sDate = to_string(date.date1._day) + "/" + to_string(date.date1._month) + "/" +to_string(date.date1._year);
        return sDate ;
    }
    [[maybe_unused]] string clsDate::DayShortName() const{
        int index = getWeekdayIndex(this->date1._day,this->date1._month,this->date1._year);
        string dayName = date::clsDate::getShortDayName(index);
        return dayName ;
    }

    [[maybe_unused]] string clsDate::DayShortName(int index){
        const string arrShortDays[7] = {
                "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
            };
        string dayName = arrShortDays[index];
        return dayName ;
    }

    [[maybe_unused]] string clsDate::DayShortName(int day , int month , int year){
        clsDate date (day ,month ,year);
        string dayName =  date.DayShortName();
        return dayName ;
    }
    [[maybe_unused]] string clsDate::MonthShortName() const{
        string monthShortName = date::clsDate::getShortMonthName(this->date1._month);
        return monthShortName ;
    }

    [[maybe_unused]] string clsDate::MonthShortName(int month){
        clsDate date;
        date.setMonth(month);
        string nameShortMonth = date.MonthShortName();
        return nameShortMonth;
    }

    [[maybe_unused]] clsDate clsDate::GetSystemDate(){
        clsDate date ;
        return date ;
    }
    [[maybe_unused]] bool clsDate::isLeapYear() const{
        return date::clsDate::_isLeapYear(this->date1._year);
    }
    [[maybe_unused]] bool clsDate::isLeapYear(int year){
        clsDate date ;
        date.setYear(year);
        return date.isLeapYear();
    }
    [[maybe_unused]] bool clsDate::IsValid() const{
        int endDayInMonth = date::clsDate::getDaysInMonth(this->date1._month , this->date1._year) ;
        int day = this->date1._day ;
        if  (this->date1._month  < 1 || this->date1._month  > 12){
            return false ;
        }
        if (day < 1 ||endDayInMonth < day ){
            return false ;
        }
        return true ;
    }

    [[maybe_unused]]  bool clsDate::IsValidDate(const clsDate& date){
        return date.IsValid();
    }
    [[maybe_unused]] int clsDate::NumberOfDaysInAYear() const{
        return isLeapYear(this->date1._year) ? 366 : 365;
    }
    [[maybe_unused]] int clsDate::NumberOfDaysInAYear(int year){
        clsDate date (1,1,year);
        return date.NumberOfDaysInAYear();
    }
    [[maybe_unused]] int clsDate::NumberOfHoursInAYear() const{
        return this->NumberOfDaysInAYear()*24;
    }
    [[maybe_unused]] int clsDate::NumberOfHoursInAYear(int year){
        return clsDate::NumberOfDaysInAYear(year)*24;
    }
    [[maybe_unused]] int clsDate::NumberOfMinutesInAYear() const{
        return this->NumberOfHoursInAYear()*60;
    }
    [[maybe_unused]] int clsDate::NumberOfMinutesInAYear(int year){
        return clsDate::NumberOfHoursInAYear(year)*60;
    }

    [[maybe_unused]]  int clsDate::NumberOfSecondsInAYear() const{
        return this->NumberOfMinutesInAYear()*60;
    }

    [[maybe_unused]]  int clsDate::NumberOfSecondsInAYear(int year){
        return clsDate::NumberOfMinutesInAYear(year)*60;
    }
    [[maybe_unused]] int clsDate::NumberOfDaysInAMonth() const{
        return date::clsDate::getDaysInMonth(this->date1._month , this->date1._year);
    }

    [[maybe_unused]] int clsDate::NumberOfDaysInAMonth(int month , int year){
        clsDate date (1,month,year);
        return date.NumberOfDaysInAMonth();
    }
    [[maybe_unused]] int clsDate::NumberOfHoursInAMonth() const{
        return this->NumberOfDaysInAMonth()*24;
    }

    [[maybe_unused]]  int clsDate::NumberOfHoursInAMonth(int month , int year){
        clsDate date (1,month,year);
        return date.NumberOfHoursInAMonth();
    }
    [[maybe_unused]] int clsDate::NumberOfMinutesInAMonth() const{
        return this->NumberOfHoursInAMonth() * 60 ;
    }

    [[maybe_unused]]  int clsDate::NumberOfMinutesInAMonth(int month , int year){
        clsDate date (1,month,year);
        return date.NumberOfMinutesInAMonth();
    }
    [[maybe_unused]] int clsDate::NumberOfSecondsInAMonth() const{
        return this->NumberOfMinutesInAMonth()*60;
    }

    [[maybe_unused]]  int clsDate::NumberOfSecondsInAMonth(int month , int year){
        clsDate date (1,month,year);
        return date.NumberOfSecondsInAMonth();
    }
    [[maybe_unused]] int clsDate::DayOfWeekOrder() const{
        return date::clsDate::getWeekdayIndex(this->date1._day,this->date1._month,this->date1._year);
    }

    [[maybe_unused]] int clsDate::DayOfWeekOrder(int day, int month , int year){
        clsDate date(day,month , year);
        return date.DayOfWeekOrder();
    }
    [[maybe_unused]] int clsDate::DaysFromTheBeginingOfTheYear() const{
        tm date = {};
        date.tm_year = this->date1._year -1900 ;
        date.tm_mon  = this->date1._month-1;
        date.tm_mday = this->date1._day ;
        mktime(&date);
        return date.tm_yday + 1 ;
    }

    [[maybe_unused]]  int clsDate::DaysFromTheBeginingOfTheYear(int day , int month , int year){
        clsDate date (day , month , year);
        return date.DaysFromTheBeginingOfTheYear();
    }

    [[maybe_unused]]  clsDate clsDate::GetDateFromDayOrderInYear(int DateOrderInYear,int year){
        clsDate date (DateOrderInYear , year);
        return date ;
    }
    [[maybe_unused]] void clsDate::AddOneDay(){
        tm date = {};
        date.tm_year = this->date1._year -1900 ;
        date.tm_mon = this ->date1._month - 1;
        date.tm_mday = this->date1._day +1 ;
        mktime(&date);
        this->date1._year = date.tm_year +1900;
        this->date1._month = date.tm_mon + 1;
        this->date1._day = date.tm_mday ;

    }

    [[maybe_unused]] [[maybe_unused]] clsDate clsDate::AddOneDay(clsDate date ){
        date.AddOneDay();
        return date ;
    }
    [[maybe_unused]] void clsDate::AddDays(int days){
        for (int i = 0 ; i <days ; i++){
            this->AddOneDay();
        }
    }

    [[maybe_unused]]  void clsDate::IncreaseDateByXDays(int Days) {
        this->AddDays(Days);
    }

    [[maybe_unused]]  void clsDate::IncreaseDateByXDays(int Days, date::clsDate &Date) {
        Date.AddDays(Days);
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneWeek(){
        this->AddDays(7);
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneWeek(clsDate& Date){
        Date.AddDays(7);
    }

    [[maybe_unused]]  void clsDate::IncreaseDateByXWeeks(short Weeks){
        this->AddDays(Weeks * 7);

    }

    [[maybe_unused]] void clsDate::IncreaseDateByXWeeks(short Weeks, clsDate& Date){
        Date.AddDays(Weeks * 7);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneMonth(){
        std::chrono::year_month_day ymd = std::chrono::year{this->date1._year}/this->date1._month/this->date1._day;
        ymd = ymd + std::chrono::months{1};
        if (!ymd.ok()) {
            ymd = std::chrono::year_month_day_last{
                    ymd.year(), std::chrono::month_day_last{ymd.month()}
            };
        }
        this->date1._year = (int)static_cast<int>(ymd.year());
        this->date1._month = int(static_cast<unsigned>(ymd.month()));
        this->date1._day = (int)static_cast<unsigned>(ymd.day());
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneMonth(clsDate& Date){
        tm date = {};
        date.tm_year = Date.date1._year - 1900 ;
        date.tm_mon = Date.date1._month - 1 ;
        date.tm_mday= Date.date1._day ;
        date.tm_mon ++;
        mktime(&date);
        Date.date1._year = date.tm_year+1900;
        Date.date1._month = date.tm_mon+1;
        Date.date1._day = date.tm_mday;
    }

    [[maybe_unused]] void clsDate::IncreaseDateByXMonths(short Months){
        for (int i = 0 ; i <Months ; i++){
            this->IncreaseDateByOneMonth();
        }
    }

    [[maybe_unused]] void clsDate::IncreaseDateByXMonths(short Months, clsDate& Date){
        for (int i = 0 ; i <Months ; i++){
            Date.IncreaseDateByOneMonth();
        }
    }

    [[maybe_unused]] string clsDate::calculateSpace() const {
        int index = getWeekdayIndex (1 , date1._month , date1._year) ;
        string space ;
        if (index != 0){
            for (int i = 0 ; i < index ; i++){
                space+="    ";
            }
        }
        return space ;
    }
    [[maybe_unused]] std::chrono::sys_days clsDate::to_sys_days() const {
        std::chrono::year_month_day ymd = std::chrono::year{date1._year} /
                std::chrono::month{static_cast<unsigned>(date1._month)} /
                std::chrono::day{static_cast<unsigned>(date1._day)};
        return std::chrono::sys_days(ymd);
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneYear(){
        for (int i = 0 ; i < 12 ; i++){
            this->IncreaseDateByOneMonth();
        }
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneYear(clsDate& Date){
        Date.IncreaseDateByOneYear();
    }
    [[maybe_unused]] void clsDate::IncreaseDateByXYears(int Years){
        for (int i = 0 ; i < Years ; i ++){
            this->IncreaseDateByOneYear();
        }
    }

    [[maybe_unused]] void clsDate::IncreaseDateByXYears(int Years, clsDate& Date){
        Date.IncreaseDateByXYears(Years);
    }

    [[maybe_unused]] void clsDate::IncreaseDateByOneDecade(){
        this->IncreaseDateByXYears(10);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneDecade(clsDate& Date){
        Date.IncreaseDateByXYears(10);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByXDecades(int Decade){
        this->IncreaseDateByXYears(10*Decade);

    }
    [[maybe_unused]] void clsDate::IncreaseDateByXDecades(int Decade, clsDate& Date){
        Date.IncreaseDateByXYears(10 * Decade);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneCentury(){
        this->IncreaseDateByXDecades(10);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneCentury(clsDate& Date){
        Date.IncreaseDateByXDecades(10);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneMillennium(){
        this->IncreaseDateByXDecades(100);
    }
    [[maybe_unused]] void clsDate::IncreaseDateByOneMillennium(clsDate& Date){
        Date.IncreaseDateByXDecades(100);
    }

    [[maybe_unused]] void clsDate::DecreaseDateByOneDay(int day) {
        std::chrono::year_month_day ymd = chrono::year{this->date1._year}/chrono::month{(unsigned) this->date1._month}/chrono::day{(unsigned)this->date1._day};
        auto sd = std::chrono::sys_days (ymd);
        sd -= std::chrono::days{day};
        ymd = std::chrono::year_month_day(sd);
        this->date1._year = (int)static_cast<int>(ymd.year());
        this->date1._month = int(static_cast<unsigned>(ymd.month()));
        this->date1._day = (int)static_cast<unsigned>(ymd.day());
    }
    [[maybe_unused]] clsDate clsDate::DecreaseDateByOneDay(clsDate Date){
        Date.DecreaseDateByOneDay();
        return Date ;
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXDays(int Days){
        this->DecreaseDateByOneDay(Days);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXDays(int Days, clsDate& Date){
        Date.DecreaseDateByOneDay(Days);
    }

    [[maybe_unused]] void clsDate::DecreaseDateByOneWeek(){
        this->DecreaseDateByOneDay(7);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneWeek(clsDate& Date){
        Date.DecreaseDateByOneDay(7);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXWeeks(int Weeks){
        DecreaseDateByOneDay(7* Weeks);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXWeeks(int Weeks, clsDate& Date){
        Date.DecreaseDateByOneDay(7 * Weeks);
    }

    [[maybe_unused]] void clsDate::DecreaseDateByOneMonth(int month){
        std::chrono::year_month_day ymd = std::chrono::year{this->date1._year}/this->date1._month/this->date1._day;
        ymd = ymd - std::chrono::months{month};
        if (!ymd.ok()) {
            ymd = std::chrono::year_month_day_last{
                    ymd.year(), std::chrono::month_day_last{ymd.month()}
            };
        }
        this->date1._year = (int)static_cast<int>(ymd.year());
        this->date1._month = int(static_cast<unsigned>(ymd.month()));
        this->date1._day = (int)static_cast<unsigned>(ymd.day());
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneMonth(clsDate& Date){
        Date.DecreaseDateByOneMonth();
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXMonths(int Months){
        this->DecreaseDateByOneMonth(Months);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXMonths(int Months, clsDate& Date){
        Date.DecreaseDateByOneMonth(Months);
    }

    [[maybe_unused]] void clsDate::DecreaseDateByOneYear(){
        this->DecreaseDateByOneMonth(12);

    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneYear(clsDate& Date){
        Date.DecreaseDateByOneMonth(12);

    }
    [[maybe_unused]] void clsDate::DecreaseDateByXYears(int Years){
        this->DecreaseDateByOneMonth(12*Years);

    }
    [[maybe_unused]] void clsDate::DecreaseDateByXYears(int Years, clsDate& Date){
        Date.DecreaseDateByOneMonth(12*Years);

    }

    [[maybe_unused]] void clsDate::DecreaseDateByOneDecade(){
        this->DecreaseDateByXYears(10);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneDecade(clsDate& Date){
        Date.DecreaseDateByXYears(10);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByXDecades(int Decades){
        this->DecreaseDateByXYears(10 *Decades);

    }
    [[maybe_unused]] void clsDate::DecreaseDateByXDecades(int Decades, clsDate& Date){
        Date.DecreaseDateByXYears(10 *Decades);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneCentury(){
        this->DecreaseDateByXDecades(10);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneCentury(clsDate& Date){
        Date.DecreaseDateByXDecades(10);
    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneMillennium(){
        this->DecreaseDateByXDecades(100);

    }
    [[maybe_unused]] void clsDate::DecreaseDateByOneMillennium(clsDate& Date){
        Date.DecreaseDateByXDecades(100);

    }

    [[maybe_unused]] bool clsDate::IsDate1BeforeDate2(const clsDate &Date1, const clsDate &Date2){
        return Date1.IsDateBeforeDate2(Date2);
    }
    [[maybe_unused]] bool clsDate::IsDateBeforeDate2(const clsDate &Date2)const{
        return to_sys_days() < Date2.to_sys_days();
    }
    [[maybe_unused]] bool clsDate::IsDate1EqualDate2(const clsDate &Date1,const clsDate &Date2){
        return Date1.IsDateEqualDate2(Date2);
    }
    [[maybe_unused]] bool clsDate::IsDateEqualDate2(const clsDate &Date2)const{
        return to_sys_days() == Date2.to_sys_days();
    }
    [[maybe_unused]] bool clsDate::IsDate1AfterDate2(const clsDate &Date1,const clsDate &Date2){
        return Date1.IsDateAfterDate2(Date2);
    }
    [[maybe_unused]] bool clsDate::IsDateAfterDate2(const clsDate &Date2)const{
        return to_sys_days() > Date2.to_sys_days();
    }
    [[maybe_unused]] enDateCompare clsDate::CompareDates(const clsDate &Date1,const clsDate &Date2){
        return Date1.CompareDates(Date2);
    }
    [[maybe_unused]] enDateCompare clsDate::CompareDates(const clsDate &Date2)const{
        if (this->IsDateBeforeDate2(Date2)) return Before ;
        if (this->IsDateAfterDate2(Date2)) return After ;
        return Equal ;
    }

    // Difference Calculation Functions
    [[maybe_unused]] int clsDate::GetDifferenceInDays(clsDate &Date1,clsDate &Date2,bool IncludeEndDay){
        return Date1.GetDifferenceInDays(Date2,IncludeEndDay);
    }
    [[maybe_unused]] int clsDate::GetDifferenceInDays(clsDate &Date2,bool IncludeEndDay ) const{
        std::chrono::days diff = this->to_sys_days() - Date2.to_sys_days() ;
        if (IncludeEndDay){
            diff += std::chrono::days{1};
        }
        return (int)diff.count() ;
    }
    [[maybe_unused]] int clsDate::CalculateMyAgeInDays(clsDate &DateOfBirth){
        std::chrono::days day = date::clsDate::GetSystemDate().to_sys_days() -DateOfBirth.to_sys_days()  ;
        return (int)day.count();
    }
    [[maybe_unused]] void clsDate::SwapDates(clsDate& Date1, clsDate& Date2){
        std::swap(Date1,Date2);
    }

    // Date Properties Check Functions
    [[maybe_unused]] bool clsDate::IsLastDayInMonth()const{
        return this->date1._day == date::clsDate::getDaysInMonth(this->date1._month,this->date1._year) ;
    }
    [[maybe_unused]] bool clsDate::IsLastDayInMonth(const clsDate &Date){
        return Date.IsLastDayInMonth() ;
    }
    [[maybe_unused]] bool clsDate::IsLastMonthInYear(const int &Month){
        return Month == 12 ;
    }
    [[maybe_unused]] bool clsDate::IsEndOfWeek()const{
        return date::clsDate::getWeekdayIndex(this->date1._day ,this->date1._month , this->date1._year) == 5 ;
    }
    [[maybe_unused]] bool clsDate::IsEndOfWeek(const clsDate &Date){
        return Date.IsEndOfWeek();
    }
    [[maybe_unused]] bool clsDate::IsWeekEnd()const{
        int dayIndex = date::clsDate::getWeekdayIndex(this->date1._day ,this->date1._month , this->date1._year);
        return dayIndex == 5 || dayIndex == 6 ;
    }
    [[maybe_unused]] bool clsDate::IsWeekEnd(const clsDate &Date){
        return Date.IsWeekEnd();
    }
    [[maybe_unused]] bool clsDate::IsBusinessDay()const{
        return !this->IsWeekEnd();
    }
    [[maybe_unused]] bool clsDate::IsBusinessDay(const clsDate &Date){
        return Date.IsBusinessDay();
    }

    // Remaining Days Calculation Functions
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfWeek() const{
        tm date = {};
        date.tm_year = this->date1._year -1900 ;
        date.tm_mon = this->date1._month -1 ;
        date.tm_mday = this->date1._day ;
        mktime(&date);
        if (date.tm_wday == 5) return 0;
        if (date.tm_wday == 6) return 6 ;
        return 5 - date.tm_wday ;
    }
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfWeek(const clsDate &Date){
        return Date.DaysUntilTheEndOfWeek();
    }
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfMonth() const{
        tm date = {};
        date.tm_year = this->date1._year -1900 ;
        date.tm_mon = this->date1._month -1 ;
        date.tm_mday = this->date1._day ;
        mktime(&date);
        return date::clsDate::getDaysInMonth(this->date1._month,this->date1._year) - date.tm_mday ;
    }
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfMonth(const clsDate &Date1){
        return Date1.DaysUntilTheEndOfMonth();
    }
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfYear() const{
        tm date = {};
        date.tm_year = this->date1._year -1900 ;
        date.tm_mon = this->date1._month -1 ;
        date.tm_mday = this->date1._day ;
        mktime(&date);
        return this->NumberOfDaysInAYear() - date.tm_yday ;
    }
    [[maybe_unused]] int clsDate::DaysUntilTheEndOfYear(const clsDate &Date1){
        return Date1.DaysUntilTheEndOfYear();
    }
    [[maybe_unused]] const clsDate *clsDate::maxDate (const clsDate &Date1, const clsDate &Date2){
        return Date1.maxDate(Date2);
    }
    [[maybe_unused]] const clsDate *clsDate::minDate (const clsDate &Date1, const clsDate &Date2){
        return Date1.minDate(Date2);
    }
    [[maybe_unused]] const clsDate* clsDate::maxDate (const clsDate &Date2)const{
        if (this->CompareDates(Date2) == Before) return &Date2 ;
        if (this->CompareDates(Date2) == Equal) return &Date2 ;
        return this;
    }
    [[maybe_unused]] const clsDate *clsDate::minDate ( const clsDate &Date2)const {
        if (this->CompareDates(Date2) == Before) return this ;
        if (this->CompareDates(Date2) == Equal) return this ;
        return &Date2;
    }

    // Business and Holiday Functions
    [[maybe_unused]] int clsDate::CalculateBusinessDays(const clsDate& DateFrom,const clsDate& DateTo){
        int counter = 0;
        if (DateFrom.CompareDates(DateTo) == Equal) {
            return DateFrom.IsBusinessDay() ? 1 : 0;
        }
        if (date::clsDate::IsDate1BeforeDate2(DateFrom,DateTo)) {
            while (!date::clsDate::IsDate1EqualDate2(DateFrom, DateTo)) {
                if (date::clsDate::IsBusinessDay(DateFrom)) {
                    counter++;
                }
                date::clsDate::AddOneDay(DateFrom);
            }
            if (DateTo.IsBusinessDay()) {
                counter++;
            }
        }
        return counter ;
    }
    [[maybe_unused]] int clsDate::CalculateVacationDays(const clsDate &DateFrom, const clsDate &DateTo){
        return date::clsDate::CalculateBusinessDays(DateFrom,DateTo);
    }
    [[maybe_unused]] clsDate clsDate::CalculateVacationReturnDate(const clsDate& DateFrom, const int &VacationDays){
        int counter = 0;
        while (counter <= VacationDays){
            if (date::clsDate::IsBusinessDay(DateFrom)){
                counter++;
            }
            date::clsDate::AddOneDay(DateFrom);
        }

        return DateFrom ;
    }

    [[maybe_unused]] int* clsDate::getDayPointer(){
        return &this->date1._day;
    }
    [[maybe_unused]] void clsDate::setDateByReference(int& d, int& m, int& y) {
        this->date1._day = d;
        this->date1._month = m;
        this->date1._year = y;
    }
    [[maybe_unused]] bool clsDate::validateDateWithLambda(){
        auto valid = [this](){return this->IsValid();};
        return valid();
    }
    [[maybe_unused]] std::vector<int> clsDate::getDateAsVector(){
        return {this->date1._year, this->date1._month, this->date1._day};
    }
    [[maybe_unused]] int* clsDate::createDynamicArray(int size) const{
        int * arr = new int [size];
        arr[0] = this->date1._year ;
        arr[1] = this->date1._month ;
        arr[2] = this->date1._day ;
        return arr ;
    }
    [[maybe_unused]] std::unique_ptr<clsDate> clsDate::createSmartDate(int d, int m, int y){
        return std::make_unique<clsDate>(d,m,y);
    }
    [[maybe_unused]] void clsDate::printFormatted(std::ostream& os) const{
        os << this->date1._day << "/" << this->date1._month << "/" << this->date1._year <<endl;
    }



    clsDate::~clsDate() = default;



}
