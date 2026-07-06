#include "orders/Order.hpp"
#include <stdexcept>

bool BuyComparator::operator()(const Order& a, const Order& b) const {
    if (a.side == Side::SELL || b.side == Side::SELL) throw std::logic_error("Expected BUY orders for Comparison");
    if (a.price != b.price) return a.price < b.price;
    return a.sequence_no > b.sequence_no;
}



bool SellComparator::operator()(const Order& a, const Order& b) const {
    if (a.side == Side::BUY || b.side == Side::BUY) throw std::logic_error("Expected SELL orders for Comparison");
    if (a.price != b.price) return a.price > b.price;
    return a.sequence_no > b.sequence_no;
}


