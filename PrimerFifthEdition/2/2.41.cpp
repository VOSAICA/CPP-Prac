#include <iostream>
#include <string>

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main()
{
    Sales_data book, total;

    while (std::cin >> book.bookNo >> book.units_sold >> book.revenue)
    {
        total.units_sold += book.units_sold;
        total.revenue += book.revenue;
    }
    total.bookNo = book.bookNo;

    std::cout << total.bookNo << '\n'
              << total.units_sold << '\n'
              << total.revenue << std::endl;

    return 0;
}
