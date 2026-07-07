add_executable(exchange_tests
    test_Order.cpp
    test_Orderbook.cpp
)

target_link_libraries(exchange_tests
    PRIVATE
    exchange
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(exchange_tests)