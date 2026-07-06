#include "orderbook/Orderbook.hpp"
#include <vector>


void OrderBook::add_order(Order order) {

};

void OrderBook::cancel_order(OrderID id) {

};

Order OrderBook::best_ask(){
    return Order{};
};


Order OrderBook::best_bid() {
    return Order{};
};

std::vector<Trade> OrderBook::trade_log() {
    return std::vector<Trade>();
};
