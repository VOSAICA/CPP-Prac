#include <iostream>
#include <string>

struct Sales_data
{
    friend std::ostream& operator<<(std::ostream& os, const Sales_data& item);
    friend std::istream& operator>>(std::istream& is, Sales_data& item);

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    Sales_data();
    Sales_data(const std::string& s, unsigned n, double p);
    explicit Sales_data(const std::string& s);
    explicit Sales_data(std::istream& is);

    std::string isbn() const; // 常量成员函数，改变this指针，使其指向常量Sales_data对象
    double avg_price() const;
    Sales_data& combine(const Sales_data&);
};

Sales_data::Sales_data() : Sales_data("Default", 0, 0)
{
#ifndef NDEBUG
    std::cout << "Default Constructor\n";
#endif
}

Sales_data::Sales_data(const std::string& s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n)
{
#ifndef NDEBUG
    std::cout << "Sales_data(const std::string& s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n)\n";
#endif
}

Sales_data::Sales_data(const std::string& s) : Sales_data(s, 0, 0)
{
#ifndef NDEBUG
    std::cout << "Sales_data(const std::string s) : Sales_data(s, 0, 0)\n";
#endif
}

Sales_data::Sales_data(std::istream& is)
{
#ifndef NDEBUG
    std::cout << "istream Constructor\n";
#endif
    std::cin >> *this;
}

std::string Sales_data::isbn() const
{
    return bookNo;
}

inline double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) // 因为常量Sales_data不能combine()，所以不用变成const成员函数
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::ostream& operator<<(std::ostream& os, const Sales_data& item)
{
    os << item.isbn() << ' ' << item.units_sold << ' ' << item.revenue << ' ' << item.avg_price();
    return os;
}

std::istream& operator>>(std::istream& is, Sales_data& item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
    {
        item.revenue = item.units_sold * price;
    }
    else
    {
        {
            item = Sales_data();
        }
    }
    return is;
}

int main()
{
    Sales_data a;
    std::cin >> a;
    std::cout << a;

    return 0;
}
