#include <gtest/gtest.h>
#include "orders/Order.hpp"


TEST(OrderTest, BuyOrderPriceComparison) {
    Order order1{0, 100, 10, 10, Side::BUY}, order2{1, 101, 10, 10, Side::BUY};
    OrderComparator buy_comp{};
    EXPECT_TRUE(buy_comp(order1, order2));
    EXPECT_FALSE(buy_comp(order2, order1));
}

TEST(OrderTest, BuyOrderTimeComparison) {
    Order order1{0, 100, 10, 10, Side::BUY}, order2{1, 100, 11, 10, Side::BUY};
    OrderComparator buy_comp{};
    EXPECT_FALSE(buy_comp(order1, order2));
    EXPECT_TRUE(buy_comp(order2, order1));
}

TEST(OrderTest, SellOrderPriceComparison) {
    Order order1{0, 100, 10, 10, Side::SELL}, order2{1, 101, 10, 10, Side::SELL};
    OrderComparator sell_comp{};
    EXPECT_FALSE(sell_comp(order1, order2));
    EXPECT_TRUE(sell_comp(order2, order1));
}

TEST(OrderTest, SellOrderTimeComparison) {
    Order order1{0, 100, 10, 10, Side::SELL}, order2{1, 100, 11, 10, Side::SELL};
    OrderComparator sell_comp{};
    EXPECT_FALSE(sell_comp(order1, order2));
    EXPECT_TRUE(sell_comp(order2, order1));
}