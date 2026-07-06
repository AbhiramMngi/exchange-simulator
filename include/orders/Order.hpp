#include <cstdint>
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
    std::uint64_t buy_order_id;
    std::uint64_t sell_order_id;
    std::uint64_t price; 
    std::uint64_t timestamp_ns;
    std::uint32_t quantity;
};

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const;
};
struct SellComparator {
    bool operator()(const Order& a, const Order& b) const;
};