#include "Sales_data.h"

#include <iostream>

double Sales_data::avg_price() const {
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;	//把 rhs 的成员加到this对象上
    revenue += rhs.revenue;
    return *this;					// 返回调用该函数的对象
}

// 输入的信息包括 ISBN、售出总数和售出价格
std::istream &read(std::istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs,  const Sales_data &rhs)
{
    Sales_data sum = lhs;   //把 lhs 的数据成员拷贝给 sum
    sum.combine(rhs);       //把 rhs 的数据成员加到 sum 当中
    return sum;
}