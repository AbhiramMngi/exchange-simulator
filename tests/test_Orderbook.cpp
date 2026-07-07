#include <gtest/gtest.h>
#include "orderbook/Orderbook.hpp"


TEST(OrderBookTest, Test_Add_Order_Default_Error) {
    OrderBook& ob = OrderBook::getInstance();
    EXPECT_THROW(
        ob.add_order(Order{1, 100, 1, 0, Side::BUY});,
        std::logic_error
    );

    EXPECT_THROW(
        ob.add_order(Order{1, 100, 1, 0, Side::SELL});,
        std::logic_error
    );
};

TEST(OrderBookTest, Test_Add_Order_Buy) {
    OrderBook& ob = OrderBook::getInstance();
    Order sell_order{1, 95, 1, 5, Side::SELL};
    Order buy_order{2, 100, 2, 10, Side::BUY};
    

    ob.add_order(sell_order);
    ob.add_order(buy_order);
    std::vector<Trade> trades_expected{Trade{2, 1, 95, 1, 5}};
    std::vector<Trade> trades_actual{ob.trade_log()};

    EXPECT_EQ(
        trades_expected,
        trades_actual
    );
    ob.clear();

};

TEST(OrderBookTest, Test_Add_Order_Sell) {
    OrderBook& ob = OrderBook::getInstance();
    Order sell_order{2, 95, 2, 5, Side::SELL};
    Order buy_order{1, 100, 1, 10, Side::BUY};
    
    ob.add_order(buy_order);
    ob.add_order(sell_order);
    
    std::vector<Trade> trades_expected{Trade{1, 2, 100, 1, 5}};
    std::vector<Trade> trades_actual{ob.trade_log()};

    EXPECT_EQ(
        trades_expected,
        trades_actual
    );
    ob.clear();
};

TEST(OrderBookTest, Test_Add_Order_Complete_Fill) {
    OrderBook& ob = OrderBook::getInstance();
    Order sell_order{2, 95, 2, 5, Side::SELL};
    Order buy_order{1, 100, 1, 5, Side::BUY};
    
    ob.add_order(buy_order);
    ob.add_order(sell_order);
    
    std::vector<Trade> trades_expected{Trade{1, 2, 100, 1, 5}};
    std::vector<Trade> trades_actual{ob.trade_log()};

    EXPECT_EQ(
        trades_expected,
        trades_actual
    );
    EXPECT_EQ(
        ob.get_bid_count(), 0
    );
    EXPECT_EQ(
        ob.get_ask_count(), 0
    );
    ob.clear();
};

TEST(OrderBookTest, Test_Add_Order_Determinism) {
    auto& book = OrderBook::getInstance();
    book.clear();

    book.add_order({1, 100, 1, 100, Side::BUY});
    EXPECT_EQ(book.get_bid_count(), 1);
    EXPECT_EQ(book.best_bid().price, 100);
    EXPECT_EQ(book.trade_log().size(), 0);

    book.add_order({2, 101, 2, 50, Side::BUY});
    EXPECT_EQ(book.best_bid().order_id, 2);
    EXPECT_EQ(book.best_bid().price, 101);
    EXPECT_EQ(book.best_bid().remaining_quantity, 50);

    book.add_order({3, 101, 3, 30, Side::BUY});
    EXPECT_EQ(book.get_bid_count(), 3);

    book.add_order({4, 101, 4, 40, Side::SELL});

    ASSERT_EQ(book.trade_log().size(), 1);

    EXPECT_EQ(book.trade_log()[0],
        (Trade{
            2,
            4,
            101,
            1,
            40
        }));

    EXPECT_EQ(book.best_bid().order_id, 2);
    EXPECT_EQ(book.best_bid().remaining_quantity, 10);

    book.add_order({5, 101, 5, 25, Side::SELL});

    ASSERT_EQ(book.trade_log().size(), 3);

    EXPECT_EQ(book.trade_log()[1],
        (Trade{
            2,
            5,
            101,
            2,
            10
        }));

    EXPECT_EQ(book.trade_log()[2],
        (Trade{
            3,
            5,
            101,
            3,
            15
        }));

    EXPECT_EQ(book.best_bid().order_id, 3);
    EXPECT_EQ(book.best_bid().remaining_quantity, 15);

    book.add_order({6, 102, 6, 200, Side::SELL});

    EXPECT_EQ(book.best_ask().order_id, 6);
    EXPECT_EQ(book.best_ask().remaining_quantity, 200);

    book.add_order({7, 103, 7, 250, Side::BUY});

    ASSERT_EQ(book.trade_log().size(), 4);

    EXPECT_EQ(book.trade_log()[3],
        (Trade{
            7,
            6,
            102,
            4,
            200
        }));

    EXPECT_EQ(book.best_bid().order_id, 7);
    EXPECT_EQ(book.best_bid().remaining_quantity, 50);

    book.add_order({8, 103, 8, 60, Side::SELL});

    ASSERT_EQ(book.trade_log().size(), 5);

    EXPECT_EQ(book.trade_log()[4],
        (Trade{
            7,
            8,
            103,
            5,
            50
        }));

    EXPECT_EQ(book.best_ask().order_id, 8);
    EXPECT_EQ(book.best_ask().remaining_quantity, 10);

    book.add_order({9, 103, 9, 5, Side::BUY});
    ASSERT_EQ(book.trade_log().size(), 6);

    EXPECT_EQ(book.trade_log()[5],
        (Trade{
            9,
            8,
            103,
            6,
            5
        }));

    EXPECT_EQ(book.best_ask().remaining_quantity, 5);

    book.add_order({10, 102, 10, 20, Side::BUY});

    EXPECT_EQ(book.best_bid().order_id, 10);
    EXPECT_EQ(book.best_bid().price, 102);

    book.add_order({11, 100, 11, 120, Side::SELL});

    ASSERT_EQ(book.trade_log().size(), 9);

    EXPECT_EQ(book.trade_log()[6],
        (Trade{
            10,
            11,
            102,
            7,
            20
        }));

    EXPECT_EQ(book.trade_log()[7],
        (Trade{
            3,
            11,
            101,
            8,
            15
        }));

    EXPECT_EQ(book.trade_log()[8],
        (Trade{
            1,
            11,
            100,
            9,
            85
        }));

    EXPECT_EQ(book.best_bid().order_id, 1);
    EXPECT_EQ(book.best_bid().remaining_quantity, 15);

    book.add_order({12, 99, 12, 30, Side::SELL});

    ASSERT_EQ(book.trade_log().size(), 10);

    EXPECT_EQ(book.trade_log()[9],
        (Trade{
            1,
            12,
            100,
            10,
            15
        }));

    EXPECT_EQ(book.best_ask().order_id, 12);
    EXPECT_EQ(book.best_ask().remaining_quantity, 15);

    book.add_order({13, 100, 13, 40, Side::BUY});

    ASSERT_EQ(book.trade_log().size(), 11);

    EXPECT_EQ(book.trade_log()[10],
        (Trade{
            13,
            12,
            99,
            11,
            15
        }));

    EXPECT_EQ(book.get_bid_count(), 1);
    EXPECT_EQ(book.get_ask_count(), 1);

    EXPECT_EQ(book.best_bid().order_id, 13);
    EXPECT_EQ(book.best_bid().remaining_quantity, 25);

    EXPECT_EQ(book.best_ask().order_id, 8);
    EXPECT_EQ(book.best_ask().remaining_quantity, 5);

    book.clear();

};

