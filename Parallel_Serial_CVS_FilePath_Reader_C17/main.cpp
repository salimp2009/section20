#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <optional>
#include <string_view>
#include <string>
#include <utility>
#include <vector>

#ifdef _MSC_VER_
    #include <execution>
#endif

#define CSV_EXTENSION(x) ".csv"
static const char* const CSV_EXTENSION =".csv";
static constexpr char DEFAULT_DATE_DELIM ='-';
static constexpr char CSV_DELIM =';';

namespace fs=std::filesystem;


[[nodiscard ]] std::vector<std::string_view> SplitString(std::string_view str, char delim)
{
    std::vector<std::string_view> output;
    
    for(auto first=str.begin(), second=str.begin(), last=str.end(); second!=last && first!=last; first=std::next(second))
    {
        second=std::find(first, last, delim);    // compare with the find of member function str
        output.emplace_back(&*first, std::distance(first, second));
        if(second ==last)     // not sure if we need this since we already defined second!=last in the for loop condition
            break;            // if it is needed , not sure why "return output;" is not used instead "break;"
    }
    
    return output;
}

template<typename T>
[[nodiscard]] std::optional<T> TryConvert(std::string_view sv) noexcept
{
    T value{};
    
    const auto last = sv.data() + sv.size();
    const auto res = std::from_chars(sv.data(), last, value); // convert std::string to numeric of value
    if(res.ec ==std::errc{} && res.ptr == last)   // if std::errc{} returns a null value if the conversion is successfull
        return value;                            // res.ptr is a pointer to first charcter that is not a value so if it is equal to last
                                                 // that mean we checked the whole string
    return std::nullopt;
}

// as of May27, 2020 the conversion to floating point types dont works
// other than VS Studio (Windows) MSVC compiler
// Mac version of clang does not support it yet ; need to check the latest version of clang
// this version of code is too heavy since std::string_view is converted back to std::string

#ifndef _MSC_VER
template<>
[[nodiscard]] std::optional<double> TryConvert(std::string_view sv) noexcept
{
    std::string str{sv};
    return ::atof(str.c_str());
}
#endif 

class Date
{
public:
enum class Format {DayMonthYear, YearMonthDay};
public:
    Date()=default;
    Date(uint8_t day, uint8_t month, uint16_t year): mDay{day}, mMonth{month}, mYear{year} {}
    
    explicit Date(std::string_view sv, char delim=DEFAULT_DATE_DELIM, Format fmt=Format::DayMonthYear);
    
    bool IsInValid() const noexcept 
    { 
        return mDay<=0 || mMonth<=0 || mYear<=0 || mDay>31 || mMonth>12;
    }
    
    friend bool operator<(const Date& lhs, const Date& rhs) noexcept 
    {
        return std::tie(lhs.mYear, lhs.mMonth, lhs.mDay)< std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
    }
    
    friend bool operator<=(const Date& lhs, const Date& rhs) noexcept 
    {
        return std::tie(lhs.mYear, lhs.mMonth, lhs.mDay)<=std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Date& d) 
    {
       //std::printf("%d-%d-%d", d.mDay, d.mMonth, d.mYear);
       // return os;
       return os<<(uint16_t)d.mDay<<DEFAULT_DATE_DELIM<<(uint16_t)d.mMonth<<DEFAULT_DATE_DELIM<<d.mYear;      // std::cout has problems with printing mDay and mYear because they are uint8_t casting to uint16_t worked; 
       
    }
    
private:
    uint8_t  mDay{0};   // 0 is invalid; max value: 31
    uint8_t  mMonth{0}; // 0 is invalid; max value: 12
    uint16_t mYear{0};  // 0 is invalid;
};

Date::Date(std::string_view sv, char delim, Date::Format fmt)
{
    const auto columns = SplitString(sv, delim);            // type of columns is std::vector<std::string_view> 
                                                            // although returning string_view from a function is dangerous, here 
    if(columns.size()==3)                                   // we still own the original string and final return value will be a date therefore it is OK
    {
        mDay=TryConvert<uint8_t>(columns[fmt==Format::DayMonthYear ? 0 : 2]).value_or(0);    // .value_or(0) is used for std::optional that we get frm TryConvert() function
        mMonth=TryConvert<uint8_t>(columns[1]).value_or(0);                                  // if TryConvert() get an empty std::optional, value_or(0) assigns "zero" as a fallback
        mYear=TryConvert<uint16_t>(columns[fmt==Format::DayMonthYear ? 2: 0]).value_or(0);   // we could dereference the the result from TryConvert() function 
                                                                                            // but if the conversion is not successfull than it will cause undefined behaviour
        if(IsInValid())
            std::cout<<"Cannot convert from: "<<sv<<'\n';                                   // original version was with throw; no fan of throw or std::cout !!!
    }
    else 
    {
        //throw std::run_time_error("Cannot convert Date from "+std::string(sv));        // refactor this to nothrow; instead log the total lines failed and total lines processed
        std::printf("Cannot convert Date from %s...", sv.data());                                         // or just disable it via macro to switch on / off
       // std::cout<<"Cannot convert Date from: "<<sv<<'\n';
    }                                                                                     
}


