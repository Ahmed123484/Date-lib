#include<iostream>
#include<ctime>
#include<cctype>
#include <vector>
#include<string>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <deque>
#include <utility>

using namespace std ;
enum enFormatDate {Unknown = 0 ,DMY = 1 , MDY = 2 , YMD = 3};
enum enDateCompare { Before [[maybe_unused]] = -1, Equal [[maybe_unused]] = 0, After [[maybe_unused]] = 1 };

namespace date {
    class clsDate{
        private :
            struct stDate{
                int _day {0};
                int _month {0};
                int _year {0};
            };
            stDate date1 ;
        static enFormatDate format (int d , int m , int y){
           if ((d > 12 && m <= 12 && y >31 )||(d > 1 && m <= 12 && y >31 )){
            return DMY ;
           }else if (d <= 12 && m > 12 && y > 31){
            return MDY;
           }else if (d > 31 && m <= 12 && y <= 31){
            return YMD ;
           }
           return Unknown ;
        } 
        void handleFormat (int d , int m , int y , enFormatDate resultH){
            switch (resultH){
                case DMY:
                    this->date1._day = d ;
                    this->date1._month = m ;
                    this->date1._year = y ;
                    break ;
                case MDY :
                    this->date1._day = m ;
                    this->date1._month = d ;
                    this->date1._year = y ;
                    break ;
                case YMD :
                    this->date1._day = y ;
                    this->date1._month = m ;
                    this->date1._year = d ;
                    break ;
                case Unknown :
                    cout << "Unknown this Format pls try again\n";
                    break;
                default :
                return ;
                break ;            
            }
        }   
        static bool _isLeapYear(int year) {
            return (year % 4 == 0) && 
                    (year % 100 != 0 || year % 400 == 0);
            }
        static int getDaysInMonth(int month, int year) {
            int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 
                                31, 31, 30, 31, 30, 31 };
            if (month < 1 || month > 12) return -1;
            if (month == 2 && _isLeapYear(year)) return 29;
            return daysInMonth[month - 1];
        }
        static string getShortMonthName (int month){
            const string arrShortMonths[12] = {
                "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
            };
            return arrShortMonths[month-1];
        }
        static string getShortDayName (int day){
            const string arrShortDays[7] = {
                "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
            };
            return arrShortDays[day];
        }
        static int getWeekdayIndex (int day , int month , int year){
            int a = (14 - month ) / 12 ;
            int y = year - a ;
            int m = month + (12 * a ) - 2;
            int d = (day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
            return d ;
        }
        [[nodiscard]] string calculateSpace () const;
        public:
        clsDate (int day , int month , int year ) ;
        clsDate ();
        explicit clsDate(const string& sDate);
        clsDate(int day , int year);
        ~clsDate();
        // setter day then month then year then object stDate
        [[maybe_unused]] void setDay (int day);
        void setMonth (int month);
        void setYear (int year);

        [[maybe_unused]] void setStDate(int day , int month , int year) ;
        // getter day then month then year then object stDate
        [[maybe_unused]] [[nodiscard]] int getDay () const;

        [[maybe_unused]] [[nodiscard]] int getMonth () const;

        [[maybe_unused]] [[nodiscard]] int getYear () const;
         
        // Print and Display Functions
        void printDate () const;

        [[maybe_unused]] static void Print(int,int,int);
        void PrintMonthCalendar();

        [[maybe_unused]] static void PrintMonthCalendar(int Month, int Year);

        [[maybe_unused]] void PrintYearCalendar() const;

        [[maybe_unused]] static void PrintYearCalendar(int Year);

        // Conversion and Formatting Functions
        [[nodiscard]] [[maybe_unused]] string DateToString() const;

        [[maybe_unused]] static string DateToString(const clsDate& Date);
        [[nodiscard]] string DayShortName() const;

        [[maybe_unused]] static string DayShortName(int);

        [[maybe_unused]] static string DayShortName(int, int, int);
        [[nodiscard]] string MonthShortName() const;

        [[maybe_unused]] static string MonthShortName(int);

        // Date and System Functions
        [[maybe_unused]] static clsDate GetSystemDate();

        // Date Validation Functions
        [[nodiscard]] bool IsValid() const;

        [[maybe_unused]] static bool IsValidDate(const clsDate& Date);

        // Leap Year Functions
        [[nodiscard]] bool isLeapYear() const;
        static bool isLeapYear(int);

        // Time Unit Calculation Functions - Year
        [[nodiscard]] int NumberOfDaysInAYear() const;
        static int NumberOfDaysInAYear(int Year);
        [[nodiscard]] int NumberOfHoursInAYear() const;
        static int NumberOfHoursInAYear(int Year);
        [[nodiscard]] int NumberOfMinutesInAYear() const;
        static int NumberOfMinutesInAYear(int Year);

        [[maybe_unused]] [[nodiscard]] int NumberOfSecondsInAYear() const;

        [[maybe_unused]] static int NumberOfSecondsInAYear(int Year);

        // Time Unit Calculation Functions - Month
        [[nodiscard]] int NumberOfDaysInAMonth() const;

        [[maybe_unused]] static int NumberOfDaysInAMonth(int Month, int Year);
        [[nodiscard]] int NumberOfHoursInAMonth() const;

        [[maybe_unused]] static int NumberOfHoursInAMonth(int Month, int Year);
        [[nodiscard]] int NumberOfMinutesInAMonth() const;

        [[maybe_unused]] static int NumberOfMinutesInAMonth(int Month, int Year);
        [[nodiscard]] int NumberOfSecondsInAMonth() const;

        [[maybe_unused]] static int NumberOfSecondsInAMonth(int Month, int Year);

        // Day Order Functions
        [[nodiscard]] int DayOfWeekOrder() const;

        [[maybe_unused]] static int DayOfWeekOrder(int Day, int Month, int Year);

        // Period Calculation Functions
        [[nodiscard]] int DaysFromTheBeginingOfTheYear() const;

        [[maybe_unused]] static int DaysFromTheBeginingOfTheYear(int Day, int Month, int Year);

        [[maybe_unused]] static clsDate GetDateFromDayOrderInYear(int DateOrderInYear, int Year);
        [[nodiscard]] [[maybe_unused]] std::chrono::sys_days to_sys_days() const;
        // Add Time Functions - Days
        void AddDays(int Days);
        void AddOneDay();

        [[maybe_unused]] static clsDate AddOneDay(clsDate Date);

        [[maybe_unused]] void IncreaseDateByXDays(int Days);

        [[maybe_unused]] static void IncreaseDateByXDays(int Days, clsDate& Date);

        // Add Time Functions - Weeks
        [[maybe_unused]] void IncreaseDateByOneWeek();

        [[maybe_unused]] static void IncreaseDateByOneWeek(clsDate& Date);

        [[maybe_unused]] void IncreaseDateByXWeeks(short Weeks);

        [[maybe_unused]] static void IncreaseDateByXWeeks(short Weeks, clsDate& Date);

        // Add Time Functions - Months
        void IncreaseDateByOneMonth();

        [[maybe_unused]] static void IncreaseDateByOneMonth(clsDate& Date);

        [[maybe_unused]] void IncreaseDateByXMonths(short Months);

        [[maybe_unused]] static void IncreaseDateByXMonths(short Months, clsDate& Date);

        // Add Time Functions - Years
        void IncreaseDateByOneYear();
        [[maybe_unused]] static void IncreaseDateByOneYear(clsDate& Date);
        void IncreaseDateByXYears(int Years);
        [[maybe_unused]] static void IncreaseDateByXYears(int Years, clsDate& Date);

        // Add Time Functions - Decades and Centuries
        [[maybe_unused]] void IncreaseDateByOneDecade();
        [[maybe_unused]] static void IncreaseDateByOneDecade(clsDate& Date);
        [[maybe_unused]] void IncreaseDateByXDecades(int Decade);
        [[maybe_unused]] static void IncreaseDateByXDecades(int Decade, clsDate& Date);
        [[maybe_unused]] void IncreaseDateByOneCentury();
        [[maybe_unused]] static void IncreaseDateByOneCentury(clsDate& Date);
        [[maybe_unused]] void IncreaseDateByOneMillennium();
        [[maybe_unused]] static void IncreaseDateByOneMillennium(clsDate& Date);

        // Subtract Time Functions - Days
        [[maybe_unused]] void DecreaseDateByOneDay(int Day = 1) ;
        [[maybe_unused]] static clsDate DecreaseDateByOneDay(clsDate Date);
        [[maybe_unused]] void DecreaseDateByXDays(int Days);
        [[maybe_unused]] static void DecreaseDateByXDays(int Days, clsDate& Date);

        // Subtract Time Functions - Weeks
        [[maybe_unused]] void DecreaseDateByOneWeek();
        [[maybe_unused]] static void DecreaseDateByOneWeek(clsDate& Date);
        [[maybe_unused]] void DecreaseDateByXWeeks(int Weeks);
        [[maybe_unused]] static void DecreaseDateByXWeeks(int Weeks, clsDate& Date);

        // Subtract Time Functions - Months
        [[maybe_unused]] void DecreaseDateByOneMonth(int month = 1);
        [[maybe_unused]] static void DecreaseDateByOneMonth(clsDate& Date);
        [[maybe_unused]] void DecreaseDateByXMonths(int Months);
        [[maybe_unused]] static void DecreaseDateByXMonths(int Months, clsDate& Date);

        // Subtract Time Functions - Years
        [[maybe_unused]] void DecreaseDateByOneYear();
        [[maybe_unused]] static void DecreaseDateByOneYear(clsDate& Date);
        [[maybe_unused]] void DecreaseDateByXYears(int Years);
        [[maybe_unused]] static void DecreaseDateByXYears(int Years, clsDate& Date);

        // Subtract Time Functions - Decades and Centuries
        [[maybe_unused]] void DecreaseDateByOneDecade();
        [[maybe_unused]] static void DecreaseDateByOneDecade(clsDate& Date);
        [[maybe_unused]] void DecreaseDateByXDecades(int Decades);
        [[maybe_unused]] static void DecreaseDateByXDecades(int Decades, clsDate& Date);
        [[maybe_unused]] void DecreaseDateByOneCentury();
        [[maybe_unused]] static void DecreaseDateByOneCentury(clsDate& Date);
        [[maybe_unused]] void DecreaseDateByOneMillennium();
        [[maybe_unused]] static void DecreaseDateByOneMillennium(clsDate& Date);

        // Date Comparison Functions
        [[maybe_unused]] static bool IsDate1BeforeDate2(const clsDate &Date1,const clsDate &Date2) ;
        [[nodiscard]] [[maybe_unused]] bool IsDateBeforeDate2(const clsDate &Date2) const ;
        [[maybe_unused]] static bool IsDate1EqualDate2(const clsDate &Date1,const clsDate &Date2);
        [[nodiscard]] [[maybe_unused]] bool IsDateEqualDate2(const clsDate &Date2) const ;
        [[maybe_unused]] static bool IsDate1AfterDate2(const clsDate &Date1,const clsDate &Date2);
        [[nodiscard]] [[maybe_unused]] bool IsDateAfterDate2(const clsDate &Date2) const ;
        [[maybe_unused]] static enDateCompare CompareDates(const clsDate &Date1,const clsDate &Date2);
        [[nodiscard]] [[maybe_unused]] enDateCompare CompareDates(const clsDate &Date2) const ;

        // Difference Calculation Functions
        [[maybe_unused]] static int GetDifferenceInDays(clsDate &Date1,clsDate &Date2,bool IncludeEndDay = false);
        [[maybe_unused]] int GetDifferenceInDays(clsDate &Date2, bool IncludeEndDay = false) const;
        [[maybe_unused]] static int CalculateMyAgeInDays(clsDate &DateOfBirth);
        [[maybe_unused]] static void SwapDates(clsDate& Date1, clsDate& Date2);

        // Date Properties Check Functions
        [[nodiscard]] [[maybe_unused]] bool IsLastDayInMonth()const;
        [[maybe_unused]] static bool IsLastDayInMonth(const clsDate &Date);
        [[maybe_unused]] static bool IsLastMonthInYear(const int &Month);
        [[nodiscard]] [[maybe_unused]] bool IsEndOfWeek()const;
        [[maybe_unused]] static bool IsEndOfWeek(const clsDate &Date);
        [[nodiscard]] [[maybe_unused]] bool IsWeekEnd()const ;
        [[maybe_unused]] static bool IsWeekEnd(const clsDate &Date);
        [[nodiscard]] [[maybe_unused]] bool IsBusinessDay()const ;
        [[maybe_unused]] static bool IsBusinessDay(const clsDate &Date);

        // Remaining Days Calculation Functions
        [[nodiscard]] [[maybe_unused]] int DaysUntilTheEndOfWeek() const;
        [[maybe_unused]] static int DaysUntilTheEndOfWeek(const clsDate &Date);
        [[nodiscard]] [[maybe_unused]] int DaysUntilTheEndOfMonth() const;
        [[maybe_unused]] static int DaysUntilTheEndOfMonth(const clsDate &Date1);
        [[nodiscard]] [[maybe_unused]] int DaysUntilTheEndOfYear() const;
        [[maybe_unused]] static int DaysUntilTheEndOfYear(const clsDate &Date1);
        [[maybe_unused]] static const clsDate *maxDate (const clsDate &Date1, const clsDate &Date2);
        [[maybe_unused]] static const clsDate *minDate (const clsDate &Date1,const  clsDate &Date2);
        [[nodiscard]] [[maybe_unused]] const clsDate *maxDate (const clsDate &Date2)const;
        [[nodiscard]] [[maybe_unused]] const clsDate *minDate (const  clsDate &Date2)const;


        // Business and Holiday Functions
        [[maybe_unused]] static int CalculateBusinessDays(const clsDate& DateFrom,const clsDate& DateTo);
        [[maybe_unused]] static int CalculateVacationDays(const clsDate &DateFrom, const clsDate &DateTo);
        [[maybe_unused]] static clsDate CalculateVacationReturnDate(const clsDate& DateFrom,const int &VacationDays);

         // Method 1: Basic pointer usage - returns pointer to day
        // يدرب على: المؤشرات (Pointers)
         [[maybe_unused]] int* getDayPointer();

        // Method 2: Reference parameter - sets date using references
        // يدرب على: المؤشرات والمراجع (References)
        [[maybe_unused]] void setDateByReference(int& d, int& m, int& y) ;

        // Method 3: Lambda function to validate date
        [[maybe_unused]] bool validateDateWithLambda();

        // Method 4: STL vector operations
        // يدرب على: مكتبة STL
        [[maybe_unused]] std::vector <int> getDateAsVector();

        // Method 5: Dynamic memory allocation
        // يدرب على: إدارة الذاكرة (Memory Management)
        [[nodiscard]] [[maybe_unused]] int* createDynamicArray(int size) const;

        // Method 6: Smart pointer usage
        // يدرب على: إدارة الذاكرة (Smart Pointers)
        [[maybe_unused]] static std::unique_ptr<clsDate> createSmartDate(int d, int m, int y);

        // Method 7: Formatted output stream
        // يدرب على: التنسيق والطباعة
        [[maybe_unused]] void printFormatted(std::ostream& os) const;

        // Method 8: Exception handling with try/catch
        // يدرب على: الاستثناءات (try/catch)
        void setDateSafely(int d, int m, int y);

        // Method 9: File writing operations
        // يدرب على: الملفات
        void saveToFile(const std::string& filename);

        // Method 10: File reading operations
        // يدرب على: الملفات
        void loadFromFile(const std::string& filename);

        // Method 11: Bitwise operations for date encoding
        // يدرب على: المعالجة الثنائية (bitwise)
        unsigned int encodeDateBitwise();

        // Method 12: Bitwise decoding
        // يدرب على: المعالجة الثنائية (bitwise)
        void decodeDateBitwise(unsigned int encoded);

        // Method 15: Static method to get object count
        // يدرب على: static members
        static int getObjectCount();

        // Method 16: Static method to create date from string
        // يدرب على: static members
        static clsDate createFromString(const std::string& dateStr);

        // Method 17: Virtual method for inheritance
        // يدرب على: الوراثة
    //    virtual std::string getDateType() const;

        // Method 18: Friend function declaration
        // يدرب على: الكلاسات والوظائف الصديقة (friend)
        friend std::ostream& operator<<(std::ostream& os, const clsDate& date);

        // Method 19: Static cast demonstration
        // يدرب على: أنواع الـ casting
        double getDayAsDouble();

        // Method 20: Dynamic cast usage (with inheritance)
        // يدرب على: أنواع الـ casting
    //    virtual void demonstrateDynamicCast();

        // Method 21: std::function usage
        // يدرب على: std::function
        void processDateWithFunction(std::function<void(clsDate&)> func);

        // Method 22: Function pointer parameter
        // يدرب على: std::function والمؤشرات
        void applyFunction(void (*func)(clsDate&));

        // Method 23: Nested class usage
        // يدرب على: التوابع والكلاسات المتداخلة
        bool isValidDate();

        // Method 24: Current system time
        // يدرب على: التاريخ والوقت
        void setToCurrentDate();

        // Method 25: Chrono library usage
        // يدرب على: التاريخ والوقت
        long long getTimestamp();

        // Method 26: STL map operations
        // يدرب على: مكتبة STL
        std::map<std::string, int> getDateAsMap();

        // Method 27: STL set operations
        // يدرب على: مكتبة STL
        std::set<int> getUniqueDigits();

        // Method 28: STL algorithm usage
        // يدرب على: مكتبة STL
        void sortDateComponents();

        // Method 29: Memory leak prevention
        // يدرب على: إدارة الذاكرة
        void cleanupResources();

        // Method 30: Shared pointer usage
        // يدرب على: إدارة الذاكرة
        std::shared_ptr<std::string> getFormattedDateShared();

        // Method 31: Custom exception throwing
        // يدرب على: الاستثناءات
        void throwCustomException();

        // Method 32: Exception specification
        // يدرب على: الاستثناءات
        void noThrowMethod() noexcept;

        // Method 33: Binary file operations
        // يدرب على: الملفات
        void saveBinaryToFile(const std::string& filename);

        // Method 34: Binary file reading
        // يدرب على: الملفات
        void loadBinaryFromFile(const std::string& filename);

        // Method 35: Bit manipulation flags
        // يدرب على: المعالجة الثنائية
        void setDateFlags(unsigned char flags);

        // Method 36: Bit checking
        // يدرب على: المعالجة الثنائية
        bool checkDateFlag(unsigned char flag);

        // Method 40: Static constant access
        // يدرب على: static members
        static const std::vector<std::string>& getMonthNames();

        // Method 41: Virtual destructor for inheritance
        // يدرب على: الوراثة
    //    virtual ~clsDate() {}

        // Method 42: Protected method access
        // يدرب على: الوراثة
    //    virtual int getDaysInMonth();

        // Method 43: Friend class demonstration
        // يدرب على: friend
        friend class DateFormatter;

        // Method 44: Const cast usage
        // يدرب على: أنواع الـ casting
        void modifyConstDate() const;

        // Method 45: Reinterpret cast demo
        // يدرب على: أنواع الـ casting
        void demonstrateReinterpretCast();

        // Method 46: Function object usage
        // يدرب على: std::function
        void useFunctionObject();

        // Method 47: Callback function
        // يدرب على: std::function
        void setDateChangeCallback(std::function<void(const clsDate&)> callback);

        // Method 48: Nested enum
        // يدرب على: التوابع والكلاسات المتداخلة
        enum class DateFormat { DMY, MDY, YMD };

        // Method 49: Using nested enum
        // يدرب على: التوابع والكلاسات المتداخلة
        std::string formatDate(DateFormat format);

        // Method 50: Date arithmetic
        // يدرب على: التاريخ والوقت
    //    clsDate addDays(int days);

        // Method 51: STL iterator usage
        // يدرب على: مكتبة STL
        void processDateDigits();

        // Method 52: STL find algorithm
        // يدرب على: مكتبة STL
        bool containsDigit(int digit);

        // Method 53: Memory pool simulation
        // يدرب على: إدارة الذاكرة
        void* allocateFromPool(size_t size);

        // Method 54: RAII pattern
        // يدرب على: إدارة الذاكرة
        class ResourceGuard;

        // Method 55: Exception safety guarantee
        // يدرب على: الاستثناءات
        void strongExceptionSafety();

        // Method 56: File stream manipulation
        // يدرب على: الملفات
        void writeFormattedToFile(const std::string& filename);

        // Method 57: CSV file operations
        // يدرب على: الملفات
        void exportToCSV(const std::string& filename);

        // Method 58: Bit field operations
        // يدرب على: المعالجة الثنائية
        struct DateBits { unsigned day:5, month:4, year:12; };

        // Method 59: Bitwise comparison
        // يدرب على: المعالجة الثنائية
        bool bitwiseEquals(const clsDate& other);

        // Method 60: Property chain setting
        // يدرب على: الخصائص set/get
        clsDate& setIsYear(int y);

        // Method 61: Lazy property evaluation
        // يدرب على: الخصائص set/get
        std::string getFormattedDate();

        // Method 62: Static factory method
        // يدرب على: static members
        static clsDate today();

        // Method 63: Static registry pattern
        // يدرب على: static members
        static void registerDate(const clsDate& date);

        // Method 64: Abstract method simulation
        // يدرب على: الوراثة
    //    virtual void displayDate() = 0; // يحتاج override في derived class

        // Method 65: Template-like behavior
        // يدرب على: الوراثة
    //    virtual void processDate();

        // Method 66: Friend operator
        // يدرب على: friend
        friend bool operator==(const clsDate& lhs, const clsDate& rhs);

        // Method 67: C-style cast avoidance
        // يدرب على: أنواع الـ casting
        void safeCasting();

        // Method 68: Custom casting operator
        // يدرب على: أنواع الـ casting
        explicit operator std::string() const;

        // Method 69: Functional programming style
        // يدرب على: std::function
        std::function<bool(int)> getValidator();

        // Method 70: Higher-order function
        // يدرب على: std::function
        void transform(std::function<int(int)> transformer);

        // Method 71: Nested struct
        // يدرب على: التوابع والكلاسات المتداخلة
        struct DateComponents { int d, m, y; };

        // Method 72: Complex nested usage
        // يدرب على: التوابع والكلاسات المتداخلة
        DateComponents getComponents();

        // Method 73: Time zone handling
        // يدرب على: التاريخ والوقت
        void setTimeZone(int utcOffset);

        // Method 74: Duration calculations
        // يدرب على: التاريخ والوقت
        std::chrono::days daysBetween(const clsDate& other);

        // Method 75: STL priority queue usage
        // يدرب على: مكتبة STL
        void addToPriorityQueue();

        // Method 76: STL deque operations
        // يدرب على: مكتبة STL
        std::deque<int> getDateDeque();

        // Method 77: Custom allocator simulation
        // يدرب على: إدارة الذاكرة
        void useCustomAllocator();

        // Method 78: Memory alignment
        // يدرب على: إدارة الذاكرة
        void* alignedAllocation(size_t size);

        // Method 79: Exception hierarchy
        // يدرب على: الاستثناءات
        class DateException : public std::exception {};

        // Method 80: Exception chaining
        // يدرب على: الاستثناءات
        void chainExceptions();

        // Method 81: JSON-like file format
        // يدرب على: الملفات
        void saveAsJSON(const std::string& filename);

        // Method 82: XML-like parsing
        // يدرب على: الملفات
        void loadFromXML(const std::string& filename);

        // Method 83: Bit shifting operations
        // يدرب على: المعالجة الثنائية
        unsigned int shiftEncodedDate(int positions);

        // Method 84: Bitwise hash function
        // يدرب على: المعالجة الثنائية
        size_t getBitwiseHash();

        // Method 85: Computed properties
        // يدرب على: الخصائص set/get
        bool getIsWeekend();

        // Method 86: Property change notification
        // يدرب على: الخصائص set/get
        void addPropertyChangeListener();

        // Method 87: Thread-safe static
        // يدرب على: static members
        static clsDate& getInstance();

        // Method 88: Static initialization order
        // يدرب على: static members
        static void initializeStatics();

        // Method 89: Multiple inheritance simulation
        // يدرب على: الوراثة
    //    virtual void implementInterface1();

        // Method 90: Virtual inheritance concepts
        // يدرب على: الوراثة
    //    virtual void implementInterface2();

        // Method 91: Friend template simulation
        // يدرب على: friend
        template<typename T> friend void processDate(T& date);

        // Method 92: Advanced casting scenarios
        // يدرب على: أنواع الـ casting
        void handlePolymorphicCasting();

        // Method 93: Function composition
        // يدرب على: std::function
        std::function<std::string(clsDate)> getComposedFormatter();

        // Method 94: Currying simulation
        // يدرب على: std::function
        std::function<bool(int)> getPartialValidator(int minYear);

        // Method 95: Complex nested patterns
        // يدرب على: التوابع والكلاسات المتداخلة
        class DateIterator { /* nested iterator */ };

        // Method 96: Iterator implementation
        // يدرب على: التوابع والكلاسات المتداخلة
        DateIterator begin();

        // Method 97: Epoch time conversion
        // يدرب على: التاريخ والوقت
        time_t toEpochTime();

        // Method 98: Date parsing from various formats
        // يدرب على: التاريخ والوقت
        static clsDate parseDate(const std::string& dateStr, const std::string& format);

        // Method 99: STL unordered_map usage
        // يدرب على: مكتبة STL
        void cacheInHashMap();

        // Method 100: Complete example combining all concepts
        // يدرب على: جميع المفاهيم مجتمعة
        void demonstrateAllConcepts();

    };
}
