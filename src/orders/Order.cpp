#include "orders/Order.hpp"
#include <stdexcept>


bool OrderComparator::operator()(const Order& a, const Order& b) const {
    if (a.side != b.side) throw std::logic_error("Dissimilar order sides!");
    if (a.side == Side::BUY && b.side == Side::BUY) {
        if (a.price != b.price) return a.price < b.price;
        return a.sequence_no > b.sequence_no;
    }
    if (a.price != b.price) return a.price > b.price;
    return a.sequence_no > b.sequence_no;
}

std::ostream& operator<<(std::ostream& cout, const Trade& trade) {
    cout << trade.bid_order_id << " " << trade.ask_order_id << " " << trade.price << " " << trade.trade_no << " " << trade.quantity;
    return cout;
}