struct Result
{
    // Result()=default;
    // Result(std::string filename, totalValue): mFilename{std::move(filename)}, Sum{totalValue} { }  // check if std::move() wont be a problem cause filename used other functions
    std::string mFilename;
    double Sum{0.0};
};

void ShowResults(const std::vector<Result>& results, Date startDate, Date endDate)
{
   
     const std::size_t maxStringLen=std::accumulate(std::cbegin(results), std::cend(results), 0,
                                                       [](std::size_t l, const auto& result) { return std::max(l, result.mFilename.length()); } );  // lambda returns the maximum lentgth of the paths; it does not do adding
                                                      
     if(!startDate.IsInValid() && !endDate.IsInValid())
         std::cout<<" | Total Orders Value Between "<<startDate<<" and "<<endDate<<'\n';
     else if(!startDate.IsInValid())
         std::cout<< " | Total Orders Value Between "<<startDate<<'\n';
    else
        std::cout<<" | Total Orders Value\n";
        
    for(const auto& [fileName, sum] : results)
        std::cout<< std::setw(maxStringLen + 1)<<std::left <<fileName <<" | "<<std::fixed<<std::setprecision(2)<<sum<<'\n';
  
}

[[nodiscard]] std::string GetFileContents(const fs::path& filePath)
{
    
    
    std::ifstream inFile{filePath, std::ios::in | std::ios::binary};
    if(!inFile)
    {
        throw std::runtime_error("Cannot open "+ filePath.filename().string());
    }
    
    std::string str(static_cast<size_t>(fs::file_size(filePath)), 0);
    
    inFile.read(str.data(), str.size());
    if(!inFile)
        throw std::runtime_error("Could not read the full contents from "+ filePath.filename().string());

    return str;
}

[[nodiscard]] std::vector<std::string_view> SplitLines(std::string_view str)
{
    auto lines = SplitString(str, '\n');

    if(!lines.empty() && lines[0].back()=='\r')  // Windows CR conversion; windows converts text files 
    {                                            // from Unix style to Windows style by adding '\r' to end of line 
        for(auto &&line : lines)                 // Windows style end of line "\r\n" , Unix style: '\n'
        {
          if(line.back()=='\r')
              line.remove_suffix(1);            // remove '\r' at the end 
        }
    }    
    return lines;
}

class OrderRecord
{
public:
    OrderRecord()=default;
    OrderRecord(Date date, std::string coupon, double unitprice=0.0, double discount=0.0, unsigned int quantity=0u) noexcept
               :mDate{date}, mCouponCode{std::move(coupon)}, mUnitPrice{unitprice},  mDiscount{discount}, mQuantity{quantity} {}
   
    double CalcRecordPrice() const noexcept { return mQuantity*(mUnitPrice*(1.0-mDiscount));} 
    
    bool CheckDate(const Date& startDate, const Date& endDate) const noexcept 
    {
        return (startDate.IsInValid() || startDate<=mDate) && (endDate.IsInValid() || mDate<=endDate);
    }
    
public:

// enum class was not used so we can use it as an array index 
enum Indices {DATE, COUPON, UNIT_PRICE, DISCOUNT, QUANTITY, ENUM_LENGTH};
                  
 private:
   Date mDate;
   std::string mCouponCode;
   double mUnitPrice;
   double mDiscount;
   unsigned int mQuantity;
};

[[nodiscard]] OrderRecord LineToRecord(std::string_view sv)
{
    const auto cols = SplitString(sv, CSV_DELIM);
    
    if(cols.size()==static_cast<std::size_t>(OrderRecord::ENUM_LENGTH))
    {
        const auto unitPrice = TryConvert<double>(cols[OrderRecord::UNIT_PRICE]);           // type of unitPrice is std::optional<T>; in order to access the value dereference it as a pointer *unitPrice
        const auto discount  = TryConvert<double>(cols[OrderRecord::DISCOUNT]);
        const auto quantity  = TryConvert<unsigned int>(cols[OrderRecord::QUANTITY]);
        
        if(unitPrice && discount && quantity)   // check if TryConvert was successfull; if not it returns nullopt thru std::optional
        {
            return { Date(cols[OrderRecord::DATE]), std::string(cols[OrderRecord::COUPON]), *unitPrice, *discount, *quantity}; //to access the value o f unitPrice, discount & quantity derefence them since types are std::optional
        }
    }
    
    std::printf("Cannot convert Record from %s", sv.data()); //TODO : check if string_view data() works with printf !!!! 
    return OrderRecord{};                                    // sv.data() with printf will return the full character array therefore if the str_view
}                                                            // refers to a part of the original string then you will get still full string   
                                                             // if part of the string will be printed then do this;
                                                             // printf("%.*s\n....", static_cast<int>(sv.size()), sv.data() );
                                                             // the * will get the casted size value as a precision therefore it wil only print the specified size of string_view
