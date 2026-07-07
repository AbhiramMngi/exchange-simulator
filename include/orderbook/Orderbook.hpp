#include "orders/Order.hpp"
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stdexcept>
#include <memory>

class OrderBook {

    std::vector<Trade> trade_history;
    std::priority_queue<Order, std::vector<Order>, OrderComparator> bids_;
    std::priority_queue<Order, std::vector<Order>, OrderComparator> asks_;
    std::uint64_t trade_sequence_count; 
    OrderBook() = default;

    
    public:
    static OrderBook& getInstance() {
        static OrderBook ob;
        return ob;
    }; 
    void add_order(Order order);
    void cancel_order(OrderID id);
    Order best_bid();
    Order best_ask();
    std::size_t get_bid_count();
    std::size_t get_ask_count();
    std::vector<Trade>& trade_log();
    void clear();
};