#include <cstdint>
#include <iostream>

enum class Side: std::uint8_t {
    BUY,
    SELL
};


using OrderID = std::uint64_t;
using Price = std::uint64_t;

struct Order {
    std::uint64_t order_id;
    std::uint64_t price;
    std::uint64_t sequence_no;
    std::uint32_t remaining_quantity;
    Side side;
};


struct Trade {
    std::uint64_t bid_order_id;
    std::uint64_t ask_order_id;
    std::uint64_t price; 
    std::uint64_t trade_no;
    std::uint32_t quantity;
    bool operator==(const Trade&) const = default;
    friend std::ostream& operator<<(std::ostream& cout, const Trade& trade);
};


struct OrderComparator {
    bool operator()(const Order& a, const Order& b) const;
};