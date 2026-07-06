#include "orders/Order.hpp"
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stdexcept>


class OrderBook {

    std::vector<Trade> trade_history;
    std::priority_queue<Order, std::vector<Order>, BuyComparator> bids_;
    std::priority_queue<Order, std::vector<Order>, SellComparator> asks_;

    public:
    void add_order(Order order);
    void cancel_order(OrderID id);
    Order best_bid();
    Order best_ask();
    std::vector<Trade> trade_log();
};