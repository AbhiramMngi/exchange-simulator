#include "orderbook/Orderbook.hpp"
#include <vector>
#include <stdexcept>
#include <functional>


void OrderBook::add_order(Order order) {
    if (order.remaining_quantity == 0) throw std::logic_error("Empty Order!");
    
    auto bid_cmp = [](const Order& order1, const Order& order2) {
        return order1.price >= order2.price;
    };
    auto ask_cmp = [](const Order& order1, const Order& order2) {
        return order1.price <= order2.price;
    };

    std::function<bool(const Order&, const Order&)> cmp = order.side == Side::BUY? bid_cmp : ask_cmp;
    std::priority_queue<Order, std::vector<Order>, OrderComparator>& counterparties = order.side == Side::BUY? asks_: bids_;
    std::priority_queue<Order, std::vector<Order>, OrderComparator>& pq_orders = order.side == Side::BUY? bids_: asks_;


    while (order.remaining_quantity > 0 && !counterparties.empty() && cmp(order, counterparties.top())) {
        Order top = counterparties.top();
        counterparties.pop();
        if (order.remaining_quantity >= top.remaining_quantity) {
            order.remaining_quantity -= top.remaining_quantity;
            if (order.side == Side::BUY) trade_history.emplace_back(order.order_id, top.order_id, top.price, ++trade_sequence_count, top.remaining_quantity);
            else trade_history.emplace_back(top.order_id, order.order_id, top.price, ++trade_sequence_count, top.remaining_quantity);
        }
        else {
            top.remaining_quantity -= order.remaining_quantity;
            if (order.side == Side::BUY) trade_history.emplace_back(order.order_id, top.order_id, top.price, ++trade_sequence_count, order.remaining_quantity);
            else trade_history.emplace_back(top.order_id, order.order_id, top.price, ++trade_sequence_count, order.remaining_quantity);
            order.remaining_quantity = 0;
            counterparties.push(top);
        }
    }
    if (order.remaining_quantity > 0) pq_orders.push(order);

};

void OrderBook::cancel_order(OrderID id) {

};

Order OrderBook::best_ask(){
    return asks_.top();
};


Order OrderBook::best_bid() {
    return bids_.top();
};

std::size_t OrderBook::get_bid_count() {
    return bids_.size();
}

std::size_t OrderBook::get_ask_count() {
    return asks_.size();
}

std::vector<Trade>& OrderBook::trade_log() {
    return trade_history;
};

void OrderBook::clear() {
    trade_history.clear();
    bids_ = {};
    asks_ = {};
    trade_sequence_count = 0;
}