[[nodiscard]] std::vector<OrderRecord> LinesToRecords(const std::vector<std::string_view>& lines)
{
      std::vector<OrderRecord> outRecords(lines.size());
// paralel algorithms supported by Microsoft or GCC 9.1 + ; no support Mac Clang      
#ifdef _MSC_VER_ 
    // parallel version
    std::transform(std::execution::par, lines.begin(), lines.end(), std::begin(outRecords), LineToRecord);  // back_inserter is not thread safe because i
#else    
    // serial version
    std::transform(lines.begin(), lines.end(), std::back_inserter(outRecords), LineToRecord);
#endif    
    return outRecords;
}

[[nodiscard]] std::vector<OrderRecord> LoadRecords(const fs::path& filename)
{
    const auto content  = GetFileContents(filename);    // type of content = std::string
    
    const auto lines    = SplitLines(content);          // type of line =std::vector<std::string_view>
    
    
    return LinesToRecords(lines);
}

[[nodiscard]] double CalcTotalOrder(const std::vector<OrderRecord>& records, const Date& startDate, const Date& endDate)
{
   
    #ifdef _MSC_VER_ // TODO ; add timer and test on windows
         // paralel version supported MS only
         return std::transform_reduce(std::excecution::par, std::begin(records), std::end(records), 
                                     0.0,                                                       // initial value
                                     std::plus<>(),                                             // std::plus<> deduces the types of arguments if the type is not passed
                                     [&startDate, &endDate](const OrderRecord& rec) 
                                     {
                                         if(rec.CheckDate(startDate, endDate))
                                             return rec.CalcRecordPrice();
                                         else
                                             return 0.0;
                                     }
                                 ); 
    #else   // serial version
        return std::accumulate(std::begin(records), std::end(records), 0.0, [&startDate, &endDate](double val, const OrderRecord& rec)
                                 {
                                    if(rec.CheckDate(startDate, endDate))
                                        return val + rec.CalcRecordPrice();
                                    else
                                        return val;
                                  }                        
                              );
   #endif
}


// CalcResults; converts  data from the file into a list of records to process
//              calculates a sum of records between given dates
[[nodiscard]] std::vector<Result> CalcResults(const std::vector<fs::path>& paths, Date startDate, Date endDate)
{
    std::vector<Result>results;
    
    for(const auto& p: paths) 
    {
        const auto records    = LoadRecords(p);
        const auto totalValue = CalcTotalOrder(records, startDate, endDate);
        results.push_back({p.string(), totalValue});        // refactor with emplace_back but had to include constructor w/ args in Result struct so emplace_back can work
    }
    
    return results;
}

bool IsCSVFile(const fs::path& p)
{
    return fs::is_regular_file(p) && p.extension()==CSV_EXTENSION;
}

[[nodiscard]] std::vector<fs::path> CollectPaths(const fs::path& startPath)
{
    std::vector<fs::path>paths;                 // will collect regular files with cvs extension inside entry path; startPath
    fs::directory_iterator dirPos{startPath};   // create const iterator from the given path    
    
    // go thru contents of a given path and if it is regular file with csv extension then 
    // insert into paths so we collect the files; later we will go thru the files create Records
    std::copy_if(fs::begin(dirPos), fs::end(dirPos), std::back_inserter(paths), IsCSVFile);
    
    return paths;
}

int main(int argc, const char** argv)
{
    
    if(argc <=1)
        return 1;
    try {
        
        const auto paths=CollectPaths(argv[1]);                          // type of paths=std::vector<fs::path>
        
        if (paths.empty()) 
        {
            std::printf("no files to process..\n");
            return 0;
        }
        
        const Date startDate = argc > 2 ? Date(argv[2]) : Date();           // type of startDate is Date() class
        const Date endDate   = argc > 3 ? Date(argv[3]) : Date();

        const auto results   = CalcResults(paths, startDate, endDate);      // type of results; std::vector<Result>
        
        ShowResults(results, startDate, endDate);

    }
    catch (const fs::filesystem_error& e) 
    {
        std::cerr<<"filesystem error! "<< e.what()<<'\n';
    }
    
    catch (const std::runtime_error& e)
    {
        std::cerr<<"runtime error! "<<e.what()<<'\n';
    }
  
    return 0;
}
